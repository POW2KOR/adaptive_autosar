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

bool PersistentMemAccessor::ReadVariantCodingData(
    const std::string& key_to_read, std::uint32_t& read_value)
{
    bool return_value = false;
    try {
        // read the data back
        ara::per::Result<std::uint32_t> result_data
            = (*key_value_storage)->GetValue<std::uint32_t>(ara::core::StringView(key_to_read));

        if (result_data.HasValue()) {
            logger_ctx.LogInfo() << "VcPersistentMemAccessor : #INFO: Data is ready to read."_sv;

            // We expect the data is an unsigned integer
            read_value = result_data.Value();
            return_value = true;
            logger_ctx.LogInfo() << "VcPersistentMemAccessor : #INFO: The read value from: "_sv
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
    if (!ReadVariantCodingData(
            "triggerEventActivationStatusByte1",
            configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1)) {
        retval = false;
    }

    if (!ReadVariantCodingData(
            "triggerEventActivationStatusByte2",
            configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2)) {
        retval = false;
    }
    return retval;
}

bool PersistentMemAccessor::ReadActivateSarStorage0131VcEventData(
    activateSarStorage0131VcEventDataType& activateSarStorage0131VcEventData)
{
    bool retval = true;
    if (!ReadVariantCodingData(
            "sarDataStorageStatus", activateSarStorage0131VcEventData.sarDataStorageStatus)) {
        retval = false;
    }
    return retval;
}

bool PersistentMemAccessor::ReadVechicleInformation0400VcEventData(
    vechicleInformation0400VcEventDataType& vechicleInformation0400VcEventData)
{
    bool retval = true;
    if (!ReadVariantCodingData("body_style", vechicleInformation0400VcEventData.body_style)) {
        retval = false;
    }

    if (!ReadVariantCodingData("veh_line", vechicleInformation0400VcEventData.veh_line)) {
        retval = false;
    }

    if (!ReadVariantCodingData("amg_type", vechicleInformation0400VcEventData.amg_type)) {
        retval = false;
    }

    if (!ReadVariantCodingData("guard_lvl_b4", vechicleInformation0400VcEventData.guard_lvl_b4)) {
        retval = false;
    }

    if (!ReadVariantCodingData("reserved", vechicleInformation0400VcEventData.reserved)) {
        retval = false;
    }

    if (!ReadVariantCodingData("guard_lvl_b7", vechicleInformation0400VcEventData.guard_lvl_b7)) {
        retval = false;
    }

    if (!ReadVariantCodingData("hybrid_avl", vechicleInformation0400VcEventData.hybrid_avl)) {
        retval = false;
    }

    if (!ReadVariantCodingData(
            "plugin_hybrid_avl", vechicleInformation0400VcEventData.plugin_hybrid_avl)) {
        retval = false;
    }

    if (!ReadVariantCodingData(
            "veh_backdoors_avl", vechicleInformation0400VcEventData.veh_backdoors_avl)) {
        retval = false;
    }

    return retval;
}

} // namespace VariantCodingApp

} // namespace application
