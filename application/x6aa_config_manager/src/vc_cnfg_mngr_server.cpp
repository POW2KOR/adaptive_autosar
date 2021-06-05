/*****************************************************************************
 * \file   vc_cnfg_mngr_server.cpp
 *
 * \brief  VVcCnfgMngrServer class representing the variant coding server application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date   
 * \note   TODO: additional notes
 ******************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "vc_cnfg_mngr_server.h"
#include "x6aa_cnfg_mngr_executable_error_domain.h"

namespace application {

using vac::container::operator""_sv;

/*!
 * \brief Initialize VcCnfgMngrServer application.
 */
VcCnfgMngrServer::VcCnfgMngrServer() {
  log_.LogInfo() << "siX6aaCnfgMngrServiceReservedSkeletonServer Skeleton demo is initializing...";

  this->StartSignalHandlerThread().InspectError([this](ara::core::ErrorCode const& error) {
    has_initialization_failed_ = true;
    log_.LogFatal() << error.Message() << ". " << error.UserMessage();
  });

  /*##### Set up the siX6aaCnfgMngrServiceReservedSkeletonServer for variant coding #### */
  ara::core::InstanceSpecifier const siX6aaCnfgMngrService_instance_specifier{
        "X6AA_Cnfg_Mngr_Executable/X6AA_Cnfg_Mngr_ExecutableRootSwc/AdaptiveProvidedPortType89"_sv};
  siX6aaCnfgMngrServiceReservedSkeletonServer.emplace(siX6aaCnfgMngrService_instance_specifier);
  siX6aaCnfgMngrServiceReservedSkeletonServer->OfferService();
  log_.LogInfo() << "Skeleton siX6aaCnfgMngrServiceReservedSkeletonServer service offered!!";
  
}

/*!
 * \brief Shutdown VcCnfgMngrServer application.
 * \internal
 * - #10 Check if exit was requested by sending SIGTERM or SIGINT.
 * -    #15 Terminate the signal handler thread to shutdown application.
 * - #20 Wait till all threads have joined.
 * \endinternal
 */
