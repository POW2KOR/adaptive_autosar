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
Application::Application() : ApplicationBase("avatar_router_2") {

  /* Offer Roller Blinder Rear service */
  roller_blinder_service_provider_.OfferService();
  log_.LogInfo() << "Roller Blinder Rear service Offered.";
}

Application::~Application() {
  /* Stop offered service */
  roller_blinder_service_provider_.StopOfferService();
}

std::int8_t Application::Run() {
  std::int8_t ret{EXIT_SUCCESS};
  int counter = 0;

  ::DataTypes::TypeRef::c02_Idle_Opn_Cls_SNA data;

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    log_.LogInfo() << "avater_router application started";

    while (!exit_requested_) {
      am_->wait();
      log_.LogDebug() << "Running in cycle " << am_->getCycle();

       if (++counter % 10 == 0) {

         data = 10;
          roller_blinder_service_provider_.RB_R_Rq_HU_ST3.Send(data);
          log_.LogInfo() << "ECU_Stat_CIVIC_M_P_Service_ST3 data sent ...";
       }
    }
  }else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

}  // namespace application
