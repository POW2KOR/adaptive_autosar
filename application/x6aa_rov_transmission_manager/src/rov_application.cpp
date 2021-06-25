/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!
 *      \file
 *      \brief  Main class representing the application.
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "rov_application.h"

namespace application {


/*!
 * \brief Initialize application.
 */
RovApplication::RovApplication() : ApplicationBase("rov_tx_manager") {

  /* Find SI SpeedLimiter service */
  log_.LogInfo() << "Start searching for SI_Speedlimiter service";
  si_speedlimiter_.FindService();

  /* Subscribe to SI SpeedLimiter events */
  si_speedlimiter_.SubscribeToEvents();

  /* Offer SI SuppFunctions service */
  si_suppfunctions_server_.OfferService();
  log_.LogInfo() << "SI_SuppFunctions_MPC_Service_ST3 service offered";

}

RovApplication::~RovApplication() {
  exit_requested_ = true;

  /* Unsubscribe from service events */
  si_speedlimiter_.UnsubscribeFromEvents();

  /* Stop offered service */
  si_suppfunctions_server_.StopOfferService();

  log_.LogInfo() << "rov_tx_manager shutdown initiated.";

  if (signal_handler_thread_.native_handle() != 0) {
    /* #10 Check if exit was requested by sending SIGTERM or SIGINT. */
    if (!terminated_by_signal_) {
      /* #15 Terminate the signal handler thread to shutdown. */
      if (0 != pthread_kill(static_cast<pthread_t>(signal_handler_thread_.native_handle()), SIGTERM)) {
        log_.LogError() << "Invalid signal!";
      }
    } else {
      log_.LogDebug() << "SIGINT or SIGTERM had been received and had been handled";
    }
  } else {
    log_.LogError() << "Thread ID = 0";
  }

  /* #20 Wait till all threads have joined. */
  if (signal_handler_thread_.joinable()) {
    signal_handler_thread_.join();
  }

  log_.LogInfo() << "rov_tx_manager finished shutdown.";
}

std::int8_t RovApplication::Run() {
  std::int8_t ret{EXIT_SUCCESS};
  int counter = 0;
  ::DataTypes::NS_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt::
    REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt cam_sensor_data;

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    log_.LogInfo() << "rov_tx_manager application started";

    std::shared_ptr<ActivationManagerBase> am_(new ActivationManagerTimer(std::chrono::milliseconds(500)));

    while (!exit_requested_) {
      am_->wait();
      log_.LogDebug() << "Running in cycle " << am_->getCycle();
      ara::core::Future<services::ns_speedlimiter::proxy::methods::Meth_GetCapabilities::Output> min_speed_limit;
      /* Verify service has been found */
      if(si_speedlimiter_.IsServiceFound() && si_speedlimiter_.IsSubscribed()) {

        // TODO write code for methods for SI_SpeedLimiter service

      } else {
        /* Keep searching for service without blocking the application */
        if(!si_speedlimiter_.IsServiceFound()) {
          si_speedlimiter_.FindService();
        }

        /* Subscribe to SI SpeedLimiter events */
        if(!si_speedlimiter_.IsSubscribed()) {
          si_speedlimiter_.SubscribeToEvents();
        }
      }

      if (++counter % 10 == 0) {
        /* Send out data for  SI_SuppFunctions_MPC_Service_ST3 */
        cam_sensor_data.CamSensSoil_CMS_IconDisp_Rq_MPC_ST3 = true;
        cam_sensor_data.CamSensSoil_IHC_IconDisp_Rq_MPC_ST3 = true;
        cam_sensor_data.CamSensSoil_LDP_IconDisp_Rq_MPC_ST3 = true;
        cam_sensor_data.CamSensSoil_MsgDisp_Rq_MPC_ST3 = true;
        cam_sensor_data.CamSensSoil_TSA_IconDisp_Rq_MPC_ST3 = true;

        si_suppfunctions_server_.Ev_CamSensSoil_MPC_ST3.Send(cam_sensor_data);
        log_.LogInfo() << "Ev_CamSensSoil_MPC_ST3 data sent ...";
      }
    }

  } else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

}  // namespace application
