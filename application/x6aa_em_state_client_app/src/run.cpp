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
/*!        \file  example/em_example_app/src/run.cpp
 *        \brief  -
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <unistd.h>
#include <climits>
#include <string>

#include "application_demo.h"
#include "ara/core/initialization.h"
#include "ara/log/logging.h"

/*!
 * \brief The main function for the demo application.
 */
int main(int argc, char *argv[]) {
  char cwd[PATH_MAX];

  /* Init basic software and instantiate ExampleApp. */
  ara::core::Result<void> ara_init_result{ara::core::Initialize()};
  if (!ara_init_result) {
    ara::core::ErrorCode ec{ara_init_result.Error()};
    std::cerr << "EM Example App: Failed to initialize basic software. Error: " << ec.Message() << "\n";
    std::cerr << "EM Example App: More details: " << ec.UserMessage() << "\n";
    std::cerr.flush();
    ara::core::Abort("EM Example App: Failed to initialize basic software.");
  }

  ara::log::Logger &log_{ara::log::CreateLogger("EMDA", "Logging context for the EXEC Demo App run.cpp")};

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    log_.LogDebug([&](ara::log::LogStream &s) { s << "main: Current working dir: " << cwd; });
  }
  bool is_msc = false;
  std::string msc_option("msc");
  log_.LogDebug([&](ara::log::LogStream &s) { s << "main: Have " << argc << " arguments:"; });
  for (int i = 0; i < argc; ++i) {
    log_.LogDebug([&](ara::log::LogStream &s) { s << "main: argument " << i << ": " << argv[i]; });
    if (argv[i] == msc_option) {
      is_msc = true;
    }
  }

  application_demo::AdaptiveApplication app(is_msc);
  app.Start();

  /* Deinit basic software */
  ara::core::Result<void> ara_deinit_result{ara::core::Deinitialize()};
  if (!ara_deinit_result) {
    ara::core::ErrorCode ec{ara_deinit_result.Error()};
    std::cerr << "EM Example App: ara::core::Deinitialize() failed!";
    std::cerr << "EM Example App: Result contains: " << ec.Message() << ", " << ec.UserMessage();
    std::cerr.flush();
  }
}
