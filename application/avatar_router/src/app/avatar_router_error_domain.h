#pragma once

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "vac/language/throw_or_terminate.h"

namespace Application {

/*!
 * \brief Enumeration for all Error Code values of the Avatar Router
 */
enum class AvatarRouterErrc : ara::core::ErrorDomain::CodeType {
    kUnknownError = 0,
    kThreadCreationFailed = 1
};

/*!
 * \brief An interface of the Avatar Router Exception.
 */
class AvatarRouterException : public ara::core::Exception {
public:
    using Exception::Exception;
};

/*!
 * \brief Avatar Router Error Domain class.
 * \details This class represents an error domain responsible for all errors
 * occurring in the Avatar Router.
 */
class AvatarRouterErrorDomain final : public ara::core::ErrorDomain {
public:
    /*!
     * \brief Error domain identifier (unique domain ID).
     */
    constexpr static IdType kId{0x123456789ABCDEF}; // sample ID

    /*!
     * \brief Error code type definition.
     */
    using Errc = AvatarRouterErrc;

    /*!
     * \brief Constructor for error domain.
     */
    constexpr AvatarRouterErrorDomain() noexcept
        : ErrorDomain(kId)
    {
    }

    /*!
     * \brief Return the name for this error domain.
     * \return The name as a null-terminated string, never nullptr.
     */
    StringType Name() const noexcept final
    {
        return "AvatarRouter";
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
        vac::language::ThrowOrTerminate<AvatarRouterException>(error_code);
    }
};

/*!
 * \brief Internal namespace.
 */
namespace internal {
/*!
 * \brief Global AvatarRouterErrorDomain instance.
 */
constexpr AvatarRouterErrorDomain kAvatarRouterErrorDomain;
} // namespace internal

/*!
 * \brief Factory function of the AvatarRouterErrorDomain.
 * \return Constant reference to the single instance of the AvatarRouterErrorDomain.
 */
inline constexpr ara::core::ErrorDomain const& GetAvatarRouterErrorDomain()
{
    return internal::kAvatarRouterErrorDomain;
}

/*!
 * \brief Make ErrorCode instances from the Avatar Router Error Domain.
 * \param code An error code identifier from the AvatarRouterErrc enumeration.
 * \param data Supplementary data for the error description.
 * \param message Additional error message supplied by user code.
 * \return ErrorCode instance always references to AvatarRouterErrorDomain.
 */
inline constexpr ara::core::ErrorCode MakeErrorCode(
    AvatarRouterErrorDomain::Errc code,
    ara::core::ErrorDomain::SupportDataType data,
    char const* message = nullptr)
{
    return {static_cast<ara::core::ErrorDomain::CodeType>(code),
            GetAvatarRouterErrorDomain(),
            data,
            message};
}

/*!
 * \brief Array of error domain message strings.
 */
constexpr std::array<ara::core::ErrorDomain::StringType, 2> kMessages{
    "Unknown error.",
    "Error during creation of a thread."};

AvatarRouterErrorDomain::StringType AvatarRouterErrorDomain::Message(
    ara::core::ErrorDomain::CodeType error_code) const noexcept
{
    if (static_cast<std::size_t>(error_code) >= kMessages.size()) {
        error_code = 0;
    }
    return kMessages[static_cast<std::size_t>(error_code)];
}

} // namespace Application

