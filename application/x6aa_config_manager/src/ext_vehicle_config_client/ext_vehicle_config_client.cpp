/*****************************************************************************
 * \file   ext_vehicle_config_client.cpp
 *
 * \brief  ExtVehicleConfig_Service_ST3 proxy implementation
 * \author Monica Delgado
 * \date   05-07-2021
 * \note   Based on BROP B1 release
 ******************************************************************************/

#include "ext_vehicle_config_client.h"

/* C++ system includes */
#include <memory>
#include <string>

namespace application {

namespace ConfigManagerApp {


using vac::container::literals::operator""_sv;

/* Initialization of static class members */
std::atomic<bool> ExtVehicleConfigClient::ext_vehicle_config_service_found_{false};
std::atomic<bool> ExtVehicleConfigClient::ext_vehicle_config_events_subscribed_{false};
std::shared_ptr<services::ns_extvehicleconfig_service_st3::proxy::SI_ExtVehicleConfig_Service_ST3Proxy>
  ExtVehicleConfigClient::ext_vehicle_config_service_proxy_;
ara::core::InstanceSpecifier const ExtVehicleConfigClient::
  ext_vehicle_config_instance_specifier_{
  "X6AA_Cnfg_Mngr_Executable/"
  "X6AA_Cnfg_Mngr_ExecutableRootSwc/"
  "R_ExtVehicleConfig_Service_ST3"_sv};


ExtVehicleConfigClient::ExtVehicleConfigClient() {
  /* Set Find Service Handler */
  find_service_handle_ = services::ns_extvehicleconfig_service_st3::proxy::
    SI_ExtVehicleConfig_Service_ST3Proxy::StartFindService(
      FindServiceHandler, ext_vehicle_config_instance_specifier_);
}

ExtVehicleConfigClient::~ExtVehicleConfigClient() {
  // Empty destructor
}

bool ExtVehicleConfigClient::CheckAndStopFindService() {
  bool retval = false;

  /* Check if ExtVehicleConfig service is found */
  if (!ext_vehicle_config_service_found_.load()) {
    static int counter = 0;
    if (++counter % 2 == 0) {
      GetLogger().LogInfo() << "Still searching for ExtVehicleConfig service";
    }
  }  else {

    /* Stop searching for further services */
    services::ns_extvehicleconfig_service_st3::proxy::
      SI_ExtVehicleConfig_Service_ST3Proxy::StopFindService(find_service_handle_);
    GetLogger().LogInfo() << "Stopped searching for ExtVehicleConfig service";
    retval = true;
  }

  return retval;
}

bool ExtVehicleConfigClient::SubscribeToEvents() {
  bool retval = false;

  /* If a service was found */
  if (ext_vehicle_config_service_found_.load()) {
    /* If the events have not been subscribed already */
    if (!ext_vehicle_config_events_subscribed_.load()) {
      /* Subscribe to 'Ev_EVC_CfgBit_01_26_Pr5_ST3' event and set handler */
      ext_vehicle_config_service_proxy_->Ev_EVC_CfgBit_01_26_Pr5_ST3.SetReceiveHandler([]() {
        Ev_EVC_CfgBit_01_26_Pr5_ST3Handler(); });
      ext_vehicle_config_service_proxy_->Ev_EVC_CfgBit_01_26_Pr5_ST3.Subscribe(
        ara::com::EventCacheUpdatePolicy::kLastN, 1);

      /* Remember that the events are subscribed */
      ext_vehicle_config_events_subscribed_.store(true);

      retval = true;
    }
  }

  return retval;
}

bool ExtVehicleConfigClient::UnsubscribeFromEvents() {
  bool retval = false;

  /* If the events had been subscribed */
  if (ext_vehicle_config_events_subscribed_.load()) {
    /* Unsubscribe from events */
    ext_vehicle_config_service_proxy_->Ev_EVC_CfgBit_01_26_Pr5_ST3.Unsubscribe();

    /* Remember that the events are not subscribed */
    ext_vehicle_config_events_subscribed_.store(false);

    retval = true;
  }

  return retval;
}

bool ExtVehicleConfigClient::IsServiceFound() {
  return ext_vehicle_config_service_found_.load();
}

bool ExtVehicleConfigClient::IsSubscribed() {
  return ext_vehicle_config_events_subscribed_.load();
}

void ExtVehicleConfigClient::FindServiceHandler(
  ara::com::ServiceHandleContainer<services::ns_extvehicleconfig_service_st3::proxy::
    SI_ExtVehicleConfig_Service_ST3Proxy::HandleType> ext_vehicle_config_services) {
  /* If there was no service found */
  if (ext_vehicle_config_services.size() == 0) {
    GetLogger().LogInfo() << "No ExtVehicleConfig service instance found";
    return;
  } else if (ext_vehicle_config_services.size() == 1) {
    /* If there is exactly one service found */
    GetLogger().LogInfo() << "Found one ExtVehicleConfig service instance";
  } else {
    /* If there are multiple services found */
    GetLogger().LogInfo() << "Found multiple instances of ExtVehicleConfig service, use the first one";
  }

  /* Get proxy instance */
  ext_vehicle_config_service_proxy_ =
    std::make_shared<services::ns_extvehicleconfig_service_st3::proxy::
    SI_ExtVehicleConfig_Service_ST3Proxy>(ext_vehicle_config_services[0]);

  /* Remember that a service is found */
  ext_vehicle_config_service_found_.store(true);
}

void ExtVehicleConfigClient::Ev_EVC_CfgBit_01_26_Pr5_ST3Handler() {
  GetLogger().LogDebug() << "Ev_EVC_CfgBit_01_26_Pr5_ST3Handler got called.";

  /* If there are events available */
  if (ext_vehicle_config_service_proxy_->Ev_EVC_CfgBit_01_26_Pr5_ST3.Update()) {
    auto samples = ext_vehicle_config_service_proxy_->Ev_EVC_CfgBit_01_26_Pr5_ST3.GetCachedSamples();

    GetLogger().LogDebug() << "Received " << samples.size() << " samples";

    for (auto &sample : samples) {
      GetLogger().LogInfo() << "ExtVehicleConfig service: Received event 'Ev_EVC_CfgBit_01_26_Pr5_ST3' with: "
        << "CRC_EVC_CfgBit_01_26_Pr5_ST3 = '" << sample->CRC_EVC_CfgBit_01_26_Pr5_ST3 << "' "
        << "EVC_01_494_Avl_ST3 = '" << sample->EVC_01_494_Avl_ST3 << "' "
        << "EVC_02_498_Avl_ST3 = '" << sample->EVC_02_498_Avl_ST3 << "' "
        << "EVC_03_623_Avl_ST3 = '" << sample->EVC_03_623_Avl_ST3 << "' "
        << "EVC_04_625_Avl_ST3 = '" << sample->EVC_04_625_Avl_ST3 << "' "
        << "EVC_05_830_Avl_ST3 = '" << sample->EVC_05_830_Avl_ST3 << "' "
        << "EVC_06_835_Avl_ST3 = '" << sample->EVC_06_835_Avl_ST3 << "' "
        << "EVC_07_460_Avl_ST3 = '" << sample->EVC_07_460_Avl_ST3 << "' "
        << "EVC_08_AddEquip_Avl_ST3 = '" << sample->EVC_08_AddEquip_Avl_ST3 << "' "
        << "EVC_09_AddEquip_Avl_ST3 = '" << sample->EVC_09_AddEquip_Avl_ST3 << "' "
        << "EVC_0A_AddEquip_Avl_ST3 = '" << sample->EVC_0A_AddEquip_Avl_ST3 << "' "
        << "EVC_0B_AddEquip_Avl_ST3 = '" << sample->EVC_0B_AddEquip_Avl_ST3 << "' "
        << "EVC_0C_465_Avl_ST3 = '" << sample->EVC_0C_465_Avl_ST3 << "' "
        << "EVC_0D_470_Avl_ST3 = '" << sample->EVC_0D_470_Avl_ST3 << "' "
        << "EVC_0E_479_Avl_ST3 = '" << sample->EVC_0E_479_Avl_ST3 << "' "
        << "EVC_0F_AddEquip_Avl_ST3 = '" << sample->EVC_0F_AddEquip_Avl_ST3 << "' "
        << "EVC_10_AddEquip_Avl_ST3 = '" << sample->EVC_10_AddEquip_Avl_ST3 << "' "
        << "EVC_11_AddEquip_Avl_ST3 = '" << sample->EVC_11_AddEquip_Avl_ST3 << "' "
        << "EVC_12_AddEquip_Avl_ST3 = '" << sample->EVC_12_AddEquip_Avl_ST3 << "' "
        << "EVC_13_AddEquip_Avl_ST3 = '" << sample->EVC_13_AddEquip_Avl_ST3 << "' "
        << "EVC_15_MED2_Avl_ST3 = '" << sample->EVC_15_MED2_Avl_ST3 << "' "
        << "EVC_16_M013_Avl_ST3 = '" << sample->EVC_16_M013_Avl_ST3 << "' "
        << "EVC_17_M014_Avl_ST3 = '" << sample->EVC_17_M014_Avl_ST3 << "' "
        << "EVC_18_M016_Avl_ST3 = '" << sample->EVC_18_M016_Avl_ST3 << "' "
        << "EVC_19_M005_Avl_ST3 = '" << sample->EVC_19_M005_Avl_ST3 << "' "
        << "EVC_1A_AddEquip_Avl_ST3 = '" << sample->EVC_1A_AddEquip_Avl_ST3 << "' "
        << "EVC_1B_MEF2_Avl_ST3 = '" << sample->EVC_1B_MEF2_Avl_ST3 << "' "
        << "EVC_1C_MEF3_Avl_ST3 = '" << sample->EVC_1C_MEF3_Avl_ST3 << "' "
        << "EVC_20_487_Avl_ST3 = '" << sample->EVC_20_487_Avl_ST3 << "' "
        << "EVC_21_488_Avl_ST3 = '" << sample->EVC_21_488_Avl_ST3 << "' "
        << "EVC_22_489_Avl_ST3 = '" << sample->EVC_22_489_Avl_ST3 << "' "
        << "EVC_23_490_Avl_ST3 = '" << sample->EVC_23_490_Avl_ST3 << "' "
        << "EVC_24_486_Avl_ST3 = '" << sample->EVC_24_486_Avl_ST3 << "' "
        << "EVC_25_AddEquip_Avl_ST3 = '" << sample->EVC_25_AddEquip_Avl_ST3 << "' "
        << "EVC_CfgBit_01_26_Stat_ST3 = '" << sample->EVC_CfgBit_01_26_Stat_ST3 << "' "
        << "SQC_EVC_CfgBit_01_26_Pr5_ST3 = '" << sample->SQC_EVC_CfgBit_01_26_Pr5_ST3 << "' "
        << "EVC_1F_215_Avl_ST3 = '" << sample->EVC_1F_215_Avl_ST3 << "' "
        << "EVC_1D_201_Avl_ST3 = '" << sample->EVC_1D_201_Avl_ST3 << "' "
        << "EVC_1E_216_Avl_ST3 = '" << sample->EVC_1E_216_Avl_ST3 << "' "
        << "EVC_14_M035_Avl_ST3 = '" << sample->EVC_14_M035_Avl_ST3 << "' ";
    }
  }
}

ara::log::Logger& ExtVehicleConfigClient::GetLogger() {
  static ara::log::Logger& logger{ara::log::CreateLogger("ExtV", "Ext Vehicle Cfg")};
  return logger;
}

} // namespace ConfigManagerApp

} // namespace application
