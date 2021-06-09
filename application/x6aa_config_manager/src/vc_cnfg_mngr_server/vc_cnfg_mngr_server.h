/*****************************************************************************
 * \file   vc_cnfg_mngr_server.h
 *
 * \brief  VVcCnfgMngrServer class representing the variant coding server application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/

#ifndef SRC_VC_CNFG_MNGR_SERVER_H_
#define SRC_VC_CNFG_MNGR_SERVER_H_

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ara/core/abort.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"
#include "ara/core/initialization.h"
#include "ara/exec/application_client.h"
#include "ara/log/logging.h"
#include "osabstraction/process/process.h"
#include "osabstraction/thread/thread.h"
#include "persistent-mem-accessor/persistent_mem_accessor.h"
#include "services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.h"
#include "vac/container/string_literals.h"
#include "vac/language/throw_or_terminate.h"

#include <csignal>
#include <iostream>
#include <thread>

/*!
 * \brief Namespace for the example application.
 */
namespace application {

/*!
 * \brief Main class representing the VcCnfgMngrServer.
 * \vprivate Example class for component internal use.
 */
class VcCnfgMngrServer final {
public:
    /*!
     * \brief Constructor of class VcCnfgMngrServer.
     */
    VcCnfgMngrServer();

    /*!
     * \brief Deleted copy constructor
     */
    VcCnfgMngrServer(VcCnfgMngrServer const&) = delete;

    /*!
     * \brief Default move constructor
     */
    VcCnfgMngrServer(VcCnfgMngrServer&& other) noexcept = delete;

    /*!
     * \brief Destructor of class VcCnfgMngrServer.
     */
    ~VcCnfgMngrServer();

    /*!
     * \brief Deleted copy assignment operator
     * \return Reference to application
     */
    VcCnfgMngrServer& operator=(VcCnfgMngrServer const&) & = delete;

    /*!
     * \brief Default move assignment operator
     * \return Reference to application
     */
    VcCnfgMngrServer& operator=(VcCnfgMngrServer&& other) & = delete;

    /*!
     * \brief Lifecycle method for run mode.
     * \return Error (Exit) code of application.
     */
    std::int8_t Run();

private:
    /*!
     * \brief Start threads given by information in handed over thread information.
     * \param thread_info The thread information array.
     * \return The process id of the started thread.
     * \error TemplateErrc::kThreadCreationFailed Naming the thread after creation has failed.
     */
    ara::core::Result<osabstraction::process::ProcessId> StartSignalHandlerThread();

    /*!
     * \brief Entry point of the thread receiving signals from the execution manager.
     */
    void SignalHandlerThread();

    /*!
     * \brief Reporting the given application state
     * \param application_state The application state to report
     */
    void ReportApplicationState(ara::exec::ApplicationState application_state);

    /*!
     * \brief Logger instance.
     */
    ara::log::Logger& log_{ara::log::CreateLogger("Skeleton", "Skeleton demo")};

    /*!
     * \brief ApplicationClient instance
     */
    ara::exec::ApplicationClient application_client;

    /*!
     * \brief Signal handler thread.
     */
    std::thread signal_handler_thread{};

    /*!
     * \brief Flag to exit the application.
     */
    std::atomic_bool exit_requested{false};

    /*!
     * \brief Flag to mark if the application exit was triggered by a signal.
     */
    std::atomic_bool terminated_by_signal{false};

    /*!
     * \brief Flag to indicate initialization error. Only used in main thread.
     */
    bool has_initialization_failed_{false};

    /*!
     * \brief SI_X6AA_Cnfg_Mngr_Service_ReservedSkeleton service instance
     */
    ara::core::Optional<
        services::ns_si_cnfg_mngr_to_dummyswc::skeleton::SI_X6AA_Cnfg_Mngr_Service_ReservedSkeleton>
        siX6aaCnfgMngrServiceReservedSkeleton;

    /*
     *  presistency integration
     */
    application::VariantCodingApp::PersistentMemAccessor memAccessor;
};

} // namespace application

#endif // SRC_VC_CNFG_MNGR_SERVER_H_
