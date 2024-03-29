#include <csignal>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>

#include "ara/core/abort.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "ara/core/initialization.h"
#include "ara/exec/application_client.h"
#include "ara/log/logging.h"
#include "osabstraction/thread/thread.h"
#include "osabstraction/process/process.h"
#include "vac/language/throw_or_terminate.h"

#include "accessor/variable.h"
#include "accessor/memory_accessor_factory.h"
#include "mtd/measurement_daemon.h"

#include "idc6mt_error_domain.h"

namespace {
/*!
 * \brief Initializes the signal handling.
 * \return void.
 */
void InitializeSignalHandling() noexcept
{
    bool success{true};
    sigset_t signals;

    /* Block all signals except the SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV
     * signals because blocking them will lead to undefined behavior. Their
     * default handling shall not be changed (dependent on underlying POSIX
     * environment, usually process is killed and a dump file is * written).
     * Signal mask will be inherited by subsequent threads. */

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

namespace idc6mtd {

/*!
 * \brief Signal handler thread.
 */
std::thread signal_handler_thread{};

/*!
 * \brief Flag to exit the application.
 */
std::atomic_bool exit_requested{false};

/*!
 * \brief Flag to mark if the application exit was triggered by a signal.
 */
std::atomic_bool terminated_by_signal{false};

/*!
 * \brief Flag to indicate initialization error. Only used in main thread.
 */
bool has_initialization_failed{false};

/*!
 * \brief Default path to the configuration files
 */
const std::string configuration_directory{"/opt/idc6mt/etc"};

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
        logger.LogDebug() << "IDC6 MT daemon app is reporting Application state "
                          << application_state_string.c_str();

        /* #30 send application state */
        if (application_client.ReportApplicationState(application_state)
            == ara::exec::ApplicationReturnType::kSuccess) {
            logger.LogDebug() << "IDC6 MT daemon reported Application state "
                              << application_state_string.c_str() << " successfully";
        } else {
            /* #35 application state could not be set. */
            logger.LogError() << "IDC6 MT daemon could not report the Application state "
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
            if (!exit_requested) {
                /* #35 request application exit.
                 *(SignalHandler initiate the shutdown!) */
                exit_requested = true;
            }
            terminated_by_signal = true;
        }
    } while (!exit_requested);
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
    vac::container::CStringView thread_name = vac::container::CStringView::FromLiteral("MtdSH", 5);

    /* #30 Start signal handler thread. */
    signal_handler_thread = std::thread(&SignalHandlerThread);

    /* #40 Create the thread native_handle object. */
    std::thread::native_handle_type const thread_id{(signal_handler_thread).native_handle()};

    /* #50 Set thread name and return the ara::core::Result object. */
    return osabstraction::thread::SetNameOfThread(thread_id, thread_name)
        .AndThen([]() -> R { return R{osabstraction::process::GetProcessId()}; })
        .OrElse([thread_name](ara::core::ErrorCode) -> R {
            return R::FromError(Idc6MtdErrc::kThreadCreationFailed, "Naming failed.");
        });
}

size_t heartbeat_counter = 0;

} // namespace idc6mtd

int main()
{
    InitializeSignalHandling();

    ara::core::Result<void> init_result{ara::core::Initialize()};
    ara::exec::ApplicationClient application_client;

    if (!init_result.HasValue()) {
        char const* msg{"ara::core::Initialize() failed."};
        std::cerr << msg << "\nResult contains: " << init_result.Error().Message() << ", "
                  << init_result.Error().UserMessage() << "\n";

        ara::core::Abort(msg);
    } else {
        ara::log::Logger& log{ara::log::CreateLogger("MTD", "Measurement and trace daemon")};

        idc6mtd::StartSignalHandlerThread().InspectError(
            [](ara::core::ErrorCode const& error) { idc6mtd::has_initialization_failed = true; });

        if (idc6mtd::has_initialization_failed) {
            return -1;
        }

        /* Create the application object and run it */
        idc6mtd::ReportState(application_client, log, ara::exec::ApplicationState::kRunning);

        try {
            auto mtd = mt::MeasurementTraceDaemon(idc6mtd::configuration_directory);

            while (!idc6mtd::exit_requested) {
                log.LogInfo() << "MT daemon running, hearbeat: " << idc6mtd::heartbeat_counter++;
                mtd.ReadVariables();
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        } catch (mt::MeasurementTraceDaemon::MtdException& e) {
            log.LogFatal() << "Critical error in daemon: " << e.what();
        }

        /* Deinitialize ara::core */
        ara::core::Result<void> deinit_result{ara::core::Deinitialize()};

        if (!deinit_result.HasValue()) {
            char const* msg{"ara::core::Deinitialize() failed."};
            std::cerr << msg << "\nResult contains: " << deinit_result.Error().Message() << ", "
                      << deinit_result.Error().UserMessage() << "\n";
            ara::core::Abort(msg);
        }

        idc6mtd::ReportState(application_client, log, ara::exec::ApplicationState::kTerminating);
    }
}
