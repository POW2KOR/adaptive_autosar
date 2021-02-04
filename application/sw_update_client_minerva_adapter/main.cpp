#include <csignal>
#include <thread>

#include "ara/core/abort.h"
#include "ara/core/initialization.h"
#include "ara/exec/application_client.h"
#include "ara/log/logging.h"


/**
 * \brief Flag to identify whether the application was requested to terminate, i.e., has received a
 * SIGTERM
 */
std::atomic_bool exit_requested_(false);

/**
 * \brief Vector to store all threads spawned by this application.
 */
std::vector<std::thread> threads_;


/**
 * \brief Signal handler function for SIGTERM
 */
void SignalHandler(void)
{
    ara::log::Logger& logger{ara::log::CreateLogger(
        "sw_update",
        "Context for prototype method invocation")};
    sigset_t signal_set;
    int sig = -1;
    sigemptyset(&signal_set); /* Empty the set of signals */
    sigaddset(&signal_set, SIGTERM); /* Add only SIGTERM to set */
    logger.LogInfo() << "SignalHandler started";
    while (sig != SIGTERM) {
        sigwait(&signal_set, &sig);
        logger.LogInfo() << "Received signal number:" << sig;
    }
    logger.LogInfo() << "Received signal SIGTERM";
    exit_requested_ = true;
}

/**
 * \brief  Function to initialize the calculator client
 */
void Initialize_Signalhandler(void)
{
    /* Block all signals for this thread. Signal mask will be inherited by subsequent threads. */
    sigset_t signals;
    sigfillset(&signals);
    pthread_sigmask(SIG_SETMASK, &signals, NULL);
    /* spawn a new signal handler thread*/
    threads_.emplace_back(SignalHandler);
}

/**
 * \brief Report to execution manager the status of the application
 */
void ReportApplicationState(ara::exec::ApplicationClient& application_client, 
                            ara::log::Logger& logger, 
                            ara::exec::ApplicationState application_state)
{
    std::string application_state_string = "NotDefined";
    bool error_occurred = false;

    if (application_state == ara::exec::ApplicationState::kRunning) 
    {
        application_state_string = "kRunning";
    } else if (application_state == ara::exec::ApplicationState::kTerminating) 
    {
        application_state_string = "kTerminating";
    } else 
    {
        error_occurred = true;
        logger.LogError() << "ReportApplicationState called with an invalid application state: " 
                          << application_state_string.c_str();
    }

    /* #20 check if invalid application state was detected. */
    if (!error_occurred) 
    {
        logger.LogDebug() << "sw_update app is reporting Application state " 
                          << application_state_string.c_str();

        /* #30 send application state */
        if (application_client.ReportApplicationState(application_state) ==
                ara::exec::ApplicationReturnType::kSuccess) 
        {
            logger.LogDebug() << "sw_update app reported Application state " 
                              << application_state_string.c_str() 
                              << " successfully";
        } 
        else 
        {
            /* #35 application state could not be set. */
            logger.LogError() << "sw_update app could not report the Application state " 
                              << application_state_string.c_str();
        }
    }
}


int main()
{
    // Initialize signal handler to ensure all signals are blocked for all child processes
    Initialize_Signalhandler();

    ara::core::Result<void> init_result{ara::core::Initialize()};
    ara::exec::ApplicationClient application_client;
    ara::log::Logger& log{ara::log::CreateLogger("sw_update", "sw_update app")};

    if (!init_result.HasValue()) 
    {
        char const* msg{"ara::core::Initialize() failed."};
        std::cerr << msg << "\nResult contains: " << init_result.Error().Message() << ", " 
                  << init_result.Error().UserMessage() << "\n";
    
        ara::core::Abort(msg);
    }
    else 
    {
        /* Create the application object and run it */
        ReportApplicationState(application_client, log, ara::exec::ApplicationState::kRunning);

        while (!exit_requested_)
        {
            /* Do nothing for now */
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        ReportApplicationState(application_client, log, ara::exec::ApplicationState::kTerminating);

        /* Deinitialize ara::core */
        ara::core::Result<void> deinit_result{ara::core::Deinitialize()};

        if (!deinit_result.HasValue()) 
        {
            char const* msg{"ara::core::Deinitialize() failed."};
            std::cerr << msg << "\nResult contains: " << deinit_result.Error().Message() 
                    << ", " << deinit_result.Error().UserMessage() << "\n";
            ara::core::Abort(msg);
        }
    }
    
    return 0;
}