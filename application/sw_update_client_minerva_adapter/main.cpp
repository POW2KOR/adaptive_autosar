#include "activation_manager.h"
#include "ara/core/abort.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "ara/core/initialization.h"
#include "ara/exec/application_client.h"
#include "ara/log/logging.h"
#include "osabstraction/thread/thread.h"
#include "sw_update_error_domain.h"

#include "mb/swuc/service_interfaces/plugin/swdlplugin_skeleton.h"

#include <csignal>
#include <thread>

namespace {
/*!
 * \brief Initializes the signal handling.
 * \return void.
 */
void InitializeSignalHandling() noexcept
{
    bool success{true};
    sigset_t signals;

    /* Block all signals except the SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV signals because
     * blocking them will lead to undefined behavior. Their default handling shall not be changed
     * (dependent on underlying POSIX environment, usually process is killed and a dump file is
     * written). Signal mask will be inherited by subsequent threads. */

    success = success && (0 == sigfillset(&signals));
    success = success && (0 == sigdelset(&signals, SIGABRT));
    success = success && (0 == sigdelset(&signals, SIGBUS));
    success = success && (0 == sigdelset(&signals, SIGFPE));
    success = success && (0 == sigdelset(&signals, SIGILL));
    success = success && (0 == sigdelset(&signals, SIGSEGV));
    success = success && (0 == pthread_sigmask(SIG_SETMASK, &signals, nullptr));

    if (!success) {
        ara::core::Abort("InitializeSignalHandling failed.");
    }
}
} // namespace

namespace Application {
/*!
 * \brief Signal handler thread.
 */
std::thread signal_handler_thread_{};

/*!
 * \brief Flag to exit the application.
 */
std::atomic_bool exit_requested_{false};

/*!
 * \brief Flag to mark if the application exit was triggered by a signal.
 */
std::atomic_bool terminated_by_signal_{false};

/*!
 * \brief Flag to indicate initialization error. Only used in main thread.
 */
bool has_initialization_failed_{false};

/**
 * \brief Report to execution manager the status of the application
 */
void ReportState(
    ara::exec::ApplicationClient& application_client,
    ara::log::Logger& logger,
    ara::exec::ApplicationState application_state)
{
    std::string application_state_string = "NotDefined";
    bool error_occurred = false;

    /* #10 verify which state should be reported  */
    if (application_state == ara::exec::ApplicationState::kRunning) {
        application_state_string = "kRunning";
    } else if (application_state == ara::exec::ApplicationState::kTerminating) {
        application_state_string = "kTerminating";
    } else {
        /* #15 invalid application state detected */
        error_occurred = true;
        logger.LogError() << "ReportState called with an invalid application state: "
                          << application_state_string.c_str();
    }

    /* #20 check if invalid application state was detected. */
    if (!error_occurred) {
        logger.LogDebug() << "sw_update app is reporting Application state "
                          << application_state_string.c_str();

        /* #30 send application state */
        if (application_client.ReportApplicationState(application_state)
            == ara::exec::ApplicationReturnType::kSuccess) {
            logger.LogDebug() << "sw_update app reported Application state "
                              << application_state_string.c_str() << " successfully";
        } else {
            /* #35 application state could not be set. */
            logger.LogError() << "sw_update app could not report the Application state "
                              << application_state_string.c_str();
        }
    }
}

/*!
 * \internal
 * - #10 empty the set of signals.
 * - #20 add SIGTERM to signal set.
 * - #21 add SIGINT to signal set.
 * - #30 loop until SIGTERM or SIGINT signal received.
 * -    #35 request application exit.
 * \endinternal
 */
void SignalHandlerThread()
{
    sigset_t signal_set;

    /* #10 empty the set of signals. */
    if (0 != sigemptyset(&signal_set)) {
        ara::core::Abort("Empty signal set failed.");
    }
    /* #20 add SIGTERM to signal set. */
    if (0 != sigaddset(&signal_set, SIGTERM)) {
        ara::core::Abort("Adding SIGTERM failed.");
    }
    /* #21 add SIGINT to signal set. */
    if (0 != sigaddset(&signal_set, SIGINT)) {
        ara::core::Abort("Adding SIGINT failed.");
    }

    /* #30 loop until SIGTERM or SIGINT signal received. */
    int sig{-1};

    do {
        if (0 != sigwait(&signal_set, &sig)) {
            ara::core::Abort("Waiting for SIGTERM or SIGINT failed.");
        }

        if ((sig == SIGTERM) || (sig == SIGINT)) {
            if (!exit_requested_) {
                /* #35 request application exit. (SignalHandler initiate the shutdown!) */
                exit_requested_ = true;
            }
            terminated_by_signal_ = true;
        }
    } while (!exit_requested_);
}

/*!
 * \brief Start a thread handling all signals send to this process.
 * \internal
 * - #10 Create ara::core::Result object.
 * - #20 Create thread_name.
 * - #30 Start signal handler thread.
 * - #40 Create the thread native_handle object.
 * - #50 Set thread name and return the ara::core::Result object.
 * \endinternal
 */
ara::core::Result<osabstraction::process::ProcessId> StartSignalHandlerThread()
{
    /* #10 Create ara::core::Result object. */
    using R = ara::core::Result<osabstraction::process::ProcessId>;

    /* #20 Create thread_name. */
    vac::container::CStringView thread_name
        = vac::container::CStringView::FromLiteral("SwUpdateSignal", 10);

    /* #30 Start signal handler thread. */
    signal_handler_thread_ = std::thread(&SignalHandlerThread);

    /* #40 Create the thread native_handle object. */
    std::thread::native_handle_type const thread_id{(signal_handler_thread_).native_handle()};

    /* #50 Set thread name and return the ara::core::Result object. */
    return osabstraction::thread::SetNameOfThread(thread_id, thread_name)
        .AndThen([]() -> R { return R{osabstraction::process::GetProcessId()}; })
        .OrElse([thread_name](ara::core::ErrorCode) -> R {
            return R::FromError(SwUpdateAppErrc::kThreadCreationFailed, "Naming failed.");
        });
}

using namespace mb::swuc::service_interfaces::plugin::internal::methods;

class SwUpdateService: public mb::swuc::service_interfaces::plugin::skeleton::SwdlPluginSkeleton {
public:
    explicit SwUpdateService(ara::core::InstanceSpecifier server_port) 
        : mb::swuc::service_interfaces::plugin::skeleton::SwdlPluginSkeleton(server_port) 
    {}

