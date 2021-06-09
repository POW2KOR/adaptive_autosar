/*****************************************************************************
 * \file   variant_coding_consumer.h
 *
 * \brief  VariantCodingService proxy implementation
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/
#ifndef SRC_VARIANT_CODING_CONSUMER_H_
#define SRC_VARIANT_CODING_CONSUMER_H_

/* C system includes */

/* C++ system includes */
#include <memory>

/* Autosar includes */
#include "ara/core/instance_specifier.h"
#include "ara/log/logging.h"

/* Project specific includes */
#include "services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_proxy.h"

namespace application {

class VariantCodingConsumer {
public:
    /*****************************************************************************
     * \brief Constructor.
     ******************************************************************************/
    VariantCodingConsumer();

    /*****************************************************************************
     * \brief Destructor.
     ******************************************************************************/
    virtual ~VariantCodingConsumer();

    /*****************************************************************************
     * \brief Find VariantCodingService
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
     * \param[in]  variant_coding_services  Container of found service handles.
     ******************************************************************************/
    static void FindServiceHandler(
        ara::com::ServiceHandleContainer<services::ns_si_cnfg_mngr_to_dummyswc::proxy::
                                             SI_X6AA_Cnfg_Mngr_Service_ReservedProxy::HandleType>
            variant_coding_services);

    /*****************************************************************************
     * \brief Handler for VechicleInformation0400VcEventData event
     ******************************************************************************/
    static void VechicleInformation0400VcEventHandler();

    /*****************************************************************************
     * \brief Retrieve the logger instance for this class
     *
     * \return  Reference to the class logger
     ******************************************************************************/
    static ara::log::Logger& GetLogger();

    /** Flag that a service has been found */
    static std::atomic<bool> variant_coding_service_found;

    /** Flag that events have been subsribed */
    static std::atomic<bool> variant_coding_events_subscribed;

    /** Pointer to the bound service */
    static std::shared_ptr<
        services::ns_si_cnfg_mngr_to_dummyswc::proxy::SI_X6AA_Cnfg_Mngr_Service_ReservedProxy>
        variant_coding_service_proxy;

    /** Instance specifier for the service */
    static ara::core::InstanceSpecifier const variant_coding_instance_specifier;
};
} // namespace application

#endif // SRC_VARIANT_CODING_CONSUMER_H_
