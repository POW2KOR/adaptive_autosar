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

#include <csignal>
#include <cstdio>
#include <string>
#include <thread>
#include <memory>

#include "ara/core/abort.h"
#include "update_app_demo_error_domain.h"
#include "osabstraction/thread/thread.h"
namespace application {

using vac::container::operator""_sv;

/*!
 * \brief Initialize application.
 */
Application::Application() {
  log_.LogInfo() << "Update App demo is initializing...";

  this->StartSignalHandlerThread().InspectError([this](ara::core::ErrorCode const& error) {
    has_initialization_failed_ = true;
    log_.LogFatal() << error.Message() << ". " << error.UserMessage();
  });
}

/*!
 * \brief Update application.
 * \internal
 * - #10 Check if exit was requested by sending SIGTERM or SIGINT.
 * -    #15 Terminate the signal handler thread to Update application.
 * - #20 Wait till all threads have joined.
 * \endinternal
 */
Application::~Application() {
  exit_requested_ = true;

  log_.LogInfo() << "Update App demo Update initiated.";

  if (signal_handler_thread_.native_handle() != 0) {
    /* #10 Check if exit was requested by sending SIGTERM or SIGINT. */
    if (!terminated_by_signal_) {
      /* #15 Terminate the signal handler thread to Update. */
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

  log_.LogInfo() << "Update App demo finished Update.";
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
ara::core::Result<osabstraction::process::ProcessId> Application::StartSignalHandlerThread() {
  /* #10 Create ara::core::Result object. */
  using R = ara::core::Result<osabstraction::process::ProcessId>;

  /* #20 Create thread_name. */
  vac::container::CStringView thread_name = vac::container::CStringView::FromLiteral("ProxySignal", 10);

  /* #30 Start signal handler thread. */
  signal_handler_thread_ = std::thread(&Application::SignalHandlerThread, this);

  /* #40 Create the thread native_handle object. */
  std::thread::native_handle_type const thread_id{(signal_handler_thread_).native_handle()};

  /* #50 Set thread name and return the ara::core::Result object. */
  return osabstraction::thread::SetNameOfThread(thread_id, thread_name)
      .AndThen([]() -> R { return R{osabstraction::process::GetProcessId()}; })
      .OrElse([thread_name, this](ara::core::ErrorCode) -> R {
        log_.LogFatal() << "Naming of thread '" << thread_name << "' failed";
        return R::FromError(UpdateAppDemoErrc::kThreadCreationFailed, "Naming failed.");
      });
}

std::int8_t Application::Run() {
  std::int8_t ret{EXIT_SUCCESS};

  if (!has_initialization_failed_) {
    this->ReportApplicationState(ara::exec::ApplicationState::kRunning);

    log_.LogInfo() << "Update demo application started";

    log_.LogInfo() << "Hello from the other side (Partition B)!!!!!!!!!!!!!";

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
 * -    #35 request application exit.
 * \endinternal
 */
void Application::SignalHandlerThread() {
  sigset_t signal_set;

  /* #10 empty the set of signals. */
  if (0 != sigemptyset(&signal_set)) {
    log_.LogFatal([](ara::log::LogStream& s) { s << "Update App demo could not empty signal set."; });
    ara::core::Abort("Empty signal set failed.");
  }
  /* #20 add SIGTERM to signal set. */
  if (0 != sigaddset(&signal_set, SIGTERM)) {
    log_.LogFatal([](ara::log::LogStream& s) { s << "Update App demo cannot add signal to signalset: SIGTERM"; });
    ara::core::Abort("Adding SIGTERM failed.");
  }
  /* #21 add SIGINT to signal set. */
  if (0 != sigaddset(&signal_set, SIGINT)) {
    log_.LogFatal([](ara::log::LogStream& s) { s << "Update App demo cannot add signal to signalset: SIGINT"; });
    ara::core::Abort("Adding SIGINT failed.");
  }

  /* #30 loop until SIGTERM or SIGINT signal received. */
  int sig{-1};

  do {
    if (0 != sigwait(&signal_set, &sig)) {
      log_.LogFatal([](ara::log::LogStream& s) { s << "Update App demo called sigwait() with invalid signalset"; });
      ara::core::Abort("Waiting for SIGTERM or SIGINT failed.");
    }
    log_.LogInfo([&sig](ara::log::LogStream& s) { s << "Update App demo received signal: " << sig << "."; });

    if ((sig == SIGTERM) || (sig == SIGINT)) {
      log_.LogInfo([](ara::log::LogStream& s) {
        s << "Update App demo received SIGTERM or SIGINT, requesting application Update.";
      });
      if (!exit_requested_) {
        /* #35 request application exit. (SignalHandler initiate the Update!) */
        exit_requested_ = true;
      }
      terminated_by_signal_ = true;
    }
  } while (!exit_requested_);
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
void Application::ReportApplicationState(ara::exec::ApplicationState application_state) {
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
    log_.LogError() << "ReportApplicationState called with an invalid application state: "
                    << ara::core::StringView{application_state_string};
  }

  /* #20 check if invalid application state was detected. */
  if (!error_occurred) {
    log_.LogDebug() << "Update App demo is reporting Application state "
                    << ara::core::StringView{application_state_string};

    /* #30 send application state */
    if (application_client_.ReportApplicationState(application_state) == ara::exec::ApplicationReturnType::kSuccess) {
      log_.LogDebug() << "Update App demo reported Application state "
                      << ara::core::StringView{application_state_string} << " successfully";
    } else {
      /* #35 application state could not be set. */
      log_.LogError() << "Update App demo could not report the Application state "
                      << ara::core::StringView{application_state_string};
    }
  }
}

}  // namespace application