VcCnfgMngrServer::~VcCnfgMngrServer() {
  exit_requested = true;

  /*##### deinitialze the siX6aaCnfgMngrServiceReservedSkeletonServer #### */
  siX6aaCnfgMngrServiceReservedSkeletonServer->StopOfferService();
  siX6aaCnfgMngrServiceReservedSkeletonServer.reset();

  ara::core::Deinitialize();

  log_.LogInfo() << "siX6aaCnfgMngrServiceReservedSkeletonServer Skeleton demo shutdown initiated.";

  if (signal_handler_thread.native_handle() != 0) {
    /* #10 Check if exit was requested by sending SIGTERM or SIGINT. */
    if (!terminated_by_signal) {
      /* #15 Terminate the signal handler thread to shutdown. */
      if (0 != pthread_kill(static_cast<pthread_t>(signal_handler_thread.native_handle()), SIGTERM)) {
        log_.LogError() << "Invalid signal!";
      }
    } else {
      log_.LogDebug() << "SIGINT or SIGTERM had been received and had been handled";
    }
  } else {
    log_.LogError() << "Thread ID = 0";
  }

  /* #20 Wait till all threads have joined. */
  if (signal_handler_thread.joinable()) {
    signal_handler_thread.join();
  }

  log_.LogInfo() << "siX6aaCnfgMngrServiceReservedSkeletonServer Skeleton demo finished shutdown.";
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
ara::core::Result<osabstraction::process::ProcessId> VcCnfgMngrServer::StartSignalHandlerThread() {
  /* #10 Create ara::core::Result object. */
  using R = ara::core::Result<osabstraction::process::ProcessId>;

  /* #20 Create thread_name. */
  vac::container::CStringView thread_name = vac::container::CStringView::FromLiteral("SkeletonSignal", 10);

  /* #30 Start signal handler thread. */
  signal_handler_thread = std::thread(&VcCnfgMngrServer::SignalHandlerThread, this);

  /* #40 Create the thread native_handle object. */
  std::thread::native_handle_type const thread_id{(signal_handler_thread).native_handle()};

  /* #50 Set thread name and return the ara::core::Result object. */
  return osabstraction::thread::SetNameOfThread(thread_id, thread_name)
      .AndThen([]() -> R { return R{osabstraction::process::GetProcessId()}; })
      .OrElse([thread_name, this](ara::core::ErrorCode) -> R {
        log_.LogFatal() << "Naming of thread '" << thread_name << "' failed";
        return R::FromError(X6AA_Cnfg_Mngr_ExecutableErrc::kThreadCreationFailed, "Naming failed.");
      });
}

std::int8_t VcCnfgMngrServer::Run() {
  std::int8_t ret{EXIT_SUCCESS};

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    log_.LogInfo() << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo application started";

    while (!exit_requested) {

      std::this_thread::sleep_for(std::chrono::milliseconds(5000));

      /*##### send out data variant coding data #### */
      ::DataTypes::NS_REC_activateSarStorage0131VcEventType_t::REC_activateSarStorage0131VcEventType_t activateSarStorage0131VcEventData;
      ::DataTypes::NS_REC_configureSarTriggerEvents0136VcEventType_t::REC_configureSarTriggerEvents0136VcEventType_t configureSarTriggerEvents0136VcEventData;
      ::DataTypes::NS_REC_vechicleInformation0400VcEventType_t::REC_vechicleInformation0400VcEventType_t vechicleInformation0400VcEventData;


      /* TODO these values shall come from persistency interface in next sprint 
              param storage class shall have an object of persistency interface class for reading these values from 
              permanent storage */
      
      /*##### vechicleInformation0400VcEventData #### */
      vechicleInformation0400VcEventData.body_style     = 0x3F;
      vechicleInformation0400VcEventData.veh_line       = 0x3F;
      vechicleInformation0400VcEventData.amg_type       = 0xFF;
      vechicleInformation0400VcEventData.guard_lvl_b4   = 0x0;
      vechicleInformation0400VcEventData.reserved       = 0x0;
      vechicleInformation0400VcEventData.guard_lvl_b7   = 0x0;
      vechicleInformation0400VcEventData.hybrid_avl     = 0x0;
      vechicleInformation0400VcEventData.plugin_hybrid_avl = 0x0;
      vechicleInformation0400VcEventData.veh_backdoors_avl = 0x0;

      /*##### activateSarStorage0131VcEventData #### */
      activateSarStorage0131VcEventData.sarDataStorageStatus = 0x1;

      /*##### configureSarTriggerEvents0136VcEventData #### */
      configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1 = 0x0;
      configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2 = 0x0;

      siX6aaCnfgMngrServiceReservedSkeletonServer->Ev_activateSarStorage0131VcEvent.Send(activateSarStorage0131VcEventData);
      siX6aaCnfgMngrServiceReservedSkeletonServer->Ev_configureSarTriggerEvents0136VcEvent.Send(configureSarTriggerEvents0136VcEventData);
      siX6aaCnfgMngrServiceReservedSkeletonServer->Ev_vechicleInformation0400VcEvent.Send(vechicleInformation0400VcEventData);
    }

  } else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

/*!
 * \internal
 * - #10 empty the set of signals.
 * - #20 add SIGTERM to signal set.
 * - #21 add SIGINT to signal set.
 * - #30 loop until SIGTERM or SIGINT signal received.
 * - #35 request application exit.
 * \endinternal
 */
void VcCnfgMngrServer::SignalHandlerThread() {
  sigset_t signal_set;

  /* #10 empty the set of signals. */
  if (0 != sigemptyset(&signal_set)) {
    log_.LogFatal([](ara::log::LogStream& s) { s << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo could not empty signal set."; });
    ara::core::Abort("Empty signal set failed.");
  }
  /* #20 add SIGTERM to signal set. */
  if (0 != sigaddset(&signal_set, SIGTERM)) {
    log_.LogFatal([](ara::log::LogStream& s) { s << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo cannot add signal to signalset: SIGTERM"; });
    ara::core::Abort("Adding SIGTERM failed.");
  }
  /* #21 add SIGINT to signal set. */
  if (0 != sigaddset(&signal_set, SIGINT)) {
    log_.LogFatal([](ara::log::LogStream& s) { s << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo cannot add signal to signalset: SIGINT"; });
    ara::core::Abort("Adding SIGINT failed.");
  }

  /* #30 loop until SIGTERM or SIGINT signal received. */
  int sig{-1};

  do {
    if (0 != sigwait(&signal_set, &sig)) {
      log_.LogFatal([](ara::log::LogStream& s) { s << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo called sigwait() with invalid signalset"; });
      ara::core::Abort("Waiting for SIGTERM or SIGINT failed.");
    }
    log_.LogInfo([&sig](ara::log::LogStream& s) { s << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo received signal: " << sig << "."; });

    if ((sig == SIGTERM) || (sig == SIGINT)) {
      log_.LogInfo([](ara::log::LogStream& s) {
        s << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo received SIGTERM or SIGINT, requesting application shutdown.";
      });
      if (!exit_requested) {
        /* #35 request application exit. (SignalHandler initiate the shutdown!) */
        exit_requested = true;
      }
      terminated_by_signal = true;
    }
  } while (!exit_requested);
}

/*!
 * \internal
 * - #10 verify which state should be reported
 * -    #15 invalid application state detected
 * - #20 check if invalid application state was detected.
 * - #30 send application state
 * -    #35 application state could not be set.
 * \endinternal
 */
void VcCnfgMngrServer::ReportApplicationState(ara::exec::ApplicationState application_state) {
  std::string application_state_string = "";
  bool error_occurred = false;

  /* #10 verify which state should be reported  */
  if (application_state == ara::exec::ApplicationState::kRunning) {
    application_state_string = "kRunning";
  } else if (application_state == ara::exec::ApplicationState::kTerminating) {
    application_state_string = "kTerminating";
  } else {
    /* #15 invalid application state detected */
    error_occurred = true;
    log_.LogError() << "ReportApplicationState called with an invalid application state: " << application_state_string;
  }

  /* #20 check if invalid application state was detected. */
  if (!error_occurred) {
    log_.LogDebug() << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo is reporting Application state " << application_state_string;

    /* #30 send application state */
    if (application_client.ReportApplicationState(application_state) == ara::exec::ApplicationReturnType::kSuccess) {
      log_.LogDebug() << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo reported Application state " << application_state_string << " successfully";
    } else {
      /* #35 application state could not be set. */
      log_.LogError() << "siX6aaCnfgMngrServiceReservedSkeletonServer skeleton demo could not report the Application state " << application_state_string;
    }
  }
}

}  // namespace application
