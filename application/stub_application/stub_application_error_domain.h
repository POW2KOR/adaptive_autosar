#ifndef STUB_APPLICATION_ERROR_DOMAIN_H
#define STUB_APPLICATION_ERROR_DOMAIN_H

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "vac/language/throw_or_terminate.h"

namespace Application {

/*!
 * \brief Enumeration for all Error Code values of the Stub application.
 */
enum class StubApplicationErrc : ara::core::ErrorDomain::CodeType {
    kUnknownError = 0,
    kThreadCreationFailed = 1
};

/*!
 * \brief An interface of the Stub Application Exception.
 */
class StubApplicationException : public ara::core::Exception {
public:
    using Exception::Exception;
};

/*!
 * \brief Stub Application Error Domain class.
 * \details This class represents an error domain responsible for all errors
 * occurring in the Stub application.
 */
class StubApplicationErrorDomain final : public ara::core::ErrorDomain {
public:
    /*!
     * \brief Error domain identifier (unique domain ID).
     */
    constexpr static IdType kId{0x123456789ABCDEF}; // sample ID

    /*!
     * \brief Error code type definition.
     */
    using Errc = StubApplicationErrc;

    /*!
     * \brief Constructor for error domain.
     */
    constexpr StubApplicationErrorDomain() noexcept
        : ErrorDomain(kId)
    {
    }

    /*!
     * \brief Return the name for this error domain.
     * \return The name as a null-terminated string, never nullptr.
     */
    StringType Name() const noexcept final
    {
        return "StubApplication";
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
        vac::language::ThrowOrTerminate<StubApplicationException>(error_code);
    }
};

/*!
 * \brief Internal namespace.
 */
namespace internal {
/*!
 * \brief Global TemplateErrorDomain instance.
 */
constexpr StubApplicationErrorDomain kStubErrorDomain;
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
    StubApplicationErrorDomain::Errc code,
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
constexpr std::array<ara::core::ErrorDomain::StringType, 5> kMessages{
    {"Unknown error.", "Error during creation of a thread."}};

StubApplicationErrorDomain::StringType StubApplicationErrorDomain::Message(
    ara::core::ErrorDomain::CodeType error_code) const noexcept
{
    if (static_cast<std::size_t>(error_code) >= kMessages.size()) {
        error_code = 0;
    }
    return kMessages[static_cast<std::size_t>(error_code)];
}

} // namespace Application

#endif /* end of include guard: STUB_APPLICATION_ERROR_DOMAIN_H */
