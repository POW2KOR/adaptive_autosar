/*****************************************************************************
 * \file   variant_coding_consumer.cpp
 *
 * \brief  VariantCodingService proxy implementation
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date   
 * \note   TODO: additional notes
 ******************************************************************************/
/* include own header first to ensure that is self contained */
#include "variant_coding_consumer.h"

/* C system includes */


/* C++ system includes */
#include <memory>
#include <string>

/* Project specific includes */

using vac::container::literals::operator""_sv;

namespace application {

std::atomic<bool> VariantCodingConsumer::variant_coding_service_found{false};
std::atomic<bool> VariantCodingConsumer::variant_coding_events_subscribed{false};
std::shared_ptr<services::ns_si_cnfg_mngr_to_dummyswc::proxy::SI_X6AA_Cnfg_Mngr_Service_ReservedProxy>
  VariantCodingConsumer::variant_coding_service_proxy;
ara::core::InstanceSpecifier const VariantCodingConsumer::variant_coding_instance_specifier{
  "X6AA_Dummy_SWC_1_Executable/"
  "X6AA_Dummy_SWC_1_ExecutableRootSwc/"
  "AdaptiveRequiredPortType110"_sv};

VariantCodingConsumer::VariantCodingConsumer() {}


VariantCodingConsumer::~VariantCodingConsumer() {}


bool VariantCodingConsumer::FindService() {
  bool retval = true;
  uint32_t max_try_count = 1000; /* one while loop count is of nearly 10ms and timeout would be 100s (1000*10ms)*/

  /* Start searching for VariantCodingService */
  GetLogger().LogInfo() << "Start searching for VariantCoding Service";
  ara::com::FindServiceHandle find_service_handle =
  services::ns_si_cnfg_mngr_to_dummyswc::proxy::SI_X6AA_Cnfg_Mngr_Service_ReservedProxy::
  StartFindService(FindServiceHandler, variant_coding_instance_specifier);

  /* Wait until VariantCodingService is found */
  while (!variant_coding_service_found.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    static int counter = 0;
    if (++counter % 10 == 0) {
      GetLogger().LogInfo() << "Still searching for VariantCodingService";
    }
    if (--max_try_count == 0)
    {
      GetLogger().LogFatal() << "Failed to find VariantCodingService -- timeout occured";
      retval = false;
      break;
    }
  }

  /* Stop searching for further services */
  services::ns_si_cnfg_mngr_to_dummyswc::proxy::SI_X6AA_Cnfg_Mngr_Service_ReservedProxy::
  StopFindService(find_service_handle);
  GetLogger().LogInfo() << "Stopped searching for VariantCodingService";

  return retval;
}


bool VariantCodingConsumer::SubscribeToEvents() {
  bool retval = false;

  /* If a service was found */
  if (variant_coding_service_found.load()) {
    /* If the events have not been subscribed already */
    if (!variant_coding_events_subscribed.load()) {
      /* Subscribe to events and set handlers */
      variant_coding_service_proxy->Ev_vechicleInformation0400VcEvent.SetReceiveHandler([]() {
        VechicleInformation0400VcEventHandler(); });
      variant_coding_service_proxy->Ev_vechicleInformation0400VcEvent.Subscribe(
        ara::com::EventCacheUpdatePolicy::kLastN, 1);

      /* Remember that the events are subscribed */
      variant_coding_events_subscribed.store(true);

      retval = true;
    }
  }

  return retval;
}


bool VariantCodingConsumer::UnsubscribeFromEvents() {
  bool retval = false;

  /* If the events had been subscribed */
  if (variant_coding_events_subscribed.load()) {
    /* Unsubscribe from events */
    variant_coding_service_proxy->Ev_vechicleInformation0400VcEvent.Unsubscribe();

    /* Remember that the events are not subscribed */
    variant_coding_events_subscribed.store(false);

    retval = true;
  }

  return retval;
}


void VariantCodingConsumer::FindServiceHandler(
  ara::com::ServiceHandleContainer<services::ns_si_cnfg_mngr_to_dummyswc::proxy::SI_X6AA_Cnfg_Mngr_Service_ReservedProxy::HandleType> 
  variant_coding_services) {
  /* If there was no service found */
  if (variant_coding_services.size() == 0) {
    GetLogger().LogInfo() << "No VariantCodingService instance found";
    return;
  } else if (variant_coding_services.size() == 1) {
    /* If there is exactly one service found */
    GetLogger().LogInfo() << "Found one VariantCodingService instance";
  } else {
    /* If there are multiple services found */
    GetLogger().LogInfo() << "Found multiple instances of VariantCodingService, use the first one";
  }
  /* Get proxy instance */
  variant_coding_service_proxy =
    std::make_shared<services::ns_si_cnfg_mngr_to_dummyswc::proxy::SI_X6AA_Cnfg_Mngr_Service_ReservedProxy> 
    (variant_coding_services[0]);

  /* Remember that a service is found */
  variant_coding_service_found.store(true);
}


void VariantCodingConsumer::VechicleInformation0400VcEventHandler() {
  GetLogger().LogInfo() << "VechicleInformation0400VcEventHandler got called.";

  /* If there are events available */
  if (variant_coding_service_proxy->Ev_vechicleInformation0400VcEvent.Update()) {
    auto samples = variant_coding_service_proxy->Ev_vechicleInformation0400VcEvent.GetCachedSamples();

    GetLogger().LogInfo() << "Received " << samples.size() << " samples";

     for (auto &sample : samples) {
       GetLogger().LogInfo() << "Variant Coding: Received event with: "
         << "vechicleInformation_body_style        = '" << sample->body_style << "' "
         << "vechicleInformation_veh_line          = '" << sample->veh_line << "' "
         << "vechicleInformation_amg_type          = '" << sample->amg_type << "' "
         << "vechicleInformation_guard_lvl_b4      = '" << sample->guard_lvl_b4 << "' "
         << "vechicleInformation_reserved          = '" << sample->reserved << "' "
         << "vechicleInformation_guard_lvl_b7      = '" << sample->guard_lvl_b7 << "' "
         << "vechicleInformation_hybrid_avl        = '" << sample->hybrid_avl << "' "
         << "vechicleInformation_plugin_hybrid_avl = '" << sample->plugin_hybrid_avl << "' "
         << "vechicleInformation_veh_backdoors_avl = '" << sample->veh_backdoors_avl << "' ";
     }
  }
}


ara::log::Logger& VariantCodingConsumer::GetLogger() {
  static ara::log::Logger& logger{ara::log::CreateLogger("VcCnsm", "Variant Coding Consumer")};
  return logger;
}


}  // namespace application
