
#include <signal.h>
#include <stdint.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <csignal>
#include <thread>

#if MBITION_USE_CASE_1
#include "use_case_1.h"
#endif

#include "ara/com/runtime.h"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/log/logging.h"

#ifdef ENABLE_EXEC_MANAGER
#include "ara/exec/application_client.h"
#endif

#include "ara/log/config/appl_manifest_logging_config.h"
#include "command_line_parser.h"
#include "config/logging_cfg.h"
#include "vac/memory/optional.h"
#include "vac/memory/three_phase_allocator.h"

#ifdef ENABLE_EXEC_MANAGER
using ApplicationClient = ara::exec::ApplicationClient;
using ApplicationState = ara::exec::ApplicationState;
#endif

/* Forward declarations */
void Initialize_Signalhandler(void);
void SignalHandler(void);

/**
 * \brief Container for command line arguments.
 */
struct CommandLineArguments {
    /**
     * \brief Path to configuration file.
     */
    std::string cfg_path_;
    /**
     * \brief Enables the applicationstate report to the executionmanager if true.
     */
    bool enable_em_;
};

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
 * \brief Prints the usage message.
 *
 * \param argc argument count
 * \param argv command line arguments
 */
static void Usage(const int argc, char* argv[])
{
    if (argc > 0) {
        std::cerr << "usage: " << argv[0] << R"( [-h] [-d] -c <config file path>
           -h                            Print this message and exit.
           -c <config file path>         Specify the location of the configuration file.
           -d                            Disabling the applicationstate report to the executionmanager.
        )";
    } else {
        std::cerr << "usage: calculatorClient "
                  << R"( [-h] [-d] -c <config file path>
           -h                            Print this message and exit.
           -c <config file path>         Specify the location of the configuration file.
           -d                            Disabling the applicationstate report to the executionmanager.
        )";
    }
}

/**
 * \brief Parses command line arguments.
 *
 * \param argc Command line argument count.
 * \param argv Array of pointers to command line arguments.
 * \return Parsed arguments.
 */
static CommandLineArguments ParseArguments(int argc, char* argv[])
{
    CommandLineArguments args;
    args.cfg_path_ = "";
    args.enable_em_ = true;

    mbition_app_prototype::commandlineparser::CommandLineParser parser(argc, argv, "hc:d");
    for (auto& it : parser) {
        switch (it.GetOption()) {
        case 'h':
            Usage(argc, argv);
            exit(EXIT_SUCCESS);
            break;
        case 'c':
            args.cfg_path_ = it.GetOptionArgument();
            break;
        case 'd':
            args.enable_em_ = false;
            break;
        default:
            Usage(argc, argv);
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (args.cfg_path_ == "") {
        ara::log::InitLogging(
            mbition_app_prototype::config::kLoggerApplicationId,
            mbition_app_prototype::config::kLoggerApplicationDescription,
            ara::log::LogLevel::kError,
            ara::log::LogMode::kConsole,
            "");
        ara::log::LogError() << "No configuration file path provided\n";
        exit(EXIT_FAILURE);
    }
    return args;
}

int main(int argc, char* argv[])
{
    // Initialize signal handler to ensure all signals are blocked for all child processes
    Initialize_Signalhandler();

    // Read configuration parameters of logging
    // sizeof() operator can be used, when calc::config::kLoggingConfigFile is defined as char[]
    ara::log::config::ApplManifestLoggingConfig config
        = ara::log::config::GetApplManifestLoggingConfig(
            {mbition_app_prototype::config::kLoggingConfigFile,
             sizeof(mbition_app_prototype::config::kLoggingConfigFile)});

    // Initialize logging framework
    ara::log::InitLogging(
        config.application_id,
        config.application_descr,
        config.default_log_level,
        config.log_mode,
        config.log_file_path);

    // Create logger in the allocation phase
    ara::log::Logger& logger{ara::log::CreateLogger(
        mbition_app_prototype::config::kContextIdProtoMethodInvocator, "Context for prototype")};
    logger.LogInfo() << "Starting prototype";

    CommandLineArguments args = ParseArguments(argc, argv);

#ifdef ENABLE_EXEC_MANAGER
    vac::memory::optional<ApplicationClient> app_client;
    if (args.enable_em_) {
        // Instantiate the ApplicationClient
        app_client.emplace();
    }
#endif

    try {
#ifdef MBITION_USE_CASE_1
        // Loading config file and initialize runtime
        logger.LogInfo() << "Initializing runtime...";
        mbition::use_case_1::initialize(args.cfg_path_);
#endif

        // Set allocation phase to 'steady' after all memory resources are initialized and allocated
        logger.LogDebug() << __FUNCTION__
                          << " Setting AllocationPhaseManager::AllocationPhase to 'steady'.";
        vac::memory::AllocationPhaseManager::GetInstance().SetPhase(
            vac::memory::AllocationPhaseManager::AllocationPhase::steady);

#ifdef ENABLE_EXEC_MANAGER
        if (args.enable_em_ && app_client.has_value()) {
            // Report application state to execution management
            logger.LogInfo() << "Reporting application state kRunning.";
            app_client->ReportApplicationState(ApplicationState::kRunning);
        }
#endif

#if MBITION_USE_CASE_1
        logger.LogInfo() << "Running Mbition use-case 1";

        // Search for service. When a service instance is found, the function
        // FindServiceHandler gets called

        logger.LogInfo() << "Searching for service";
        ara::com::FindServiceHandle find_service_handle = mbition::use_case_1::start_find_service();

        // Wait until service is found
        while (!mbition::use_case_1::service_found() && !exit_requested_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        logger.LogInfo() << "Stop searching for service";
        mbition::use_case_1::stop_find_service(find_service_handle);

        while (!exit_requested_) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        mbition::use_case_1::deinitialize();
#endif

        logger.LogInfo() << "Finished prototype operation";

#ifdef ENABLE_EXEC_MANAGER
        if (args.enable_em_ && app_client.has_value()) {
            // Report application state to execution management
            logger.LogInfo() << "Reporting application state kTerminating.";
            app_client->ReportApplicationState(ApplicationState::kTerminating);
        }
#endif
    } catch (const std::runtime_error& error) {
        logger.LogInfo() << error.what();
    }

    logger.LogInfo() << "Terminating";

    // Set allocation phase to 'deallocation' before destroying and deallocating all memory
    // resources
    logger.LogDebug() << __FUNCTION__
                      << " Setting AllocationPhaseManager::AllocationPhase to 'deallocation'";
    vac::memory::AllocationPhaseManager::GetInstance().SetPhase(
        vac::memory::AllocationPhaseManager::AllocationPhase::deallocation);

    return 0;
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
 * \brief Signal handler function for SIGTERM
 */
void SignalHandler(void)
{
    ara::log::Logger& logger{ara::log::CreateLogger(
        mbition_app_prototype::config::kContextIdProtoMethodInvocator,
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
