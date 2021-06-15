
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
 *        \brief Defines the error domain for the Template Component.
 *
 *********************************************************************************************************************/
#ifndef ERROR_DOMAIN_H_
#define ERROR_DOMAIN_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "vac/language/throw_or_terminate.h"

namespace application {

/*!
 * \brief Enumeration for all Error Code values of the ApplicationBase.
 */
enum class ApplicationBaseErrc : ara::core::ErrorDomain::CodeType { kUnknownError = 0, kThreadCreationFailed = 1 };

/*!
 * \brief An interface of the Template Exception.
 */
class ApplicationBaseException : public ara::core::Exception {
 public:
  using Exception::Exception;
};

/*!
 * \brief Template Error Domain class.
 * \details This class represents an error domain responsible for all errors occurring in the ApplicationBase.
 */
class ApplicationBaseErrorDomain : public ara::core::ErrorDomain {
 public:
  /*!
   * \brief Template error domain identifier (unique domain ID).
   */
  constexpr static IdType kId{0x123456789ABCDEF};  // sample ID

  /*!
   * \brief Error code type definition.
   */
  using Errc = ApplicationBaseErrc;

  /*!
   * \brief Constructor for TemplateErrorDomain.
   */
  constexpr ApplicationBaseErrorDomain() noexcept : ErrorDomain(kId) {}

  /*!
   * \brief Return the name for this error domain.
   * \return The name as a null-terminated string, never nullptr.
   */
  StringType Name() const noexcept final { return "ApplicationBase"; };

  /*!
   * \brief Return the textual description for the given error code.
   * \param error_code The domain specific error code.
   * \return The text as a null-terminated string, never nullptr.
   */
  StringType Message(ara::core::ErrorDomain::CodeType error_code) const noexcept final;

  /*!
   * \brief Throws the given ErrorCode as Exception.
   * \details If the code is compiled w/o exceptions, this function will call terminate instead.
   * \param error_code The ErrorCode to be thrown.
   */
  [[noreturn]] void ThrowAsException(const ara::core::ErrorCode& error_code) const noexcept(false) {
    vac::language::ThrowOrTerminate<ApplicationBaseException>(error_code);
  }
};

/*!
 * \brief Internal namespace.
 */
namespace internal {
/*!
 * \brief Global TemplateErrorDomain instance.
 */
constexpr ApplicationBaseErrorDomain kTemplateErrorDomain;
}  // namespace internal

/*!
 * \brief Factory function of the TemplateErrorDomain.
 * \return Constant reference to the single instance of the TemplateErrorDomain.
 */
inline constexpr ara::core::ErrorDomain const& GetTemplateErrorDomain() { return internal::kTemplateErrorDomain; }

/*!
 * \brief Make ErrorCode instances from the Template Error Domain.
 * \param code An error code identifier from the TemplateErrc enumeration.
 * \param data Supplementary data for the error description.
 * \param message Additional error message supplied by user code.
 * \return ErrorCode instance always references to TemplateErrorDomain.
 */
inline constexpr ara::core::ErrorCode MakeErrorCode(ApplicationBaseErrorDomain::Errc code,
                                                    ara::core::ErrorDomain::SupportDataType data,
                                                    char const* message = nullptr) {
  return {static_cast<ara::core::ErrorDomain::CodeType>(code), GetTemplateErrorDomain(), data, message};
}

}  // namespace application

#endif  // ERROR_DOMAIN_H_
