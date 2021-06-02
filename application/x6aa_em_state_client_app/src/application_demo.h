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
 *        \brief  A demo adaptive application to the execution management.
 *
 *      \details  Handles signals, reports its application states, uses the failure handler client.
 *
 *********************************************************************************************************************/

#ifndef EXAMPLE_EM_EXAMPLE_APP_SRC_APPLICATION_DEMO_H_
#define EXAMPLE_EM_EXAMPLE_APP_SRC_APPLICATION_DEMO_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "ara/core/optional.h"
#include "ara/log/logging.h"

#include "ara/exec/application_client.h"
#include "ara/exec/state_client.h"

#include "failure_handler.h"

namespace application_demo {

constexpr uint_least8_t kNumOfThreads = 2; /*!< \brief Number of Threads used in AdaptiveApplication. */

/*!
 * \brief Main class representing the application
 */
class AdaptiveApplication {
 public:
  AdaptiveApplication();
  /*!
   * \brief Constructor of the Adaptive Application
   *
   * \param is_state_client Inidicator if the application should work as machine state client or not
   */
  explicit AdaptiveApplication(bool is_state_client);
  virtual ~AdaptiveApplication() = default;

  /*!
   * \brief Starts the application.
   */
  void Start();

 protected:
  /*!
   * \brief Data Type containing the state to be saved across iterations of a cyclic task.
   */
  typedef struct {
    int my_data; /**< data */
  } PeriodicWorkStateType;

  /*!
   * \brief Lifecycle Method for Initialization.
   */
  void Initialize();

  /*!
   * \brief Lifecycle Methods for Run Mode.
   */
  void Run();

  /*!
   * \brief Lifecycle Methods for Shutdown.
   */
  void Shutdown();

 private:
  /*!
   * \brief Member to report the application state to the Execution Management.
   */
  ara::exec::ApplicationClient application_client_;

  /*!
   * \brief Member to report the machine state to the Execution Management.
   */
  ara::core::Optional<ara::exec::StateClient> state_client_;

  /*!
   * \brief Flag to identify whether the application was requested to terminate, i.e., has received a SIGTERM
   */
  std::atomic_bool exit_requested_;

  /*!
   * \brief Vector to store all threads spawned by this application.
   */
  std::vector<std::thread> threads_;

  /*!
   * \brief Inidicator if the application should work as machine state client or not
   */
  bool is_state_client_;

  /*!
   * \brief Logging context
   */
  ara::log::Logger& log_;

  /*!
   * \brief Entry point of the thread receiving signals from the execution manager
   */
  void SignalHandlerThread();

  /*!
   * \brief Entry point of a thread that executed periodic work.
   */
  void PeriodicThread();

  /*!
   * \brief Actual workload to be executed periodically. The parameter contains the state to be preserved across
   * iterations.
   */
  void PeriodicWork(PeriodicWorkStateType& state);

  /*! \brief Instance of failure handler */
  FailureHandler failure_handler_;
};

}  // namespace application_demo

#endif  // EXAMPLE_EM_EXAMPLE_APP_SRC_APPLICATION_DEMO_H_
