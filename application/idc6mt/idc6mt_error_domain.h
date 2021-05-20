#pragma once

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "vac/language/throw_or_terminate.h"

namespace idc6mtd {

/*!
 * \brief Enumeration for all Error Code values of the IDC6 MT daemon.
 */
enum class Idc6MtdErrc : ara::core::ErrorDomain::CodeType {
    kUnknownError = 0,
    kThreadCreationFailed = 1,
    kInternalDaemonError = 2,
};

/*!
 * \brief An interface of the IDC6 MT daemon Exception.
 */
class Idc6MtdException : public ara::core::Exception {
public:
    using Exception::Exception;
};

/*!
 * \brief IDC6 MT daemon Error Domain class.
 * \details This class represents an error domain responsible for all errors
 * occurring in the IDC6 MT daemon.
 */
class Idc6MtdErrorDomain final : public ara::core::ErrorDomain {
public:
    /*!
     * \brief Error domain identifier (unique domain ID).
     */
    constexpr static IdType kId{0x123456789ABCDEF}; // sample ID

    /*!
     * \brief Error code type definition.
     */
    using Errc = Idc6MtdErrc;

    /*!
     * \brief Constructor for error domain.
     */
    constexpr Idc6MtdErrorDomain() noexcept
        : ErrorDomain(kId)
    {
    }

    /*!
     * \brief Return the name for this error domain.
     * \return The name as a null-terminated string, never nullptr.
     */
    StringType Name() const noexcept final
    {
        return "IDC6 MT daemon";
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
        vac::language::ThrowOrTerminate<Idc6MtdException>(error_code);
    }
};

/*!
 * \brief Internal namespace.
 */
namespace internal {
/*!
 * \brief Global TemplateErrorDomain instance.
 */
constexpr Idc6MtdErrorDomain kIdc6MtdErrorDomain;
} // namespace internal

/*!
 * \brief Factory function of the TemplateErrorDomain.
 * \return Constant reference to the single instance of the TemplateErrorDomain.
 */
inline constexpr ara::core::ErrorDomain const& GetIdc6MtdErrorDomain()
{
    return internal::kIdc6MtdErrorDomain;
}

/*!
 * \brief Make ErrorCode instances from the Idc6MtdError Domain.
 * \param code An error code identifier from the Idc6MtdErrc enumeration.
 * \param data Supplementary data for the error description.
 * \param message Additional error message supplied by user code.
 * \return ErrorCode instance always references to Idc6MtdErrorDomain.
 */
inline constexpr ara::core::ErrorCode MakeErrorCode(
    Idc6MtdErrorDomain::Errc code,
    ara::core::ErrorDomain::SupportDataType data,
    char const* message = nullptr)
{
    return {static_cast<ara::core::ErrorDomain::CodeType>(code),
            GetIdc6MtdErrorDomain(),
            data,
            message};
}

/*!
 * \brief Array of error domain message strings.
 */
constexpr std::array<ara::core::ErrorDomain::StringType, 3> kMessages{
    "Unknown error.",
    "Error during creation of a thread.",
    "Internal Daemon error."
};

Idc6MtdErrorDomain::StringType Idc6MtdErrorDomain::Message(
    ara::core::ErrorDomain::CodeType error_code) const noexcept
{
    if (static_cast<std::size_t>(error_code) >= kMessages.size()) {
        error_code = 0;
    }
    return kMessages[static_cast<std::size_t>(error_code)];
}

} // namespace idc6mtd
