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
 *        \brief  Demonstrates how to use the execution management's failure handler client.
 *********************************************************************************************************************/

#ifndef EXAMPLE_EM_EXAMPLE_APP_SRC_FAILURE_HANDLER_H_
#define EXAMPLE_EM_EXAMPLE_APP_SRC_FAILURE_HANDLER_H_

#include "ara/core/error_code.h"
#include "ara/log/logging.h"

#include "ara/exec/failure_handler_client/callback_interface.h"
#include "ara/exec/failure_handler_client/failure_handler_client.h"

namespace application_demo {

/*!
 * \brief Example implementation of a failure handler using the failure handler client.
 */
class FailureHandler final : public ara::exec::failure_handler_client::CallbackInterface {
 public:
  /*!
   * \brief Constructs a failure handler object.
   * \param exit_requested reference to a flag that indicates when exit is requested.
   */
  explicit FailureHandler(std::atomic_bool &exit_requested);

  FailureHandler(FailureHandler const &) = delete;

  FailureHandler &operator=(FailureHandler const &) = delete;

  FailureHandler(FailureHandler &&) noexcept = delete;

  FailureHandler &operator=(FailureHandler &&) noexcept = delete;

  /*!
   * \brief           Deconstructs this object
   */
  ~FailureHandler() final = default;

  /*!
   * \brief Initialize the failure handler
   * \details Blocks until the IPC connection to the EM process is established and the process monitoring can be
   * started.
   */
  void Initialize();

  /*!
   * \brief Periodic thread that calls the failure clients handle events function.
   */
  void PeriodicThread();

  /*!
   * \brief Gets and logs all process states.
   */
  void LogProcessStates();

  /*!
   * \copydoc ara::exec::failure_handler_client::CallbackInterface::OnProcessMonitoringReady()
   */
  void OnProcessMonitoringReady() noexcept final;

  /*!
   * \copydoc ara::exec::failure_handler_client::CallbackInterface::OnProcessTerminated()
   */
  void OnProcessTerminated(const ara::core::StringView short_name_path,
                           ara::exec::failure_handler_client::ExitCodeType exit_code) noexcept final;

  /*!
   * \copydoc ara::exec::failure_handler_client::CallbackInterface::OnError()
   */
  void OnError(ara::core::ErrorCode error_code) noexcept final;

  /*!
   * \copydoc ara::exec::failure_handler_client::CallbackInterface::OnProcessStateChange()
   */
  void OnProcessStateChange(const ara::exec::failure_handler_client::ProcessListEntry &process) noexcept final;

 private:
  /*! \brief Reference to logger instance */
  ara::log::Logger &log_;
  /*! \brief Instance of the failure handler client */
  ara::exec::failure_handler_client::FailureHandlerClient failure_handler_client_;
  /*! \brief Flag to indicate that process monitoring is ready */
  bool process_monitoring_ready_;
  /*! \brief Flag to indicate exit request */
  std::atomic_bool &exit_requested_;
};

}  // namespace application_demo
#endif  // EXAMPLE_EM_EXAMPLE_APP_SRC_FAILURE_HANDLER_H_
