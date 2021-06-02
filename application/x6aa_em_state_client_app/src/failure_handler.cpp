/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file
 *        \brief  See failure_handler.h
 *********************************************************************************************************************/

#include "failure_handler.h"
#include "ara/exec/result.h"

namespace application_demo {

FailureHandler::FailureHandler(std::atomic_bool &exit_requested)
    : ara::exec::failure_handler_client::CallbackInterface(),
      log_{ara::log::CreateLogger("EMDA", "Logging context for the EXEC Demo App FailureClient")},
      failure_handler_client_{*this},
      process_monitoring_ready_{false},
      exit_requested_{exit_requested} {}

void FailureHandler::Initialize() {
  ara::core::Result<void> connect_result{failure_handler_client_.Connect()};
  if (!connect_result.HasValue()) {
    log_.LogFatal() << "FailureHandler::FailureHandler: Connect to execution manager daemon failed.";
    std::terminate();
  }
  while (!process_monitoring_ready_) {
    failure_handler_client_.WaitForEvents(std::chrono::milliseconds(100));
  }
}

void FailureHandler::PeriodicThread() {
  while (!exit_requested_) {
    failure_handler_client_.WaitForEvents(std::chrono::milliseconds(100));
  }
}

void FailureHandler::LogProcessStates() {
  ara::core::Result<ara::exec::failure_handler_client::ProcessList const &> process_list{
      failure_handler_client_.GetProcessList()};
  if (process_list.HasValue()) {
    ara::exec::failure_handler_client::ProcessList const &pl{process_list.Value()};
    for (ara::exec::failure_handler_client::ProcessListEntry process : pl) {
      log_.LogDebug() << "FailureHandler::CheckProcessStates: process = " << process.short_name_path_
                      << ", current state = "
                      << ((process.state_ == ara::exec::failure_handler_client::FailureHandlerProcessState::kRunning)
                              ? "Running"
                              : "Not Running");
    }
  }
}

void FailureHandler::OnProcessMonitoringReady() noexcept {
  log_.LogDebug() << "FailureHandler::OnProcessMonitoringReady";
  process_monitoring_ready_ = true;
}

void FailureHandler::OnProcessTerminated(const ara::core::StringView short_name_path,
                                         ara::exec::failure_handler_client::ExitCodeType exit_code) noexcept {
  log_.LogInfo() << "FailureHandler::OnProcessTerminated: process = " << short_name_path
                 << ", exit_code = " << exit_code;
}

void FailureHandler::OnError(ara::core::ErrorCode error_code) noexcept {
  log_.LogFatal() << "FailureHandler::OnError " << error_code;
  /* Instead of terminating a real application can try to destroy and re-instantiate the FailureHandlerClient object. */
  std::terminate();
}

void FailureHandler::OnProcessStateChange(const ara::exec::failure_handler_client::ProcessListEntry &process) noexcept {
  log_.LogInfo() << "FailureHandler::OnProcessStateChange: process = " << process.short_name_path_ << ", new state = "
                 << ((process.state_ == ara::exec::failure_handler_client::FailureHandlerProcessState::kRunning)
                         ? "Running"
                         : "Not Running");
}

}  // namespace application_demo
