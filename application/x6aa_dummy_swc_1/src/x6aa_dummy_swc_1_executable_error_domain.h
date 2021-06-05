/*****************************************************************************
 * \file   x6aa_dummy_swc_1_executable_error_domain.h
 *
 * \brief  VariantCodingService error domain 
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date   
 * \note   TODO: additional notes
 ******************************************************************************/
#ifndef X6AA_DUMMY_SWC_1_EXECUTABLE_ERROR_DOMAIN_H
#define X6AA_DUMMY_SWC_1_EXECUTABLE_ERROR_DOMAIN_H

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "vac/language/throw_or_terminate.h"

namespace application {

/*!
 * \brief Enumeration for all Error Code values of the Stub application.
 */
enum class X6AADummySWC1ExecutableErrc : ara::core::ErrorDomain::CodeType {
    kUnknownError = 0,
    kThreadCreationFailed = 1
};

/*!
 * \brief An interface of the Stub Application Exception.
 */
class X6AADummySWC1ExecutableException : public ara::core::Exception {
public:
    using Exception::Exception;
};

/*!
 * \brief Stub Application Error Domain class.
 * \details This class represents an error domain responsible for all errors
 * occurring in the Stub application.
 */
class X6AADummySWC1ExecutableErrorDomain final : public ara::core::ErrorDomain {
public:
    /*!
     * \brief Error domain identifier (unique domain ID).
     */
    constexpr static IdType kId{0x123456789ABCDEF}; // sample ID

    /*!
     * \brief Error code type definition.
     */
    using Errc = X6AADummySWC1ExecutableErrc;

    /*!
     * \brief Constructor for error domain.
     */
    constexpr X6AADummySWC1ExecutableErrorDomain() noexcept
        : ErrorDomain(kId)
    {
    }

    /*!
     * \brief Return the name for this error domain.
     * \return The name as a null-terminated string, never nullptr.
     */
    StringType Name() const noexcept final
    {
        return "X6AADummySWC1Executable";
    };

    /*!
     * \brief Return the textual description for the given error code.
     * \param error_code The domain specific error code.
     * \return The text as a null-terminated string, never nullptr.
     */
    StringType Message(ara::core::ErrorDomain::CodeType error_code) const noexcept final;

    /*!
     * \brief Throws the given ErrorCode as Exception.
     * \details If the code is compiled w/o exceptions, this function will call
     * terminate instead.
     * \param error_code The ErrorCode to be thrown.
     */
    [[noreturn]] void ThrowAsException(const ara::core::ErrorCode& error_code) const noexcept(false)
    {
        vac::language::ThrowOrTerminate<X6AADummySWC1ExecutableException>(error_code);
    }
};

/*!
 * \brief Internal namespace.
 */
namespace internal {
/*!
 * \brief Global TemplateErrorDomain instance.
 */
constexpr X6AADummySWC1ExecutableErrorDomain kStubErrorDomain;
} // namespace internal

/*!
 * \brief Factory function of the TemplateErrorDomain.
 * \return Constant reference to the single instance of the TemplateErrorDomain.
 */
inline constexpr ara::core::ErrorDomain const& GetStubErrorDomain()
{
    return internal::kStubErrorDomain;
}

/*!
 * \brief Make ErrorCode instances from the Stub Error Domain.
 * \param code An error code identifier from the StubErrc enumeration.
 * \param data Supplementary data for the error description.
 * \param message Additional error message supplied by user code.
 * \return ErrorCode instance always references to StubErrorDomain.
 */
inline constexpr ara::core::ErrorCode MakeErrorCode(
    X6AADummySWC1ExecutableErrorDomain::Errc code,
    ara::core::ErrorDomain::SupportDataType data,
    char const* message = nullptr)
{
    return {static_cast<ara::core::ErrorDomain::CodeType>(code),
            GetStubErrorDomain(),
            data,
            message};
}

/*!
 * \brief Array of error domain message strings.
 */
constexpr std::array<ara::core::ErrorDomain::StringType, 2> kMessages {
    "Unknown error.", "Error during creation of a thread."};

X6AADummySWC1ExecutableErrorDomain::StringType X6AADummySWC1ExecutableErrorDomain::Message(
    ara::core::ErrorDomain::CodeType error_code) const noexcept
{
    if (static_cast<std::size_t>(error_code) >= kMessages.size()) {
        error_code = 0;
    }
    return kMessages[static_cast<std::size_t>(error_code)];
}

} // namespace Application

#endif /* end of include guard: X6AA_DUMMY_SWC_1_EXECUTABLE_ERROR_DOMAIN_H */
