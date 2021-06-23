/*****************************************************************************
 * \file   diagnostic_ssa_client.h
 *
 * \brief  SSA client implementation for receiving variant coding data
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/
#ifndef SRC_DIAGNOSTIC_SSA_CLIENT_H_
#define SRC_DIAGNOSTIC_SSA_CLIENT_H_

/* C system includes */

/* C++ system includes */
#include <memory>

/* Autosar includes */
#include "ara/core/instance_specifier.h"
#include "ara/log/logging.h"

/* Project specific includes */
#include "services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_proxy.h"

namespace application {

namespace ConfigManagerApp {

class DiagnosticSsaClient {
public:
    /*****************************************************************************
     * \brief Constructor.
     ******************************************************************************/
    DiagnosticSsaClient();

    /*****************************************************************************
     * \brief Destructor.
     ******************************************************************************/
    virtual ~DiagnosticSsaClient();

    /*****************************************************************************
     * \brief Find SSA services for variant coding
     *
     * This method is blocking until the first service provider is discovered.
     *
     * \retval  true   Success
     * \retval  false  Failure
     ******************************************************************************/
    static bool FindService();

    /*****************************************************************************
     * \brief Subscribe to service events and register handler for events.
     *
     * \retval  true   Success
     * \retval  false  Failure
     ******************************************************************************/
    static bool SubscribeToEvents();

    /*****************************************************************************
     * \brief Unsubscribe from service events.
     *
     * \retval  true   Success
     * \retval  false  Failure
     ******************************************************************************/
    static bool UnsubscribeFromEvents();

private:
    /*****************************************************************************
     * \brief Handler for service discovery
     *
     * \param[in]  ssa_variant_coding_services  Container of found service handles.
     ******************************************************************************/
    static void FindSsaServiceHandler(
        ara::com::ServiceHandleContainer<services::ns_si_dummyswc_2_to_cnfg_mngr::proxy::
                                             SI_X6AA_Dummy_B2_Service_ReservedProxy::HandleType>
            ssa_variant_coding_services);

    /*****************************************************************************
     * \brief Handler for EventHandlerForSsaVariantCodingData event
     ******************************************************************************/
    static void EventHandlerForSsaVariantCodingData();

    /**
     * \brief Holds the logging context
     */
    static ara::log::Logger& GetLoggerForSsaClient();

    /** Flag that a service has been found */
    static std::atomic<bool> ssa_variant_coding_service_found;

    /** Flag that events have been subsribed */
    static std::atomic<bool> ssa_variant_coding_events_subscribed;

    /** Pointer to the bound service */
    static std::shared_ptr<
        services::ns_si_dummyswc_2_to_cnfg_mngr::proxy::SI_X6AA_Dummy_B2_Service_ReservedProxy>
        ssa_variant_coding_service_proxy;
    /** Instance specifier for the service */
    static ara::core::InstanceSpecifier const ssa_variant_coding_instance_specifier;
};

} // namespace ConfigManagerApp

} // namespace application

#endif // SRC_DIAGNOSTIC_SSA_CLIENT_H_
