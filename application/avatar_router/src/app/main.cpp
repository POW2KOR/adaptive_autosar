#include "ara/core/abort.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "ara/core/initialization.h"
#include "ara/exec/application_client.h"
#include "vac/language/throw_or_terminate.h"
#include "ara/log/logging.h"
#include "osabstraction/thread/thread.h"
#include "avatar_router_error_domain.h"

#include <iostream>
#include <csignal>
#include <thread>
#include <unistd.h>

namespace {

void InitializeSignalHandling() noexcept
{
    bool success{true};
    sigset_t signals;

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

    if (application_state == ara::exec::ApplicationState::kRunning) {
        application_state_string = "kRunning";
    } else if (application_state == ara::exec::ApplicationState::kTerminating) {
        application_state_string = "kTerminating";
    } else {
        error_occurred = true;
        logger.LogError()
            << "ReportState called with an invalid application state: "
            << application_state_string.c_str();
    }

    if (!error_occurred) {
        logger.LogDebug() << "Avatar Router is reporting Application state "
                          << application_state_string.c_str();

        if (application_client.ReportApplicationState(application_state)
            == ara::exec::ApplicationReturnType::kSuccess) {
            logger.LogDebug()
                << "Avatar Router reported Application state "
                << application_state_string.c_str() << " successfully";
        } else {
            logger.LogError()
                << "Avatar Router could not report the Application state "
                << application_state_string.c_str();
        }
    }
}

/**
 * \brief Thread to process incoming signals
 */
void SignalHandlerThread()
{
    sigset_t signal_set;

    if (0 != sigemptyset(&signal_set)) {
        ara::core::Abort("Empty signal set failed.");
    }
    if (0 != sigaddset(&signal_set, SIGTERM)) {
        ara::core::Abort("Adding SIGTERM failed.");
    }
    if (0 != sigaddset(&signal_set, SIGINT)) {
        ara::core::Abort("Adding SIGINT failed.");
    }

    int sig{-1};

    do {
        if (0 != sigwait(&signal_set, &sig)) {
            ara::core::Abort("Waiting for SIGTERM or SIGINT failed.");
        }

        if ((sig == SIGTERM) || (sig == SIGINT)) {
            if (!exit_requested) {
                exit_requested = true;
            }
            terminated_by_signal = true;
        }
    } while (!exit_requested);
}

/*!
 * \brief Start a thread handling all signals send to this process.
 */
ara::core::Result<osabstraction::process::ProcessId> StartSignalHandlerThread()
{
    using R = ara::core::Result<osabstraction::process::ProcessId>;

    vac::container::CStringView thread_name
        = vac::container::CStringView::FromLiteral("ARSigH", 7);

    signal_handler_thread = std::thread(&SignalHandlerThread);

    std::thread::native_handle_type const thread_id{
        (signal_handler_thread).native_handle()};

    return osabstraction::thread::SetNameOfThread(thread_id, thread_name)
        .AndThen([]() -> R {
            return R{getpid()};
        })
        .OrElse([thread_name](ara::core::ErrorCode) -> R {
            return R::FromError(
                AvatarRouterErrc::kThreadCreationFailed,
                "Naming failed.");
        });
}

} // namespace Application

int main() {
    InitializeSignalHandling();

    ara::core::Result<void> init_result{ara::core::Initialize()};
    ara::exec::ApplicationClient application_client;

    if (!init_result.HasValue()) {
        char const* msg{"ara::core::Initialize() failed."};
        std::cerr
            << msg << "\nResult contains: " << init_result.Error().Message()
            << ", " << init_result.Error().UserMessage() << "\n";

        ara::core::Abort(msg);
    } else {
        ara::log::Logger& log{
            ara::log::CreateLogger("AR", "Avatar Router")};

        Application::StartSignalHandlerThread()
            .InspectError([](ara::core::ErrorCode const& error) {
                Application::has_initialization_failed = true;
            });

        if (Application::has_initialization_failed) {
            return -1;
        }

        Application::ReportState(
            application_client, log, ara::exec::ApplicationState::kRunning);

        log.LogInfo() << "Statring main loop of Avatar Router";

        while (!Application::exit_requested) {
            // Router's logic runs here
            log.LogInfo() << "Avatar Router running";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        ara::core::Result<void> deinit_result{ara::core::Deinitialize()};

        if (!deinit_result.HasValue()) {
            char const* msg{"ara::core::Deinitialize() failed."};
            std::cerr
                << msg << "\nResult contains: "
                << deinit_result.Error().Message() << ", "
                << deinit_result.Error().UserMessage() << "\n";
            ara::core::Abort(msg);
        }

        Application::ReportState(
            application_client, log, ara::exec::ApplicationState::kTerminating);
    }
}
