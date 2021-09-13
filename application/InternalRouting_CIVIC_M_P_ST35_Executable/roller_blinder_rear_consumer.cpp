#include "roller_blinder_rear_consumer.h"

using vac::container::literals::operator""_sv;

namespace i3 {
namespace services {
namespace common {

/* Initialization of static class members */
std::atomic<bool> RollerBlinderRearConsumer::rb_rear_service_instance_found_{false};

std::atomic<bool> RollerBlinderRearConsumer::rb_rear_events_subscribed_{false};

::DataTypes::TypeRef::c02_Idle_Opn_Cls_SNA RollerBlinderRearConsumer::data_;

ara::core::InstanceSpecifier const rb_rear_consumer_instance_specifier {
    "InternalRouting_CIVIC_M_P_ST35_Executable/"
    "InternalRouting_CIVIC_M_P_ST35_ExecutableRootSwc/"
    "R_RollerBlindRear_UI_Ctrl_HU_Service_ST3"_sv};

std::shared_ptr<::services::ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::
    RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy> RollerBlinderRearConsumer::rb_rear_service_proxy_;

RollerBlinderRearConsumer::RollerBlinderRearConsumer() {
    find_service_handle_ =
        ::services::ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::
        RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy::StartFindService(FindServiceHandler, rb_rear_consumer_instance_specifier);
}

RollerBlinderRearConsumer::~RollerBlinderRearConsumer() {
}

bool RollerBlinderRearConsumer::CheckAndStopFindService() {
  bool retval = false;

  /* Check if SI_Speedlimiter service is found */
  if (!rb_rear_service_instance_found_.load()) {
    static int counter = 0;
    if (++counter % 2 == 0) {
      GetLogger().LogInfo() << "Still searching for RB_Rear service";
    }
  }  else {

    /* Stop searching for further services */
    ::services::ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy::
    StopFindService(find_service_handle_);
    GetLogger().LogInfo() << "Stopped searching for SI_Speedlimiter service";
    retval = true;
  }

  return retval;
}

void RollerBlinderRearConsumer::FindServiceHandler(ara::com::ServiceHandleContainer<::services::
    ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::
    RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy::HandleType> rb_rear_services) {
    if (rb_rear_services.size() == 0) {
        GetLogger().LogInfo() << "No Roller Blinder service instance found.";
        return;
    } else if (rb_rear_services.size() == 1) {
        GetLogger().LogInfo() << "Found exactly one Roller Blinder service instance.";
        //rb_rear_service_proxy_ = std::make_shared<::services::ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy>(rb_rear_services[0]);
        rb_rear_service_instance_found_ = true;
    } else {
        GetLogger().LogInfo() << "Found more than one Roller Blinder service instance. Taking the first.";
        //rb_rear_service_proxy_ = std::make_shared<::services::ns_rollerblindrear_ui_ctrl_hu_service_st3_210::proxy::RollerBlindRear_UI_Ctrl_HU_Service_ST3_210Proxy>(rb_rear_services[0]);
        rb_rear_service_instance_found_ = true;
    }
}

bool RollerBlinderRearConsumer::SubscribeToEvents() {
  bool retval = false;

    /* If a service was found */
    if (rb_rear_service_instance_found_.load()) {
        /* If the events have not been subscribed already */
        if (!rb_rear_events_subscribed_.load()) {
            /* Subscribe to 'Ev_Capabilities' event and set handler */
            rb_rear_service_proxy_->RB_R_Rq_HU_ST3.SetReceiveHandler([]() {
                        RB_R_Rq_HU_ST3EventHandler();
                    });
            rb_rear_service_proxy_->RB_R_Rq_HU_ST3.Subscribe(
                        ara::com::EventCacheUpdatePolicy::kLastN, 1);

            /* Remember that the events are subscribed */
            rb_rear_events_subscribed_ = true;

            retval = true;
        }
    }

  return retval;
}

bool RollerBlinderRearConsumer::UnsubscribeFromEvents() {
    bool retval = false;
    /* If the events had been subscribed */
    if (rb_rear_events_subscribed_.load()) {
        /* Unsubscribe from events */
        rb_rear_service_proxy_->RB_R_Rq_HU_ST3.Unsubscribe();
        /* Remember that the events are not subscribed */
        rb_rear_events_subscribed_.store(false);
        retval = true;
    }
    return retval;
}

bool RollerBlinderRearConsumer::IsServiceFound() {
  return rb_rear_service_instance_found_.load();
}

bool RollerBlinderRearConsumer::IsSubscribed() {
  return rb_rear_service_instance_found_.load();
}

ara::log::Logger &RollerBlinderRearConsumer::GetLogger() {
    static ara::log::Logger &logger{ara::log::CreateLogger("RB_C", "Roller Blinder Service")};
    return logger;
}

void RollerBlinderRearConsumer::RB_R_Rq_HU_ST3EventHandler() {
    /* If there are events available */
    if (rb_rear_service_proxy_->RB_R_Rq_HU_ST3.Update()) {
        auto samples = rb_rear_service_proxy_->RB_R_Rq_HU_ST3.GetCachedSamples();
        /* receive data and send it immidiately */
        for (auto &sample : samples) {
            // @TODO : This operation has to be atomic
            data_ = *sample;
            GetLogger().LogInfo() << "rb_rear_service_proxy_.RB_R_Rq_HU_ST3 received with value: ["
                                    << data_ << "]";
        }
    }
}

}  // namespace common
}  // namespace services
}  // namespace i3