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
    if (!InitializeVcMemoryWithDefaultValues()) {
        logger_ctx.LogFatal()
            << "VcPersistentMemAccessor : unable to initialize persistent data."_sv;
    }
    has_kvs_initialization_failed = false;
}

bool PersistentMemAccessor::StoreVariantCodingData(
    const std::string& key_to_store, uint32_t data_to_store)
{
    bool retval = false;
    try {
        (*key_value_storage)
            ->SetValue<std::uint32_t>(ara::core::StringView(key_to_store), data_to_store);

        (*key_value_storage)->SyncToStorage();
        logger_ctx.LogInfo() << "VcPersistentMemAccessor : #Writing: store key: "_sv
                             << key_to_store << " with value: "_sv << data_to_store;

        // read the data back
        ara::per::Result<std::uint32_t> result_data
            = (*key_value_storage)->GetValue<std::uint32_t>(ara::core::StringView(key_to_store));

        if (result_data.HasValue()) {

            // We expect the data is an unsigned integer
            uint32_t restored_value = result_data.Value();

            // check the value??
            retval = (data_to_store == restored_value) ? true : false;

            logger_ctx.LogInfo() << "VcPersistentMemAccessor : #Writing: The written value for : "_sv
                                 << key_to_store << " is: "_sv << restored_value;
        } else {
            logger_ctx.LogInfo() << "Data NOT ready"_sv;
        }
    } catch (const std::exception& e) {
        logger_ctx.LogError() << "Persistency caught std::exception! Message = "_sv << e.what();
    } catch (...) {
        logger_ctx.LogError() << "Caught unknown exception!"_sv;
    }
    return retval;
}

bool PersistentMemAccessor::StoreConfigureSarTriggerEvents0136VcEventData(
    configureSarTriggerEvents0136VcEventDataType& configureSarTriggerEvents0136VcEventData)
{
    bool retval = true;

    if (!StoreVariantCodingData(
            "triggerEventActivationStatusByte1",
            configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1)) {
        retval = false;
    }

    if (!StoreVariantCodingData(
            "triggerEventActivationStatusByte2",
            configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2)) {
        retval = false;
    }

    return retval;
}

bool PersistentMemAccessor::StoreActivateSarStorage0131VcEventData(
    activateSarStorage0131VcEventDataType& activateSarStorage0131VcEventData)
{
    bool retval = true;

    if (!StoreVariantCodingData(
            "sarDataStorageStatus", activateSarStorage0131VcEventData.sarDataStorageStatus)) {
        retval = false;
    }

    return retval;
}

bool PersistentMemAccessor::StoreVechicleInformation0400VcEventData(
    vechicleInformation0400VcEventDataType& vechicleInformation0400VcEventData)
{
    bool retval = true;

    if (!StoreVariantCodingData("body_style", vechicleInformation0400VcEventData.body_style)) {
        retval = false;
    }

    if (!StoreVariantCodingData("veh_line", vechicleInformation0400VcEventData.veh_line)) {
        retval = false;
    }

    if (!StoreVariantCodingData("amg_type", vechicleInformation0400VcEventData.amg_type)) {
        retval = false;
    }

    if (!StoreVariantCodingData("guard_lvl_b4", vechicleInformation0400VcEventData.guard_lvl_b4)) {
        retval = false;
    }

    if (!StoreVariantCodingData("reserved", vechicleInformation0400VcEventData.reserved)) {
        retval = false;
    }

    if (!StoreVariantCodingData("guard_lvl_b7", vechicleInformation0400VcEventData.guard_lvl_b7)) {
        retval = false;
    }

    if (!StoreVariantCodingData("hybrid_avl", vechicleInformation0400VcEventData.hybrid_avl)) {
        retval = false;
    }

    if (!StoreVariantCodingData(
            "plugin_hybrid_avl", vechicleInformation0400VcEventData.plugin_hybrid_avl)) {
        retval = false;
    }

    if (!StoreVariantCodingData(
            "veh_backdoors_avl", vechicleInformation0400VcEventData.veh_backdoors_avl)) {
        retval = false;
    }

    return retval;
}

