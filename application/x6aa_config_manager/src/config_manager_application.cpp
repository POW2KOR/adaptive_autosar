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
#include "config_manager_application.h"

namespace application {

/*!
 * \brief Initialize application.
 */
CnfgMngrApplication::CnfgMngrApplication() : ApplicationBase("ConfigManager",5000) {
  int ret_value = 0;

  /* Offer Config Manager Service Reserved */
  GetLogger().LogInfo() << "Skeleton siX6aaCnfgMngrServiceReservedSkeleton service offered!!";
  service_reserved_server_.OfferService();

  /* Find SSA Client service and subscribe */
  ret_value = ssa_client_.FindService();

  if (EXIT_FAILURE == ret_value) {
    /* TODO: take action */
  }
  ret_value = ssa_client_.SubscribeToEvents();
  if (EXIT_FAILURE == ret_value) {
    /* TODO: take action */
  }

  /* Find SI ExtVehicleConfig service */
  GetLogger().LogInfo() << "Start searching for ExtVehicleConfig service";
  ext_vehicle_config_client_.CheckAndStopFindService();

  /* Subscribe to SI ExtVehicleConfig events */
  ext_vehicle_config_client_.SubscribeToEvents();
}

CnfgMngrApplication::~CnfgMngrApplication() {
  exit_requested_ = true;

  /* Stop offering services */
  service_reserved_server_.StopOfferService();

  /* Unsubscribe from service events */
  ssa_client_.UnsubscribeFromEvents();
  ext_vehicle_config_client_.UnsubscribeFromEvents();

  GetLogger().LogInfo() << "ConfigManager shutdown initiated.";

  if (signal_handler_thread_.native_handle() != 0) {
    /* #10 Check if exit was requested by sending SIGTERM or SIGINT. */
    if (!terminated_by_signal_) {
      /* #15 Terminate the signal handler thread to shutdown. */
      if (0 != pthread_kill(static_cast<pthread_t>(signal_handler_thread_.native_handle()), SIGTERM)) {
        GetLogger().LogError() << "Invalid signal!";
      }
    } else {
      GetLogger().LogDebug() << "SIGINT or SIGTERM had been received and had been handled";
    }
  } else {
    GetLogger().LogError() << "Thread ID = 0";
  }

  /* #20 Wait till all threads have joined. */
  if (signal_handler_thread_.joinable()) {
    signal_handler_thread_.join();
  }

  GetLogger().LogInfo() << "ConfigManager finished shutdown.";
}

std::int8_t CnfgMngrApplication::Run() {
  std::int8_t ret{EXIT_SUCCESS};

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    GetLogger().LogInfo() << "ConfigManager application started";

    application::VariantCodingApp::SingletonPersistentMemAccessor* memAccessor
      = application::VariantCodingApp::SingletonPersistentMemAccessor::getInstance();

    while (!exit_requested_) {
      am_->wait();
      GetLogger().LogDebug() << "Running in cycle " << am_->getCycle();

      /**************************************************/
      /* Verify ExtVehicleConfig service has been found */
      /**************************************************/
      if(!ext_vehicle_config_client_.IsServiceFound()) {
        /* Keep searching for service without blocking the application */
        ext_vehicle_config_client_.CheckAndStopFindService();
      } else {
        /* Subscribe to SI ExtVehicleConfig events */
        if(!ext_vehicle_config_client_.IsSubscribed()) {
          ext_vehicle_config_client_.SubscribeToEvents();
        }
      }

      /********************************/
      /* Send out variant coding data */
      /********************************/
      ara::core::Result<activateSarStorage0131VcEventDataType> resultFor131Vc{
        memAccessor->ReadDataForActivateSarStorage0131VcEvent()};
      ara::core::Result<configureSarTriggerEvents0136VcEventDataType> resultFor136Vc{
        memAccessor->ReadDataForConfigureSarTriggerEvents0136VcEvent()};
      ara::core::Result<vechicleInformation0400VcEventDataType> resultFor400Vc{
        memAccessor->ReadDataForVechicleInformation0400VcEvent()};

      if (resultFor131Vc.HasValue()) {
        service_reserved_server_.Ev_activateSarStorage0131VcEvent.Send(
            resultFor131Vc.Value());
      } else {
        GetLogger().LogError() << resultFor131Vc.Error().Message();
      }
      if (resultFor136Vc.HasValue()) {
        service_reserved_server_.Ev_configureSarTriggerEvents0136VcEvent.Send(
            resultFor136Vc.Value());
      } else {
        GetLogger().LogError() << resultFor136Vc.Error().Message();
      }
      if (resultFor400Vc.HasValue()) {
        service_reserved_server_.Ev_vechicleInformation0400VcEvent.Send(
            resultFor400Vc.Value());
      } else {
        GetLogger().LogError() << resultFor400Vc.Error().Message();
      }

    }

  } else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

}  // namespace application
