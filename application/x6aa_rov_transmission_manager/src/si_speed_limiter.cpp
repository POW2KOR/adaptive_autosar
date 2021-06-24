/*****************************************************************************
 * \file   si_speedlimiter.cpp
 *
 * \brief  ns_speedlimiter proxy implementation
 * \author
 * \date
 * \note
 ******************************************************************************/

#include "si_speed_limiter.h"

/* C system includes */

/* C++ system includes */
#include <memory>
#include <string>

namespace idc6 {
namespace rovservices {

using vac::container::literals::operator""_sv;

/* Initialization of static class members */
std::atomic<bool> SISpeedlimiter::si_speedlimiter_service_found_{false};
std::atomic<bool> SISpeedlimiter::si_speedlimiter_events_subscribed_{false};
std::shared_ptr<services::ns_speedlimiter::proxy::SI_SpeedLimiterProxy>
  SISpeedlimiter::si_speedlimiter_service_proxy_;
ara::core::InstanceSpecifier const SISpeedlimiter::
  si_speedlimiter_instance_specifier_{
  "TransmissionManager_ROVExecutable/"
  "TransmissionManager_ROVExecutableRootSwc/"
  "R_SpeedLimiter"_sv};


SISpeedlimiter::SISpeedlimiter() {
  // Empty constructor
}

SISpeedlimiter::~SISpeedlimiter() {
  // Empty destructor
}

bool SISpeedlimiter::FindService() {
  bool retval = false;
  static ara::com::FindServiceHandle find_service_handle =
  services::ns_speedlimiter::proxy::SI_SpeedLimiterProxy::
    StartFindService(FindServiceHandler, si_speedlimiter_instance_specifier_);

  /* Wait until SI_Speedlimiter service is found */
  if (!si_speedlimiter_service_found_.load()) {
    static int counter = 0;
    if (++counter % 2 == 0) {
      GetLogger().LogInfo() << "Still searching for SI_Speedlimiter service";
    }
  }  else {

    /* Stop searching for further services */
    services::ns_speedlimiter::proxy::SI_SpeedLimiterProxy::
    StopFindService(find_service_handle);
    GetLogger().LogInfo() << "Stopped searching for SI_Speedlimiter service";
    retval = true;
  }

  return retval;
}

bool SISpeedlimiter::SubscribeToEvents() {
  bool retval = false;

  /* If a service was found */
  if (si_speedlimiter_service_found_.load()) {
    /* If the events have not been subscribed already */
    if (!si_speedlimiter_events_subscribed_.load()) {
      /* Subscribe to 'Ev_Capabilities' event and set handler */
      si_speedlimiter_service_proxy_->Ev_Capabilities.SetReceiveHandler([]() {
        Ev_CapabilitiesHandler(); });
      si_speedlimiter_service_proxy_->Ev_Capabilities.Subscribe(
        ara::com::EventCacheUpdatePolicy::kLastN, 1);

      /* Subscribe to 'Ev_SpeedLimiterState' event and set handler */
      si_speedlimiter_service_proxy_->Ev_SpeedLimiterState.SetReceiveHandler([]() {
        Ev_SpeedLimiterStateHandler(); });
      si_speedlimiter_service_proxy_->Ev_SpeedLimiterState.Subscribe(
        ara::com::EventCacheUpdatePolicy::kLastN, 1);

      /* Remember that the events are subscribed */
      si_speedlimiter_events_subscribed_.store(true);

      retval = true;
    }
  }

  return retval;
}

bool SISpeedlimiter::UnsubscribeFromEvents() {
  bool retval = false;

  /* If the events had been subscribed */
  if (si_speedlimiter_events_subscribed_.load()) {
    /* Unsubscribe from events */
    si_speedlimiter_service_proxy_->Ev_Capabilities.Unsubscribe();
    si_speedlimiter_service_proxy_->Ev_SpeedLimiterState.Unsubscribe();

    /* Remember that the events are not subscribed */
    si_speedlimiter_events_subscribed_.store(false);

    retval = true;
  }

  return retval;
}

bool SISpeedlimiter::IsServiceFound() {
  return si_speedlimiter_service_found_.load();
}

ara::core::Future<services::ns_speedlimiter::proxy::methods::Meth_GetCapabilities::
  Output> SISpeedlimiter::Meth_GetCapabilities(void) {
  ara::core::Future<services::ns_speedlimiter::proxy::methods::Meth_GetCapabilities::
    Output> delete_future = si_speedlimiter_service_proxy_->Meth_GetCapabilities();

  return delete_future;
}

void SISpeedlimiter::Meth_RequestSpeedLimit(::DataTypes::VSLim_RequestLimit_In::VSLim_RequestLimit_In const& data) {
  ara::core::Future<services::ns_speedlimiter::proxy::methods::
    Meth_RequestSpeedLimit::Output> val = si_speedlimiter_service_proxy_->Meth_RequestSpeedLimit(data);
}

void SISpeedlimiter::FindServiceHandler(
  ara::com::ServiceHandleContainer<services::ns_speedlimiter::proxy::
    SI_SpeedLimiterProxy::HandleType> si_speedlimiter_services) {
  /* If there was no service found */
  if (si_speedlimiter_services.size() == 0) {
    GetLogger().LogInfo() << "No SI_Speedlimiter service instance found";
    return;
  } else if (si_speedlimiter_services.size() == 1) {
    /* If there is exactly one service found */
    GetLogger().LogInfo() << "Found one SI_Speedlimiter service instance";

    /* Get proxy instance */
    si_speedlimiter_service_proxy_ =
      std::make_shared<services::ns_speedlimiter::proxy::
    SI_SpeedLimiterProxy>(si_speedlimiter_services[0]);

    /* Remember that a service is found */
    si_speedlimiter_service_found_.store(true);
  } else {
    /* If there are multiple services found */
    GetLogger().LogInfo() << "Found multiple instances of SI_Speedlimiter service, use the first one";

    /* Get proxy instance */
    si_speedlimiter_service_proxy_ =
      std::make_shared<services::ns_speedlimiter::proxy::SI_SpeedLimiterProxy>(si_speedlimiter_services[0]);

    /* Remember that a service is found */
    si_speedlimiter_service_found_.store(true);
  }
}

void SISpeedlimiter::Ev_CapabilitiesHandler() {
  GetLogger().LogDebug() << "Handler got called.";

  /* If there are events available */
  if (si_speedlimiter_service_proxy_->Ev_Capabilities.Update()) {
    auto samples = si_speedlimiter_service_proxy_->Ev_Capabilities.GetCachedSamples();

    GetLogger().LogDebug() << "Received " << samples.size() << " samples";

    for (auto &sample : samples) {
      GetLogger().LogInfo() << "SI_Speedlimiter service: Received event 'Ev_Capabilities' with: "
        << "minimum_speed_limit = '" << sample->minimum_speed_limit << "' ";
    }
  }
}

void SISpeedlimiter::Ev_SpeedLimiterStateHandler() {
  GetLogger().LogDebug() << "Handler got called.";

  /* If there are events available */
  if (si_speedlimiter_service_proxy_->Ev_SpeedLimiterState.Update()) {
    auto samples = si_speedlimiter_service_proxy_->Ev_SpeedLimiterState.GetCachedSamples();

    GetLogger().LogDebug() << "Received " << samples.size() << " samples";

    for (auto &sample : samples) {
      GetLogger().LogInfo() << "SI_Speedlimiter service: Received event 'Ev_SpeedLimiterState' with: "
        << "variable.speed_limit = '" << sample->variable.speed_limit << "' "
        << "variable.no_speed_limit = '" << sample->variable.no_speed_limit << "' "
        << "variable.limiter_activity = '" << sample->variable.limiter_activity << "' "
        << "permanent.speed_limit = '" << sample->permanent.speed_limit << "' "
        << "permanent.no_speed_limit = '" << sample->permanent.no_speed_limit << "' "
        << "permanent.limiter_activity = '" << sample->permanent.limiter_activity << "' ";
    }
  }
}

ara::log::Logger& SISpeedlimiter::GetLogger() {
  static ara::log::Logger& logger{ara::log::CreateLogger("SpdLim", "SI Speed Limit")};
  return logger;
}

}  // namespace rovservices
}  // namespace idc6