    ~SwUpdateService() {}

    // Implementation for all function is not done by purpose
    // Reason is that the implementation is out of the scope
    ara::core::Future<Rollback::Output> Rollback() override {
        ara::core::Future<Rollback::Output> ret;
        return ret;
    }
    
    ara::core::Future<GetResumePosition::Output> GetResumePosition() override {
        ara::core::Future<GetResumePosition::Output> ret;
        return ret;
    }
    
    void CleanUp() override {
        return;
    }
    
    void Revert() override {
        return;
    }
    
    ara::core::Future<Verify::Output> Verify() override {
        ara::core::Future<Verify::Output> ret;
        return ret;
    }
    
    void Process(const std::uint64_t& resumeOffset, const ::mb::swuc::types::ByteVector& file) override {
        return;
    }

    ara::core::Future<Activate::Output> Activate() override {
        ara::core::Future<Activate::Output> ret;
        return ret;
    }
};
} // namespace Application

int main()
{
    // Initialize signal handler to ensure all signals are blocked for all child processes
    InitializeSignalHandling();

    ara::core::Result<void> init_result{ara::core::Initialize()};
    ara::exec::ApplicationClient application_client;

    if (!init_result.HasValue()) {
        char const* msg{"ara::core::Initialize() failed."};
        std::cerr << msg << "\nResult contains: " << init_result.Error().Message() << ", "
                  << init_result.Error().UserMessage() << "\n";

        ara::core::Abort(msg);
    } else {
        ara::log::Logger& log{ara::log::CreateLogger("sw_update", "sw_update app")};

        ara::core::Optional<Application::SwUpdateService> swUpdateServer;
        
        // The path took from aracom_someip_binding_init.cpp file
        // File generated by amsr_someipbinding
        ara::core::basic_string_view<char> instance_specifier_path {
            "sw_update_client_minerva_adapter_app/RootSwComponentPrototype/ProvideSwdlPluginPort"};
        ara::core::InstanceSpecifier const swUpdate_instance_specifier{instance_specifier_path};
        swUpdateServer.emplace(swUpdate_instance_specifier);

        swUpdateServer->OfferService();

        Application::StartSignalHandlerThread().InspectError([](ara::core::ErrorCode const& error) {
            Application::has_initialization_failed_ = true;
        });

        if (Application::has_initialization_failed_) {
            return -1;
        }

        /* Create the application object and run it */
        Application::ReportState(application_client, log, ara::exec::ApplicationState::kRunning);

        std::shared_ptr<ActivationManagerBase> am(
            new ActivationManagerTimer(std::chrono::milliseconds(500)));

        while (!Application::exit_requested_) {
            /* Do nothing for now */
            am->wait();
            log.LogDebug() << "Running in cycle " << am->getCycle();
        }

        swUpdateServer->StopOfferService();
        swUpdateServer.reset();

        /* Deinitialize ara::core */
        ara::core::Result<void> deinit_result{ara::core::Deinitialize()};

        if (!deinit_result.HasValue()) {
            char const* msg{"ara::core::Deinitialize() failed."};
            std::cerr << msg << "\nResult contains: " << deinit_result.Error().Message() << ", "
                      << deinit_result.Error().UserMessage() << "\n";
            ara::core::Abort(msg);
        }

        Application::ReportState(
            application_client, log, ara::exec::ApplicationState::kTerminating);
    }

    return 0;
}