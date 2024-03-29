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
#include "dummy_swc1_application.h"

namespace application {

/*!
 * \brief Initialize application.
 */
DummySwc1Application::DummySwc1Application() : ApplicationBase("DummySWC1",1000) {

  /* Reporting fatal below as only purpose of this application is
   * consume vatiant coding data and if services are not found then this application
   * will endup with fatal error. This can be changed later on*/
  if (!vc_consumer_.FindService()) {
    log_.LogError() << "DummySWC1 could not find variant coding service, "
                              "timeout occured:";
  }
  if (!vc_consumer_.SubscribeToEvents()) {
    log_.LogError()
      << "DummySWC1 could not find subscribe to variant coding events:";
  }
}

DummySwc1Application::~DummySwc1Application() {
  /* Unsubscribe from service events */
  vc_consumer_.UnsubscribeFromEvents();
}

std::int8_t DummySwc1Application::Run() {
  std::int8_t ret{EXIT_SUCCESS};

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    log_.LogInfo() << "DummySWC1 application started";


    while (!exit_requested_) {
      am_->wait();
      log_.LogInfo() << "DummySWC1 Running, hearbeat:"
                             << am_->getCycle();
    }

  } else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

}  // namespace application
