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
/**        \file  DiagnosticManagerDeamon_Executable/src/ara/core/initialization.cpp
 *        \brief  Provides ara::core::Initialize() and ara::core::Deinitialize().
 *
 *      \details  Provides the global initialization and shutdown functions that initialize resp. deinitialize data
*                 structures and threads of the AUTOSAR Runtime for Adaptive Applications (ARA).
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GENERATOR INFORMATION
 *  -------------------------------------------------------------------------------------------------------------------
 *    Generator Name: amsr_applicationbase_init_deinit
 *         Commit ID: e9cceb85f7dbddd50606a552afd41f2be3fe5766
 *********************************************************************************************************************/

#include <cstdlib>
#include <string>

#include "amsr/application_base/initialization_error_domain.h"
#include "amsr/generic/write_std_stream.h"
#include "amsr/log/internal/lifecycle.h"
#include "amsr/socal/internal/lifecycle.h"
#include "ara/core/initialization.h"
#include "vac/internal/lifecycle.h"

namespace ara {
namespace core {
namespace details {

bool g_ara_core_initialized{false};
bool g_ara_core_deinitialized{false};

}  // namespace details

/*!
 * \brief Returns a Result that contains an error code if the pre-conditions for initialization are not met.
 */
static ara::core::Result<void> CheckPreCondition() {
  ara::core::Result<void> res{amsr::application_base::InitializationErrc::kWrongSequence};

  if ((!ara::core::details::g_ara_core_initialized) && (!ara::core::details::g_ara_core_deinitialized)) {
    res.EmplaceValue();
  }

  return res;
}

/*!
 * \brief Registers a de-initialization check that is to be made at normal program termination.
 */
static void RegisterAtExit() {
  static_cast<void>(std::atexit([] {
    if ((ara::core::details::g_ara_core_initialized) && (!ara::core::details::g_ara_core_deinitialized)) {
      static_cast<void>(
          amsr::generic::WriteToStderr("Application terminated without proper call to ara::core::Deinitialize()!\n"));
    }
  }));
}

}  // namespace core
}  // namespace ara

ara::core::Result<void> ara::core::Initialize() noexcept {
  std::string const ara_com_json_file_path{"./etc/com_application.json"};
  return CheckPreCondition()
      .AndThen([]() { return vac::internal::InitializeComponent(); })
      .AndThen([]() { return amsr::log::internal::InitializeComponent(); })
      .AndThen(
          [&ara_com_json_file_path]() { return amsr::socal::internal::InitializeComponent(ara_com_json_file_path); })

      .Inspect([]() {
        ara::core::details::g_ara_core_initialized = true;
        RegisterAtExit();
      })
      .InspectError([](ara::core::ErrorCode const& error) {
        static_cast<void>(amsr::generic::WriteToStderr("ara::core::Initialize() failed! Result contains: "));
        static_cast<void>(amsr::generic::WriteToStderr(error.Message()));
        static_cast<void>(amsr::generic::WriteToStderr(", "));
        static_cast<void>(amsr::generic::WriteToStderr(error.UserMessage()));
      });
}

ara::core::Result<void> ara::core::Deinitialize() noexcept {
  ara::core::Result<void> res{amsr::application_base::InitializationErrc::kWrongSequence};

  if ((ara::core::details::g_ara_core_initialized) && (!ara::core::details::g_ara_core_deinitialized)) {
    // when Initialize() was called before, deinitialize; otherwise return kWrongSequence

    res = amsr::socal::internal::DeinitializeComponent()
              .AndThen([]() { return amsr::log::internal::DeinitializeComponent(); })
              .AndThen([]() { return vac::internal::DeinitializeComponent(); })
              .Inspect([]() { ara::core::details::g_ara_core_deinitialized = true; })
              .InspectError([](ara::core::ErrorCode const& error) {
                static_cast<void>(amsr::generic::WriteToStderr("ara::core::Deinitialize() failed! Result contains: "));
                static_cast<void>(amsr::generic::WriteToStderr(error.Message()));
                static_cast<void>(amsr::generic::WriteToStderr(", "));
                static_cast<void>(amsr::generic::WriteToStderr(error.UserMessage()));
              });
  }

  return res;
}
