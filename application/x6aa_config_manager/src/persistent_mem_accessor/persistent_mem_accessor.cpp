/*****************************************************************************
 * \file   persistent_mem_accessor.cpp
 *
 * \brief  persistent_mem_accessor class representing the variant coding application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "persistent_mem_accessor.h"

#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"
#include "ara/core/string_view.h"
#include "vac/container/string_literals.h"

#include <utility>

namespace application {

namespace VariantCodingApp {

using namespace vac::container::literals; // NOLINT(build/namespace

PersistentMemAccessor::PersistentMemAccessor()
{
    ara::core::Result<ara::core::InstanceSpecifier> is_kvs_result
        = ara::core::InstanceSpecifier::MakeInstanceSpecifier(
            "X6AA_Cnfg_Mngr_Executable/X6AA_Cnfg_Mngr_ExecutableRootSwc/MyPersistencyKvsPrPortPrototype"_sv);

    if (is_kvs_result.HasValue()) {
        ara::per::Result<ara::per::SharedHandle<ara::per::KeyValueStorage>> result_kvs
            = ara::per::OpenKeyValueStorage(is_kvs_result.Value());

        if (result_kvs.HasValue()) {
            key_value_storage.emplace(result_kvs.Value());
        }
    }
}

void PersistentMemAccessor::StoreVariantCodingData(
    uint32_t data_to_store, const std::string& key_to_store)
{
    // try {
    //   (*key_value_storage)->SetValue<std::uint32_t>(ara::core::StringView(key_to_store),
    //   data_to_store);

    //   (*key_value_storage)->SyncToStorage();

    //   // read the data back
    //   ara::per::Result<std::uint32_t> result_data =
    //       (*key_value_storage)->GetValue<std::uint32_t>(ara::core::StringView(key_to_store));

    //   if (result_data.HasValue()) {
    //     logger_ctx.LogInfo() << "VcPersistentMemAccessor : #INFO: Data is ready to read."_sv;

    //     // We expect the data is an unsigned integer
    //     uint32_t restored_value = result_data.Value();

    //     logger_ctx.LogInfo() << "VcPersistentMemAccessor : #INFO: The read value from: "_sv <<
    //     key_to_store << " is: "_sv
    //                           << restored_value;
    //   } else {
    //     logger_ctx.LogInfo() << "Data NOT ready"_sv;
    //   }
    // } catch (const std::exception& e) {
    //   logger_ctx.LogError() << "Persistency caught std::exception! Message = "_sv << e.what();
    // } catch (...) {
    //   logger_ctx.LogError() << "Caught unknown exception!"_sv;
    // }
}

void PersistentMemAccessor::InitializeVcMemoryWithDefaultValues()
{

    /* initialize key value storage with default values */
}

uint32_t PersistentMemAccessor::ReadVariantCodingData(const std::string& key_to_store)
{
    // try {
    //   // read the data back
    //   ara::per::Result<std::uint32_t> result_data =
    //       (*key_value_storage)->GetValue<std::uint32_t>(ara::core::StringView(key_to_store));

    //   if (result_data.HasValue()) {
    //     logger_ctx.LogInfo() << "VcPersistentMemAccessor : #INFO: Data is ready to read."_sv;

    //     // We expect the data is an unsigned integer
    //     uint32_t return_value = result_data.Value();

    //     logger_ctx.LogInfo() << "VcPersistentMemAccessor : #INFO: The read value from: "_sv <<
    //     key_to_store << " is: "_sv
    //                           << return_value;
    //   } else {
    //     logger_ctx.LogInfo() << "Data NOT ready"_sv;
    //   }

    //   return return_value;

    // } catch (const std::exception& e) {
    //   logger_ctx.LogError() << "Persistency caught std::exception! Message = "_sv << e.what();
    // } catch (...) {
    //   logger_ctx.LogError() << "Caught unknown exception!"_sv;
    // }
}

configureSarTriggerEvents0136VcEventDataType PersistentMemAccessor::
    ReadConfigureSarTriggerEvents0136VcEventData()
{

    /**
     * TODO: these values are hardcoded here. Currently there is no information on persistency
     * interface in ECU extract. This code shall be updated once persistency interface has been
     * added
     */

    configureSarTriggerEvents0136VcEventDataType configureSarTriggerEvents0136VcEventData;

    /*##### configureSarTriggerEvents0136VcEventData #### */
    configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1 = 0x0;
    configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2 = 0x0;

    return configureSarTriggerEvents0136VcEventData;
}

activateSarStorage0131VcEventDataType PersistentMemAccessor::ReadActivateSarStorage0131VcEventData()
{

    /**
     * TODO: these values are hardcoded here. Currently there is no information on persistency
     * interface in ECU extract. This code shall be updated once persistency interface has been
     * added
     */

    activateSarStorage0131VcEventDataType activateSarStorage0131VcEventData;

    /*##### activateSarStorage0131VcEventData #### */
    activateSarStorage0131VcEventData.sarDataStorageStatus = 0x1;

    return activateSarStorage0131VcEventData;
}

vechicleInformation0400VcEventDataType PersistentMemAccessor::
    ReadVechicleInformation0400VcEventData()
{

    /**
     * TODO: these values are hardcoded here. Currently there is no information on persistency
     * interface in ECU extract. This code shall be updated once persistency interface has been
     * added
     */

    vechicleInformation0400VcEventDataType vechicleInformation0400VcEventData;
    vechicleInformation0400VcEventData.body_style = 0x3F;
    vechicleInformation0400VcEventData.veh_line = 0x3F;
    vechicleInformation0400VcEventData.amg_type = 0xFF;
    vechicleInformation0400VcEventData.guard_lvl_b4 = 0x0;
    vechicleInformation0400VcEventData.reserved = 0x0;
    vechicleInformation0400VcEventData.guard_lvl_b7 = 0x0;
    vechicleInformation0400VcEventData.hybrid_avl = 0x0;
    vechicleInformation0400VcEventData.plugin_hybrid_avl = 0x0;
    vechicleInformation0400VcEventData.veh_backdoors_avl = 0x0;

    return vechicleInformation0400VcEventData;
}

} // namespace VariantCodingApp

} // namespace application
