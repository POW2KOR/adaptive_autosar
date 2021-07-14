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

  /* Offer Config Manager Service Reserved */
  log_.LogInfo() << "Skeleton siX6aaCnfgMngrServiceReservedSkeleton service offered!!";
  service_reserved_server_.OfferService();

  /* Find SSA Client service and subscribe */
  if (!ssa_client_.FindService()) {
    /* TODO: take action */
  }
  if (!ssa_client_.SubscribeToEvents()) {
    /* TODO: take action */
  }

  /* Find ExtVehicleConfig service */
  log_.LogInfo() << "Start searching for ExtVehicleConfig service";
  ext_vehicle_config_client_.CheckAndStopFindService();

  /* Subscribe to ExtVehicleConfig events */
  ext_vehicle_config_client_.SubscribeToEvents();
}

CnfgMngrApplication::~CnfgMngrApplication() {
  /* Stop offering services */
  service_reserved_server_.StopOfferService();

  /* Unsubscribe from service events */
  ssa_client_.UnsubscribeFromEvents();
  ext_vehicle_config_client_.UnsubscribeFromEvents();
}

std::int8_t CnfgMngrApplication::Run() {
  std::int8_t ret{EXIT_SUCCESS};

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    log_.LogInfo() << "ConfigManager application started";

    application::VariantCodingApp::SingletonPersistentMemAccessor* memAccessor
      = application::VariantCodingApp::SingletonPersistentMemAccessor::getInstance();

    while (!exit_requested_) {
      am_->wait();
      log_.LogDebug() << "Running in cycle " << am_->getCycle();

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
        log_.LogError() << resultFor131Vc.Error().Message();
      }
      if (resultFor136Vc.HasValue()) {
        service_reserved_server_.Ev_configureSarTriggerEvents0136VcEvent.Send(
            resultFor136Vc.Value());
      } else {
        log_.LogError() << resultFor136Vc.Error().Message();
      }
      if (resultFor400Vc.HasValue()) {
        service_reserved_server_.Ev_vechicleInformation0400VcEvent.Send(
            resultFor400Vc.Value());
      } else {
        log_.LogError() << resultFor400Vc.Error().Message();
      }

    }

  } else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

}  // namespace application
