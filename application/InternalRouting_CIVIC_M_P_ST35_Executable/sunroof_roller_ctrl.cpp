/*
 *  Created on: May 5th, 2021
 *      Author: laxettd
 *       Notes: use case example for s2s
 */

#include "sunroof_roller_ctrl.h"

using vac::container::literals::operator""_sv;

namespace i3 {
namespace services {
namespace common {

/* Initialization of static class members */
std::atomic<bool> SunroofRollerConsumer::sunroof_roller_service_instance_found_{false};

std::atomic<bool> SunroofRollerConsumer::sunroof_roller_events_subscribed_{false};

ara::core::InstanceSpecifier const sunroof_roller_consumer_instance_specifier {
    "InternalRouting_CIVIC_M_P_ST35_Executable/"
    "InternalRouting_CIVIC_M_P_ST35_ExecutableRootSwc/"
    "R_TSSR_UI_Ctrl_Rq_Service_ST3"_sv};

std::shared_ptr<::services::ns_tssr_ui_ctrl_rq_service_st3::proxy::
    TSSR_UI_Ctrl_Rq_Service_ST3Proxy> SunroofRollerConsumer::sunroof_roller_service_proxy_;

sunroofDataType SunroofRollerConsumer::data_;


SunroofRollerConsumer::SunroofRollerConsumer() {
    find_service_handle_ = ::services::ns_tssr_ui_ctrl_rq_service_st3::proxy::TSSR_UI_Ctrl_Rq_Service_ST3Proxy::
        StartFindService(FindServiceHandler, sunroof_roller_consumer_instance_specifier);
}

SunroofRollerConsumer::~SunroofRollerConsumer() {
}

bool SunroofRollerConsumer::CheckAndStopFindService() {
    bool retval = true;

    /* Check if Roller Blinder service is found */
    if (!sunroof_roller_service_instance_found_.load()) {
        static int counter = 0;
        if (++counter % 2 == 0) {
            GetLogger().LogInfo() << "Still searching for Sunroof Roller service";
        }
    }else {
        /* Stop searching for further services */
        ::services::ns_tssr_ui_ctrl_rq_service_st3::proxy::TSSR_UI_Ctrl_Rq_Service_ST3Proxy::
        StopFindService(find_service_handle_);
        GetLogger().LogInfo() << "Stopped searching for Sunroof Roller service";
        retval = true;
    }

    return retval;
}

void SunroofRollerConsumer::FindServiceHandler(ara::com::ServiceHandleContainer<::services::
ns_tssr_ui_ctrl_rq_service_st3::proxy::TSSR_UI_Ctrl_Rq_Service_ST3Proxy::HandleType> sunroof_roller_services) {
    if (sunroof_roller_services.size() == 0) {
        GetLogger().LogInfo() << "no sunroof roller service instance found.";
        return;
    } else if (sunroof_roller_services.size() == 1) {
        GetLogger().LogInfo() << "found exactly one sunroof roller service instance.";
        sunroof_roller_service_proxy_ = std::make_shared<::services::ns_tssr_ui_ctrl_rq_service_st3::proxy::
        TSSR_UI_Ctrl_Rq_Service_ST3Proxy>(sunroof_roller_services[0]);
        sunroof_roller_service_instance_found_ = true;
    } else {
        GetLogger().LogInfo() << "Found more than one sunroof roller service instance. Taking the first.";
        sunroof_roller_service_proxy_ = std::make_shared<::services::ns_tssr_ui_ctrl_rq_service_st3::proxy::
        TSSR_UI_Ctrl_Rq_Service_ST3Proxy>(sunroof_roller_services[0]);
        sunroof_roller_service_instance_found_ = true;
    }
}

bool SunroofRollerConsumer::SubscribeToEvents() {
    bool retval = false;

    /* If a service was found */
    if (sunroof_roller_service_instance_found_.load()) {
        /* If the events have not been subscribed already */
        if (!sunroof_roller_events_subscribed_.load()) {
            /* Subscribe to 'Ev_Capabilities' event and set handler */
            sunroof_roller_service_proxy_->TSSR_UI_Ctrl_Rq_ST3.SetReceiveHandler([]() {
                    TSSR_UI_Ctrl_Rq_ST3EventHandler();
                    });
            sunroof_roller_service_proxy_->TSSR_UI_Ctrl_Rq_ST3.Subscribe(
                    ara::com::EventCacheUpdatePolicy::kLastN, 1);

            /* Remember that the events are subscribed */
            sunroof_roller_events_subscribed_ = true;

            retval = true;
        }
    }
    return retval;
}

bool SunroofRollerConsumer::UnsubscribeFromEvents() {
    bool retval = false;
    /* If the events had been subscribed */
    if (sunroof_roller_events_subscribed_.load()) {
        /* Unsubscribe from events */
        sunroof_roller_service_proxy_->TSSR_UI_Ctrl_Rq_ST3.Unsubscribe();
        /* Remember that the events are not subscribed */
        sunroof_roller_events_subscribed_.store(false);
        retval = true;
    }
    return retval;
}

ara::log::Logger &SunroofRollerConsumer::GetLogger() {
    static ara::log::Logger &logger{ara::log::CreateLogger("SR_C", "Sunroof Roller Service")};
    return logger;
}

void SunroofRollerConsumer::TSSR_UI_Ctrl_Rq_ST3EventHandler() {
    /* If there are events available */
    if (sunroof_roller_service_proxy_->TSSR_UI_Ctrl_Rq_ST3.Update()) {
        auto samples = sunroof_roller_service_proxy_->TSSR_UI_Ctrl_Rq_ST3.GetCachedSamples();
        GetLogger().LogInfo() << "TSSR_UI_Ctrl_Rq_ST3 received " << samples.size() << " samples";
        /* receive data and send it immidiately */
        for (auto &sample : samples) {
            SunroofRollerConsumer::data_.TSSR_RB_Sw_Psd_ST3 = sample->TSSR_RB_Sw_Psd_ST3;
            SunroofRollerConsumer::data_.TSSR_Sw_Stat_ST3 = sample->TSSR_Sw_Stat_ST3;
            GetValues();
        }
    }
}

bool SunroofRollerConsumer::IsServiceFound() {
  return sunroof_roller_service_instance_found_.load();
}

bool SunroofRollerConsumer::IsSubscribed() {
  return sunroof_roller_events_subscribed_.load();
}

void SunroofRollerConsumer::GetValues()
{
    GetLogger().LogInfo() << "TSSR_UI_Ctrl_Rq_ST3.TSSR_RB_Sw_Psd_ST3 received with value: ["
            << SunroofRollerConsumer::data_.TSSR_RB_Sw_Psd_ST3 << "]\n"
            << "TSSR_UI_Ctrl_Rq_ST3.TSSR_Sw_Stat_ST3 received with value: ["
            << SunroofRollerConsumer::data_.TSSR_Sw_Stat_ST3 << "]";
}
}  // namespace common
}  // namespace services
}  // namespace i3
