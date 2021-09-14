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
#include "application.h"

namespace application {


/*!
 * \brief Initialize application.
 */
Application::Application() : ApplicationBase("CIVIC_M_P_ST35") {

  /* Offer Roller Blinder Rear service on vlan10*/
  roller_blinder_service_provider_.OfferService();
  log_.LogInfo() << "Roller Blinder Rear service Offered.";

  /* Find Roller Blinder service on vlan210*/
  roller_blinder_service_consumer_.CheckAndStopFindService();
  log_.LogInfo() << "find service Roller Blinder invoked.";
  roller_blinder_service_consumer_.SubscribeToEvents();

  /* Find Sunroof Service on vlan10 */
  sunroof_roller_service_app_proxy_.CheckAndStopFindService();
  log_.LogInfo() << "find service Sunroof Roller invoked.";
  sunroof_roller_service_app_proxy_.SubscribeToEvents();

  /* Offer Sunroof Roller Service on Vlan210 */
  sunroof_roller_provider_.OfferService();
  log_.LogInfo() << "Sunroof Roller service Offered.";

}

Application::~Application() {
  /* Stop offered service */
  roller_blinder_service_provider_.StopOfferService();
  sunroof_roller_provider_.StopOfferService();

  /* Unsubscribe from service events */
  roller_blinder_service_consumer_.UnsubscribeFromEvents();
  sunroof_roller_service_app_proxy_.UnsubscribeFromEvents();
}

std::int8_t Application::Run() {
  std::int8_t ret{EXIT_SUCCESS};
  int counter = 0;

  ::DataTypes::TypeRef::c02_Idle_Opn_Cls_SNA data;

  i3::services::common::sunroofDataType sunroof_data;

  if (!has_initialization_failed_) {

    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    log_.LogInfo() << "CIVIC_M_P_ST35 application started";

    while (!exit_requested_) {
      am_->wait();
      log_.LogDebug() << "Running in cycle " << am_->getCycle();

      /* Verify service has been found on vlan 210 for Roller Blinder Rear*/
      if(roller_blinder_service_consumer_.IsServiceFound() && roller_blinder_service_consumer_.IsSubscribed()) {
          //Copying the values received to provided it later
          data = roller_blinder_service_consumer_.data_;
      }else {
        /* Keep searching for service without blocking the application */
        if(!roller_blinder_service_consumer_.IsServiceFound()) {
          roller_blinder_service_consumer_.CheckAndStopFindService();
        }
        /* Subscribe to SI SpeedLimiter events */
        if(!roller_blinder_service_consumer_.IsSubscribed()) {
          roller_blinder_service_consumer_.SubscribeToEvents();
        }
      }

       /* Verify service has been found on vlan 10 for Sunroof roller*/
      if(sunroof_roller_service_app_proxy_.IsServiceFound() && sunroof_roller_service_app_proxy_.IsSubscribed()) {
          //Copying the values received to provided it later
          sunroof_data = sunroof_roller_service_app_proxy_.data_;
      }else {
        /* Keep searching for service without blocking the application */
        if(!sunroof_roller_service_app_proxy_.IsServiceFound()) {
          sunroof_roller_service_app_proxy_.CheckAndStopFindService();
        }
        /* Subscribe to SI SpeedLimiter events */
        if(!sunroof_roller_service_app_proxy_.IsSubscribed()) {
          sunroof_roller_service_app_proxy_.SubscribeToEvents();
        }
      }

    if (++counter % 10 == 0){

      //Read the data stored 
      // @TODO : This operation has to be atomic. We have to revisit 
      // this implementation which will depend on frequency of read
      // and write. But for now It should be ok till tested
      data = roller_blinder_service_consumer_.data_;
      
      roller_blinder_service_provider_.RB_R_Rq_HU_ST3.Send(data);
      log_.LogInfo() << "RB_R_Rq_HU_ST3 data sent ...";

      sunroof_roller_provider_.TSSR_UI_Ctrl_Rq_ST3.Send(sunroof_data);
      log_.LogInfo() << "TSSR_UI_Ctrl_Rq_ST3 data sent ...";

      }
    }
  }else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

}  // namespace application
