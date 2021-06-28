
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
/*!        \file  application_base.h
 *        \brief  Base class for all the applications.
 *
 *      \details  -
 *
 *********************************************************************************************************************/

#ifndef APPLICATION_BASE_H_
#define APPLICATION_BASE_H_

#include <csignal>

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/exec/application_client.h"
#include "ara/log/logging.h"
#include "osabstraction/process/process.h"
#include "vac/container/string_literals.h"

#include "activation_manager.h"

/*!
 * \brief Namespace for the example application.
 */
namespace application {

/*!
 * \brief Main class representing the application.
 * \vprivate Example class for component internal use.
 */
class ApplicationBase {
 public:
  /*!
   * \brief Constructor of class ApplicationBase.
   *
   * \param[in] name        Name of the application.
   *                        It is also used as logger and thread names.
   * \param[in] cycle_time, cycle time in milliseconds passed to the
   *                        activation manager, used during run phase.
   *                        Default: 500 msec.
   */
  ApplicationBase(std::string name = "Default app name", int cycle_time = 500);

  /*!
   * \brief Deleted copy constructor
   */
  ApplicationBase(ApplicationBase const&) = delete;

  /*!
   * \brief Default move constructor
   */
  ApplicationBase(ApplicationBase&& other) noexcept = delete;

  /*!
   * \brief Destructor of class ApplicationBase.
   */
  virtual ~ApplicationBase();

  /*!
   * \brief Deleted copy assignment operator
   * \return Reference to application
   */
  ApplicationBase& operator=(ApplicationBase const&) & = delete;

  /*!
   * \brief Default move assignment operator
   * \return Reference to application
   */
  ApplicationBase& operator=(ApplicationBase&& other) & = delete;

  /*!
   * \brief Retrieve the name of the application.
   *
   * \return Name of the application.
   */
  std::string getName(void) const;

  /*!
   * \brief Lifecycle method for run mode.
   * \return Error (Exit) code of application.
   */
  virtual std::int8_t Run();

 protected:

  /*!
   * \brief Start threads given by information in handed over thread information.
   * \param thread_info The thread information array.
   * \return The process id of the started thread.
   * \error TemplateErrc::kThreadCreationFailed Naming the thread after creation has failed.
   */
  ara::core::Result<osabstraction::process::ProcessId> StartSignalHandlerThread();

  /*!
   * \brief Entry point of the thread receiving signals from the execution manager.
   */
  void SignalHandlerThread();

  /*!
   * \brief Reporting the given application state
   * \param application_state The application state to report
   */
  void ReportApplicationState(ara::exec::ApplicationState application_state);

  /*!
   * \brief Logger instance.
   */
  ara::log::Logger& GetLogger();

  /*!
   * \brief ApplicationClient instance
   */
  ara::exec::ApplicationClient application_client_;

  /*!
   * \brief Signal handler thread.
   */
  std::thread signal_handler_thread_{};

  /*!
   * \brief Flag to exit the application.
   */
  std::atomic_bool exit_requested_{false};

  /*!
   * \brief Flag to mark if the application exit was triggered by a signal.
   */
  std::atomic_bool terminated_by_signal_{false};

  /*!
   * \brief Flag to indicate initialization error. Only used in main thread.
   */
  bool has_initialization_failed_{false};

  /*!
   * \brief Name of the application.
   */
  std::string name_;

  /*!
   * \brief Cycle time for the activation manager
   */
  int cycle_time_;

  /*!
   * \brief Activation manager instance.
   */
  // TODO: Enable class member
  //std::shared_ptr<ActivationManagerBase> am_;

};

}  // namespace application

#endif  // APPLICATION_BASE_H_
