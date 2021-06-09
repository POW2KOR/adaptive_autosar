/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *           Developed and programmed by MBition - Copyright (c) 2019-2020 Daimler AG
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file
 *        \brief  Entry point of the vcServer application.
 *
 *      \details  -
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "amsr/log/internal/lifecycle.h"
#include "ara/core/abort.h"
#include "ara/core/initialization.h"
#include "ara/core/result.h"
#include "vc_cnfg_mngr_server/vc_cnfg_mngr_server.h"

#include <csignal>

using vac::container::operator""_sv;

namespace {
/*!
 * \brief Initializes the signal handling.
 * \return void.
 */
void InitializeSignalHandling() noexcept
{
    bool success{true};
    sigset_t signals;

    /* Block all signals except the SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGSEGV signals because
     * blocking them will lead to undefined behavior. Their default handling shall not be changed
     * (dependent on underlying POSIX environment, usually process is killed and a dump file is
     * written). Signal mask will be inherited by subsequent threads. */

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

} // namespace

/*!
 * \brief Entry Point of the process.
 * \return zero when successfully executed
 */
int main()
{
    int return_value = 0;

    /* Initialize signal handling. */
    InitializeSignalHandling();

    /* Initialize ara::core */
    ara::core::Result<void> init_result{ara::core::Initialize()};

    if (!init_result.HasValue()) {
        char const* msg{"ara::core::Initialize() failed."};
        std::cerr << msg << "\nResult contains: " << init_result.Error().Message() << ", "
                  << init_result.Error().UserMessage() << "\n";
        ara::core::Abort(msg);
    } else {
        /* Create the application object and run it */
        application::VcCnfgMngrServer vcServerApp;
        return_value = vcServerApp.Run();

        if ( EXIT_FAILURE == return_value) {
            char const* msg{"failed to run variant coding server for offering services."};
            ara::core::Abort(msg);
        }

        /* Deinitialize ara::core */
        ara::core::Result<void> deinit_result{ara::core::Deinitialize()};

        if (!deinit_result.HasValue()) {
            char const* msg{"ara::core::Deinitialize() failed."};
            std::cerr << msg << "\nResult contains: " << deinit_result.Error().Message() << ", "
                      << deinit_result.Error().UserMessage() << "\n";
            ara::core::Abort(msg);
        }
    }

    return return_value;
}