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
  if (false == vc_consumer_.FindService()) {
    GetLogger().LogFatal() << "DummySWC1 could not find variant coding service, "
                              "timeout occured:";
  }
  if (false == vc_consumer_.SubscribeToEvents()) {
    GetLogger().LogFatal()
      << "DummySWC1 could not find subscribe to variant coding events:";
  }
}

DummySwc1Application::~DummySwc1Application() {
  exit_requested_ = true;

  /* Unsubscribe from service events */
  vc_consumer_.UnsubscribeFromEvents();

  GetLogger().LogInfo() << "DummySWC1 shutdown initiated.";

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

  GetLogger().LogInfo() << "DummySWC1 finished shutdown.";
}

std::int8_t DummySwc1Application::Run() {
  std::int8_t ret{EXIT_SUCCESS};

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    GetLogger().LogInfo() << "DummySWC1 application started";


    while (!exit_requested_) {
      am_->wait();
      GetLogger().LogInfo() << "DummySWC1 Running, hearbeat:"
                             << am_->getCycle();
    }

  } else {
    ret = EXIT_FAILURE;
  }

  this->ReportApplicationState(ara::exec::ApplicationState::kTerminating);

  return ret;
}

}  // namespace application
