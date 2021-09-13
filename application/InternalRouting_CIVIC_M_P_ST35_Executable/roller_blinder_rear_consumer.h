#ifndef ROLLER_BLINDER_REAR_CONSUMER_H_
#define ROLLER_BLINDER_REAR_CONSUMER_H_

#include <memory>
#include <ara/log/logging.h>
#include <thread>

#include "ara/core/instance_specifier.h"

#include "services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/rollerblindrear_ui_ctrl_hu_service_st3_210_proxy.h"
#include "services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_types.h"

namespace i3 {
namespace services {
namespace common {

 class RollerBlinderRearConsumer {
 public:

    /*!
     * \brief Constructor.
     */
    explicit RollerBlinderRearConsumer();

    /*!
     * \brief Destructor.
     */
    ~RollerBlinderRearConsumer();

    /*!
     * \brief Check if rollerBlinder_rear service has been found.
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

    /** Variable to store the Data read **/
    static ::DataTypes::TypeRef::c02_Idle_Opn_Cls_SNA data_;

    private:

    static void
    FindServiceHandler(ara::com::ServiceHandleContainer<::services::
        ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy::HandleType>
        rb_rear_services);

    static void RB_R_Rq_HU_ST3EventHandler();

    static ara::log::Logger& GetLogger();

    /** Pointer to the bound service */
    static std::shared_ptr<::services::ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::
    RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy> rb_rear_service_proxy_;

    /*!
     * \brief Flag that a service has been found.
     */
    static std::atomic<bool> rb_rear_service_instance_found_;

    /*!
     * \brief Flag that events have been subsribed.
     */
    static std::atomic<bool> rb_rear_events_subscribed_;

    /*!
     * \brief Find service handler instance.
     */
    ara::com::FindServiceHandle find_service_handle_;
};

}  // namespace common
}  // namespace services
}  // namespace i3

#endif  // ROLLER_BLINDER_REAR_CONSUMER_H_