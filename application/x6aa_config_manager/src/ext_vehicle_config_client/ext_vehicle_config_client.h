/*****************************************************************************
 * \file   ext_vehicle_config_client.h
 *
 * \brief  ExtVehicleConfig_Service_ST3 proxy implementation
 * \author Monica Delgado
 * \date   05-07-2021
 * \note   Based on BROP B1 release
 ******************************************************************************/
#ifndef SRC_EXT_VEHICLE_CONFIG_CLIENT_H_
#define SRC_EXT_VEHICLE_CONFIG_CLIENT_H_


/* C++ system includes */
#include <memory>

/* Autosar includes */
#include "ara/log/logging.h"
#include "ara/core/instance_specifier.h"


/* Project specific includes */
#include "services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3_proxy.h"

namespace application {

namespace ConfigManagerApp {

class ExtVehicleConfigClient {
 public:

    /*!
     * \brief Constructor.
     */
    ExtVehicleConfigClient();

    /*!
     * \brief Destructor.
     */
    ~ExtVehicleConfigClient();

    /*!
     * \brief Check if ExtVehicleConfig service has been found.
     *
     * This method will stop the FindService if this has been found.
     *
     * \return  true   when success, false otherwise.
     */
    bool CheckAndStopFindService();

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
     * \return true when service found, false otherwise.
     */
    static bool IsServiceFound();

    /*!
     * \brief Get if it subscribed successfully to the service.
     *
     * \return true when subscribed, false otherwise.
     */
    static bool IsSubscribed();

 private:
    /*!
     * \brief Handler for service discovery.
     *
     * \param[in]  ext_vehicle_config_services  Container of found service handles.
     */
    static void FindServiceHandler(ara::com::ServiceHandleContainer<services::
      ns_extvehicleconfig_service_st3::proxy::SI_ExtVehicleConfig_Service_ST3Proxy::
      HandleType> ext_vehicle_config_services);

    /*!
     * \brief Handler for Ev_EVC_CfgBit_01_26_Pr5_ST3 event.
     */
    static void Ev_EVC_CfgBit_01_26_Pr5_ST3Handler();

    /*!
     * \brief Retrieve the logger instance for this class.
     *
     * \return  Reference to the class logger.
     */
    static ara::log::Logger& GetLogger();

    /*!
     * \brief Flag that a service has been found.
     */
    static std::atomic<bool> ext_vehicle_config_service_found_;

    /*!
     * \brief Flag that events have been subsribed.
     */
    static std::atomic<bool> ext_vehicle_config_events_subscribed_;

    /*!
     * \brief Pointer to the bound service.
     */
    static std::shared_ptr<services::ns_extvehicleconfig_service_st3::
      proxy::SI_ExtVehicleConfig_Service_ST3Proxy> ext_vehicle_config_service_proxy_;

    /*!
     * \brief Service instance identifier.
     */
    static ara::core::InstanceSpecifier const ext_vehicle_config_instance_specifier_;

    /*!
     * \brief Find service handler instance.
     */
    ara::com::FindServiceHandle find_service_handle_;

};

} // namespace ConfigManagerApp

} // namespace application

#endif  // SRC_EXT_VEHICLE_CONFIG_CLIENT_H_
