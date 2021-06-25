/*****************************************************************************
 * \file   diagnostic_ssa_client.cpp
 *
 * \brief  SSA client implementation for receiving variant coding data
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/
/* include own header first to ensure that is self contained */
#include "diagnostic_ssa_client.h"

/* C system includes */

/* C++ system includes */
#include <memory>
#include <string>

/* Project specific includes */

using vac::container::literals::operator""_sv;

namespace application {

namespace ConfigManagerApp {

std::atomic<bool> DiagnosticSsaClient::ssa_variant_coding_service_found{false};
std::atomic<bool> DiagnosticSsaClient::ssa_variant_coding_events_subscribed{false};
std::shared_ptr<
    services::ns_si_dummyswc_2_to_cnfg_mngr::proxy::SI_X6AA_Dummy_B2_Service_ReservedProxy>
    DiagnosticSsaClient::ssa_variant_coding_service_proxy;
ara::core::InstanceSpecifier const DiagnosticSsaClient::ssa_variant_coding_instance_specifier{
    "X6AA_Cnfg_Mngr_Executable/"
    "X6AA_Cnfg_Mngr_ExecutableRootSwc/"
    "AdaptiveRequiredPortType108"_sv};

ara::log::Logger& DiagnosticSsaClient::GetLoggerForSsaClient()
{
    static ara::log::Logger& logger{ara::log::CreateLogger("SSAP", "SSA Proxy")};
    return logger;
}

DiagnosticSsaClient::DiagnosticSsaClient()
{
}

DiagnosticSsaClient::~DiagnosticSsaClient()
{
}

bool DiagnosticSsaClient::FindService()
{
    bool retval = true;
    int counter = 0;
    uint32_t max_try_count
        = 1000; /* one while loop count is of nearly 100ms and timeout would be 100s (1000*100ms)*/

    /* Start searching for variant coding services offered by SSA module */
    GetLoggerForSsaClient().LogInfo()
        << "Start searching for variant coding services offered by SSA module";
    ara::com::FindServiceHandle find_service_handle
        = services::ns_si_dummyswc_2_to_cnfg_mngr::proxy::SI_X6AA_Dummy_B2_Service_ReservedProxy::
            StartFindService(FindSsaServiceHandler, ssa_variant_coding_instance_specifier);

    /* Wait until variant coding services offered by SSA module is found */
    while (!ssa_variant_coding_service_found.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (counter % 100 == 0) {
            GetLoggerForSsaClient().LogInfo()
                << "Still searching for variant coding services offered by SSA module";
        }
        if (max_try_count == 0) {
            GetLoggerForSsaClient().LogFatal()
                << "Failed to find variant coding services offered by SSA module "
                   "-- timeout occured";
            retval = false;
            break;
        }
        counter++;
        max_try_count--;
    }

    /* Stop searching for further services */
    services::ns_si_dummyswc_2_to_cnfg_mngr::proxy::SI_X6AA_Dummy_B2_Service_ReservedProxy::
        StopFindService(find_service_handle);
    GetLoggerForSsaClient().LogInfo()
        << "Stopped searching for variant coding services offered by SSA module";

    return retval;
}

bool DiagnosticSsaClient::SubscribeToEvents()
{
    bool retval = false;

    /* If a service was found */
    if (ssa_variant_coding_service_found.load()) {
        /* If the events have not been subscribed already */
        if (!ssa_variant_coding_events_subscribed.load()) {
            /* Subscribe to events and set handlers */
            ssa_variant_coding_service_proxy->Ev_CalculationResult.SetReceiveHandler(
                []() { EventHandlerForSsaVariantCodingData(); });
            ssa_variant_coding_service_proxy->Ev_CalculationResult.Subscribe(
                ara::com::EventCacheUpdatePolicy::kLastN, 1);

            /* Remember that the events are subscribed */
            ssa_variant_coding_events_subscribed.store(true);

            retval = true;
        }
    }

    return retval;
}

bool DiagnosticSsaClient::UnsubscribeFromEvents()
{
    bool retval = false;

    /* If the events had been subscribed */
    if (ssa_variant_coding_events_subscribed.load()) {
        /* Unsubscribe from events */
        ssa_variant_coding_service_proxy->Ev_CalculationResult.Unsubscribe();

        /* Remember that the events are not subscribed */
        ssa_variant_coding_events_subscribed.store(false);

        retval = true;
    }

    return retval;
}

void DiagnosticSsaClient::FindSsaServiceHandler(
    ara::com::ServiceHandleContainer<services::ns_si_dummyswc_2_to_cnfg_mngr::proxy::
                                         SI_X6AA_Dummy_B2_Service_ReservedProxy::HandleType>
        ssa_variant_coding_services)
{
    /* If there was no service found */
    if (ssa_variant_coding_services.size() == 0) {
        GetLoggerForSsaClient().LogInfo()
            << "No instance of variant coding services offered by SSA module found";
        return;
    } else if (ssa_variant_coding_services.size() == 1) {
        /* If there is exactly one service found */
        GetLoggerForSsaClient().LogInfo()
            << "Found one instance of variant coding services offered by SSA module";
    } else {
        /* If there are multiple services found */
        GetLoggerForSsaClient().LogInfo()
            << "Found multiple instances of variant coding services offered by "
               "SSA module, use the first one";
    }
    /* Get proxy instance */
    ssa_variant_coding_service_proxy = std::make_shared<
        services::ns_si_dummyswc_2_to_cnfg_mngr::proxy::SI_X6AA_Dummy_B2_Service_ReservedProxy>(
        ssa_variant_coding_services[0]);

    /* Remember that a service is found */
    ssa_variant_coding_service_found.store(true);
}

void DiagnosticSsaClient::EventHandlerForSsaVariantCodingData()
{
    GetLoggerForSsaClient().LogInfo() << "EventHandlerForSsaVariantCodingData got called.";

    /* If there are events available */
    if (ssa_variant_coding_service_proxy->Ev_CalculationResult.Update()) {
        auto samples = ssa_variant_coding_service_proxy->Ev_CalculationResult.GetCachedSamples();

        GetLoggerForSsaClient().LogInfo() << "Received " << samples.size() << " samples";

        /* FIXME: Currently, we don't have concrete information on ara::com interfaces provided by
         * SSA and dummy SSA server is only providing one Ev_CalculationResult event which sends
         * integer type data, therfore, to keep initial implementation simple it's assumed that
         * event of dummy SSA server is providing vehicleInformation_body_style variant coding
         * data. This code will change significantly once we have information on SSA ara::com
         * intefaces and event handlers will also be revisited at that time.
         * */
        for (auto& sample : samples) {
            GetLoggerForSsaClient().LogInfo()
                << "SSA Client: Received event with: "
                << "vehicleInformation_body_style        = '" << (*sample) << "' ";
            application::VariantCodingApp::SingletonPersistentMemAccessor* memAccessor
                = application::VariantCodingApp::SingletonPersistentMemAccessor::getInstance();
            /* FIXME: SSA client will not invoke memAccessor functions directly. Instead it
             * will use intefaces provided by diagnostic transformer element. Since, we don't have
             * diagnostic transformer implemented therefore Read function are used here directly for
             * verifying complete functionality of config manager application.
             * */
            auto read_result = memAccessor->ReadDataForVechicleInformation0400VcEvent();
            ara::core::Result<void> write_result;
            if (read_result.HasValue()) {
                auto val = read_result.Value();
                if (val.body_style != (*sample)) {
                    val.body_style = (*sample);
                    /* FIXME: SSA client will pass variant coding information to param validator and
                     * param validator shall cross validate this data with EVC signals coming from
                     * BUS. Upon successful verification, param validator shall store data to
                     * persistent memory. Since, param validator isn't implemented yet therefore we
                     * are using memAccessor instance directly here.
                     * */
                    write_result = memAccessor->StoreDataForVechicleInformation0400VcEvent(val);
                }
            }
            if (write_result.HasValue()) {
                GetLoggerForSsaClient().LogInfo()
                    << "SSA client received body_style =" << (*sample)
                    << "variant coding data and store it to persistent memory";
            } else {
                GetLoggerForSsaClient().LogError() << "SSA client couldn't store newly received "
                                                      "variant coding data in persistent memory";
            }
        }
    }
}

} // namespace ConfigManagerApp

} // namespace application
