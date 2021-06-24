/*****************************************************************************
 * \file   si_speedlimiter.h
 *
 * \brief  ns_speedlimiter proxy implementation
 * \author
 * \date
 * \note
 ******************************************************************************/
#ifndef SRC_SI_SPEEDLIMITER_H_
#define SRC_SI_SPEEDLIMITER_H_

/* C system includes */


/* C++ system includes */
#include <memory>

/* Autosar includes */
#include "ara/log/logging.h"
#include "ara/core/instance_specifier.h"


/* Project specific includes */
#include "services/ns_speedlimiter/si_speedlimiter_proxy.h"

namespace idc6 {
namespace rovservices {

class SISpeedlimiter {
 public:

    /*!
     * \brief Constructor.
     */
    SISpeedlimiter();

    /*!
     * \brief Destructor.
     */
    ~SISpeedlimiter();

    /*!
     * \brief Find ns_speedlimiter service.
     *
     * This method is blocking until the first service provider is discovered.
     *
     * \return  true   when success, false otherwise.
     */
    static bool FindService();

    /*!
     * \brief Subscribe to service events and register handler for events.
     *
     * \return  true   when success, false otherwise.
     */
    static bool SubscribeToEvents();

    /*!
     * \brief Unsubscribe from service events.
     *
     * \return  true   when success, false otherwise.
     */
    static bool UnsubscribeFromEvents();

    /*!
     * \brief Get if the service has been found.
     *
     * \return  true   when service found, false otherwise.
     */
    static bool IsServiceFound();

    /*!
     * \brief Implementation of 'Meth_GetCapabilities' method.
     *
     * \return  Future of the return value
     */
    ara::core::Future<services::ns_speedlimiter::proxy::methods::Meth_GetCapabilities::Output>
    Meth_GetCapabilities(void);

    /*!
     * \brief Implementation of 'Meth_RequestSpeedLimit' method.
     *
     * \param[in] data The speed limit request
     */
    void Meth_RequestSpeedLimit(::DataTypes::VSLim_RequestLimit_In::VSLim_RequestLimit_In const& data);


 private:
    /*!
     * \brief Handler for service discovery.
     *
     * \param[in]  si_speedlimiter_services  Container of found service handles.
     */
    static void FindServiceHandler(ara::com::ServiceHandleContainer<services::ns_speedlimiter::proxy::SI_SpeedLimiterProxy::HandleType>
                                   si_speedlimiter_services);

    /*!
     * \brief Handler for Ev_Capabilities event.
     */
    static void Ev_CapabilitiesHandler();

    /*!
     * \brief Handler for Ev_SpeedLimiterState event.
     */
    static void Ev_SpeedLimiterStateHandler();

    /*!
     * \brief Retrieve the logger instance for this class.
     *
     * \return  Reference to the class logger.
     */
    static ara::log::Logger& GetLogger();

    /*!
     * \brief Flag that a service has been found.
     */
    static std::atomic<bool> si_speedlimiter_service_found_;

    /*!
     * \brief Flag that events have been subsribed.
     */
    static std::atomic<bool> si_speedlimiter_events_subscribed_;

    /*!
     * \brief Pointer to the bound service.
     */
    static std::shared_ptr<services::ns_speedlimiter::proxy::
    SI_SpeedLimiterProxy> si_speedlimiter_service_proxy_;

    /*!
     * \brief Service instance identifier.
     */
    static ara::core::InstanceSpecifier const si_speedlimiter_instance_specifier_;

};

}  // namespace services
}  // namespace idc6

#endif  // SRC_SI_SPEEDLIMITER_H_
