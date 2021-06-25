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
/*!        \file
 *        \brief  Entry point of the example application.
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <csignal>

#include "ara/core/abort.h"
#include "ara/core/result.h"
#include "ara/core/initialization.h"

#include "dummy_2_application.h"


namespace {
/*!
 * \brief Initializes the signal handling.
 * \return void.
 */
void InitializeSignalHandling() noexcept {
  bool success{true};
  sigset_t signals;

  /* Block all signals except the SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV signals because blocking them will lead to
   * undefined behavior. Their default handling shall not be changed (dependent on underlying POSIX environment, usually
   * process is killed and a dump file is written). Signal mask will be inherited by subsequent threads. */

  success = success && (0 == sigfillset(&signals));
  success = success && (0 == sigdelset(&signals, SIGABRT));
  success = success && (0 == sigdelset(&signals, SIGBUS));
  success = success && (0 == sigdelset(&signals, SIGFPE));
  success = success && (0 == sigdelset(&signals, SIGILL));
  success = success && (0 == sigdelset(&signals, SIGSEGV));
  success = success && (0 == pthread_sigmask(SIG_SETMASK, &signals, nullptr));

  if (!success) {
    ara::core::Abort("InitializeSignalHandling failed.");
  }
}

}  // namespace

/*!
 * \brief Entry Point of the process.
 * \return zero when successfully executed
 */
int main() {
  int return_value = 0;

  /* Initialize signal handling. */
  InitializeSignalHandling();

  /* Initialize ara::core */
  ara::core::Result<void> init_result{ara::core::Initialize()};

  if (!init_result.HasValue()) {
    char const* msg{" x6aa_dummy_2_app ara::core::Initialize() failed."};
    std::cerr << msg << "\nResult contains: " << init_result.Error().Message() << ", "
              << init_result.Error().UserMessage()
              << "\n";
    ara::core::Abort(msg);
  } else {
    /* Create the application object and run it */
    application::Dummy2Application app;
    return_value = app.Run();

    /* Deinitialize ara::core */
    ara::core::Result<void> deinit_result{ara::core::Deinitialize()};

    if (!deinit_result.HasValue()) {
      char const* msg{"ara::core::Deinitialize() failed."};
      std::cerr << msg << "\nResult contains: " << deinit_result.Error().Message() << ", "
                << deinit_result.Error().UserMessage()
                << "\n";
      ara::core::Abort(msg);
    }
  }

  return return_value;
}
