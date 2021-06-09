/*!********************************************************************************************************************
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
 *        \brief  Defines the error domain for the Template Component.
 *
 *********************************************************************************************************************/
#include "update_app_demo_error_domain.h"

namespace application {

/*!
 * \brief Array of error domain message strings.
 */
constexpr std::array<ara::core::ErrorDomain::StringType, 5> kMessages{
    {"Unknown error.", "Error during creation of a thread."}};

UpdateAppDemoErrorDomain::StringType UpdateAppDemoErrorDomain::Message(ara::core::ErrorDomain::CodeType error_code)
  const noexcept {
  if (static_cast<std::size_t>(error_code) >= kMessages.size()) {
    error_code = 0;
  }
  return kMessages[static_cast<std::size_t>(error_code)];
}

}  // namespace application