bool PersistentMemAccessor::InitializeVcMemoryWithDefaultValues()
{
    bool retval = true;
    /* initialize key value storage with default values */

    /*##### configureSarTriggerEvents0136VcEventData #### */
    configureSarTriggerEvents0136VcEventDataType configureSarTriggerEvents0136VcEventData;
    configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1 = 0x0;
    configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2 = 0x0;
    if (!StoreConfigureSarTriggerEvents0136VcEventData(configureSarTriggerEvents0136VcEventData)) {
        retval = false;
    }

    /*##### activateSarStorage0131VcEventData #### */
    activateSarStorage0131VcEventDataType activateSarStorage0131VcEventData;
    activateSarStorage0131VcEventData.sarDataStorageStatus = 0x1;
    if (!StoreActivateSarStorage0131VcEventData(activateSarStorage0131VcEventData)) {
        retval = false;
    }
    /*##### vechicleInformation0400VcEventData #### */
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
    if (!StoreVechicleInformation0400VcEventData(vechicleInformation0400VcEventData)) {
        retval = false;
    }

    return retval;
}

bool PersistentMemAccessor::ReadVariantCodingData(
    const std::string& key_to_read, std::uint32_t& read_value)
{
    bool return_value = false;
    try {
        // read the data back
        ara::per::Result<std::uint32_t> result_data
            = (*key_value_storage)->GetValue<std::uint32_t>(ara::core::StringView(key_to_read));

        if (result_data.HasValue()) {
            logger_ctx.LogInfo() << "VcPersistentMemAccessor : #Reading: Data is ready to read."_sv;

            // We expect the data is an unsigned integer
            read_value = result_data.Value();
            return_value = true;
            logger_ctx.LogInfo() << "VcPersistentMemAccessor : #Reading: The read value from: "_sv
                                 << key_to_read << " is: "_sv << result_data.Value();
        } else {
            logger_ctx.LogInfo() << "Data NOT ready"_sv;
        }

    } catch (const std::exception& e) {
        logger_ctx.LogError() << "Persistency caught std::exception! Message = "_sv << e.what();
    } catch (...) {
        logger_ctx.LogError() << "Caught unknown exception!"_sv;
    }
    return return_value;
}

bool PersistentMemAccessor::ReadConfigureSarTriggerEvents0136VcEventData(
    configureSarTriggerEvents0136VcEventDataType& configureSarTriggerEvents0136VcEventData)
{
    bool retval = true;
    std::uint32_t read_value = 0;
    if (ReadVariantCodingData("triggerEventActivationStatusByte1", read_value)) {
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1
            = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("triggerEventActivationStatusByte2", read_value)) {
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2
            = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    return retval;
}

bool PersistentMemAccessor::ReadActivateSarStorage0131VcEventData(
    activateSarStorage0131VcEventDataType& activateSarStorage0131VcEventData)
{
    bool retval = true;
    std::uint32_t read_value = 0;
    if (ReadVariantCodingData("sarDataStorageStatus", read_value)) {
        activateSarStorage0131VcEventData.sarDataStorageStatus = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    return retval;
}

bool PersistentMemAccessor::ReadVechicleInformation0400VcEventData(
    vechicleInformation0400VcEventDataType& vechicleInformation0400VcEventData)
{
    std::uint32_t read_value = 0;
    bool retval = true;

    if (ReadVariantCodingData("body_style", read_value)) {
        vechicleInformation0400VcEventData.body_style = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("veh_line", read_value)) {
        vechicleInformation0400VcEventData.veh_line = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("amg_type", read_value)) {
        vechicleInformation0400VcEventData.amg_type = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("guard_lvl_b4", read_value)) {
        vechicleInformation0400VcEventData.guard_lvl_b4 = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("reserved", read_value)) {
        vechicleInformation0400VcEventData.reserved = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("guard_lvl_b7", read_value)) {
        vechicleInformation0400VcEventData.guard_lvl_b7 = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("hybrid_avl", read_value)) {
        vechicleInformation0400VcEventData.hybrid_avl = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("plugin_hybrid_avl", read_value)) {
        vechicleInformation0400VcEventData.plugin_hybrid_avl = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    if (ReadVariantCodingData("veh_backdoors_avl", read_value)) {
        vechicleInformation0400VcEventData.veh_backdoors_avl = static_cast<uint8_t>(read_value);
    } else {
        retval = false;
    }

    return retval;
}

} // namespace VariantCodingApp

} // namespace application
