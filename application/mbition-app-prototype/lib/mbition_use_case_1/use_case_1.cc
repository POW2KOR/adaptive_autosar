#include "use_case_1.h"

#include "mbition/adas/proto/MbitionExampleServiceInterface.h"
#include "mbition/adas/proto/mbitionexampleserviceinterface_proxy.h"

#include <atomic>
#include <iomanip>

/*
 * Simple use-case communicating to the Classic Stack over SOME/IP. The
 * use-case searches for a service, subscribes to it and also subscribes to an
 * event that it provides.
 */

namespace mbition {
namespace use_case_1 {

std::atomic<bool> server_found{false};
std::atomic<bool> subscribed_to_events{false};
std::atomic<bool> event_received{false};

std::shared_ptr<mbition::adas::proto::proxy::MbitionExampleServiceInterfaceProxy> service_proxy;

void initialize(const std::string& cfg_path)
{
    return ara::com::Runtime::getInstance().Initialize(cfg_path);
}

/**
 * This function is registered as a callback to the event proxy and gets called
 * every time a new event is received.
 */
void result_handler(void)
{
    // Check if new events are placed into the local cache
    if (service_proxy->MbitionExampleEvent.Update()) {
        auto example_event = service_proxy->MbitionExampleEvent.GetCachedSamples().begin();

        ara::log::LogInfo() << "Event received: 0x" << std::hex << std::setfill('0') << std::setw(2)
                            << (**example_event)[0] << (**example_event)[1] << (**example_event)[2];
        event_received = true;
    }
}

void subscribe_to_events(void)
{
    // Subscribe to event
    ara::log::LogInfo() << "Setting receive handler";
    service_proxy->MbitionExampleEvent.SetReceiveHandler([]() { result_handler(); });

    ara::log::LogInfo() << "Subscribing to event";
    service_proxy->MbitionExampleEvent.Subscribe(ara::com::EventCacheUpdatePolicy::kLastN, 1);

    subscribed_to_events.store(true);
}

/**
 * Internal handler called with results from the service finder. This function
 * is also called when the finder cannot find any services. When exactly one
 * service has been found, event subscription will be triggered.
 */
void find_service_handler(const ara::com::ServiceHandleContainer<ara::com::HandleType>& services)
{
    if (services.size() == 0) {
        ara::log::LogInfo() << "No service instance found";
        return;
    } else if (services.size() == 1) {
        ara::log::LogInfo() << "Found one service instance";
        // Get proxy instance

        ara::log::LogInfo() << "Getting proxy";
        service_proxy
            = std::make_shared<mbition::adas::proto::proxy::MbitionExampleServiceInterfaceProxy>(
                services[0]);

        server_found.store(true);

        ara::log::LogInfo() << "Subscribing";
        subscribe_to_events();
    } else {
        // The example doesn't handle this case
        ara::log::LogInfo() << "Found multiple instances of service";
    }
}

ara::com::FindServiceHandle start_find_service()
{
    return mbition::adas::proto::proxy::MbitionExampleServiceInterfaceProxy::StartFindService(
        find_service_handler);
}

void stop_find_service(const ara::com::FindServiceHandle& find_service_handle)
{
    mbition::adas::proto::proxy::MbitionExampleServiceInterfaceProxy::StopFindService(
        find_service_handle);
}

bool service_found(void)
{
    return server_found.load(std::memory_order_seq_cst);
}

void deinitialize(void)
{
    if (subscribed_to_events) {
        // Unsubscribe from event
        service_proxy->MbitionExampleEvent.Unsubscribe();
        service_proxy.reset();
    }
}

} // namespace use_case_1
} // namespace mbition
