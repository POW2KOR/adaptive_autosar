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
#include "x6aa_config_manager_error_domain.h"

#include <utility>

namespace application {

namespace VariantCodingApp {

using namespace vac::container::literals; // NOLINT(build/namespace

PersistentMemAccessor::PersistentMemAccessor()
{
    ara::core::Result<ara::core::InstanceSpecifier> kvs_instance_specifier
        = ara::core::InstanceSpecifier::MakeInstanceSpecifier(
            "X6AA_Cnfg_Mngr_Executable/X6AA_Cnfg_Mngr_ExecutableRootSwc/MyPersistencyKvsPrPortPrototype"_sv);

    if (kvs_instance_specifier.HasValue()) {
        ara::per::Result<ara::per::SharedHandle<ara::per::KeyValueStorage>> opened_kvs
            = ara::per::OpenKeyValueStorage(kvs_instance_specifier.Value());

        if (opened_kvs.HasValue()) {
            key_value_storage.emplace(opened_kvs.Value());
            logger_ctx.LogFatal() << "config manager is able to open key value storage."_sv;
        }
    }
    has_kvs_initialized_with_default_values = false;
    logger_ctx.SetPrefix("VcPersistentMemAccessor : "_sv);
}

template<typename dataType>
ara::core::Result<void> PersistentMemAccessor::StoreVariantCodingData(
    const variantCodingKeys key_to_store, dataType data_to_store)
{
    ara::core::Result<void> write_result;
    ara::core::String key = kvs_enum_to_string_key(key_to_store);
    try {
        if (key.empty()) {
            throw std::invalid_argument("invalid key");
        }
        // Insert values into the database.
        write_result
            = (*key_value_storage)->SetValue<dataType>(ara::core::StringView(key), data_to_store);

        logger_ctx.LogInfo() << "Writing to store key: " << key << " with value: " << data_to_store;

        // Test if data was stored and print the value.
        // read the data back
        ara::per::Result<dataType> result_data
            = (*key_value_storage)->GetValue<dataType>(ara::core::StringView(key));

        if (result_data.HasValue() && write_result.HasValue()) {
            logger_ctx.LogInfo() << "The value written for : "
                                 << kvs_enum_to_string_key(key_to_store)
                                 << " is: " << result_data.Value();
            // Persist the database.
            (*key_value_storage)->SyncToStorage();
        } else {
            logger_ctx.LogInfo() << "Data NOT ready"_sv;
            write_result.FromError(
                X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed, "Writing Failed");
        }
    } catch (const std::invalid_argument& e) {
        logger_ctx.LogError() << "Caught std::exception! Message = " << e.what();
    } catch (const std::exception& e) {
        logger_ctx.LogError() << "Caught std::exception! Message = " << e.what();
    } catch (...) {
        logger_ctx.LogError() << "Caught unknown exception!"_sv;
    }
    return write_result;
}

ara::core::Result<void> PersistentMemAccessor::StoreDataForConfigureSarTriggerEvents0136VcEvent(
    configureSarTriggerEvents0136VcEventDataType& configureSarTriggerEvents0136VcEventData)
{
    ara::core::Result<void> result;

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::triggerEventActivationStatusByte1,
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "triggerEventActivationStatusByte1 Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::triggerEventActivationStatusByte2,
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2);

    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "triggerEventActivationStatusByte2 Writing Failed");
    }

    return result;
}

ara::core::Result<void> PersistentMemAccessor::StoreDataForActivateSarStorage0131VcEvent(
    activateSarStorage0131VcEventDataType& activateSarStorage0131VcEventData)
{
    ara::core::Result<void> result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::sarDataStorageStatus,
        activateSarStorage0131VcEventData.sarDataStorageStatus);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "sarDataStorageStatus Writing Failed");
    }
    return result;
}

ara::core::Result<void> PersistentMemAccessor::StoreDataForVechicleInformation0400VcEvent(
    vechicleInformation0400VcEventDataType& vechicleInformation0400VcEventData)
{
    ara::core::Result<void> result;

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::bodyStyle, vechicleInformation0400VcEventData.body_style);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "body_style Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::vehLine, vechicleInformation0400VcEventData.veh_line);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed, "veh_line Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::amgType, vechicleInformation0400VcEventData.amg_type);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed, "amg_type Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::guardLvlB4, vechicleInformation0400VcEventData.guard_lvl_b4);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "guard_lvl_b4 Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::guardLvlB7, vechicleInformation0400VcEventData.guard_lvl_b7);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "guard_lvl_b7 Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::reserved400, vechicleInformation0400VcEventData.reserved);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed, "reserved Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::hybridAvl, vechicleInformation0400VcEventData.hybrid_avl);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "hybrid_avl Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::pluginHybridAvl, vechicleInformation0400VcEventData.plugin_hybrid_avl);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "plugin_hybrid_avl Writing Failed");
    }

    result = StoreVariantCodingData<uint8_t>(
        variantCodingKeys::vehBackdoorsAvl, vechicleInformation0400VcEventData.veh_backdoors_avl);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "veh_backdoors_avl Writing Failed");
    }

    return result;
}

ara::core::Result<void> PersistentMemAccessor::InitializeVcMemoryWithDefaultValues()
{
    ara::core::Result<void> result;
    // initialize key value storage with default values

    // ##### configureSarTriggerEvents0136VcEventData ####
    configureSarTriggerEvents0136VcEventDataType configureSarTriggerEvents0136VcEventData;
    configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1 = 0x0;
    configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2 = 0x0;
    result = StoreDataForConfigureSarTriggerEvents0136VcEvent(
        configureSarTriggerEvents0136VcEventData);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "Memory initialization with default values for DID 0x136 has been failed");
    }

    // ##### activateSarStorage0131VcEventData ####
    activateSarStorage0131VcEventDataType activateSarStorage0131VcEventData;
    activateSarStorage0131VcEventData.sarDataStorageStatus = 0x1;
    result = StoreDataForActivateSarStorage0131VcEvent(activateSarStorage0131VcEventData);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "Memory initialization with default values for DID 0x131 has been failed");
    }

    // ##### vechicleInformation0400VcEventData ####
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
    result = StoreDataForVechicleInformation0400VcEvent(vechicleInformation0400VcEventData);
    if (!result.HasValue()) {
        return result.FromError(
            X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed,
            "Memory initialization with default values for DID 0x400 has been failed");
    }

    return result;
}

template<typename dataType>
bool PersistentMemAccessor::TryReadingDataFromKvs(
    const ara::core::String& key_to_read, dataType& read_value)
{
    bool return_value = false;
    ara::per::Result<dataType> result_data
        = (*key_value_storage)->GetValue<dataType>(ara::core::StringView(key_to_read));

    if (result_data.HasValue()) {
        logger_ctx.LogInfo() << "Reading: Data is ready to read."_sv;

        // We expect the data is an unsigned integer
        read_value = result_data.Value();

        logger_ctx.LogInfo() << "Reading: The read value from: "_sv << key_to_read
                             << " is: " << result_data.Value();
        return_value = true;
    } else {
        logger_ctx.LogInfo() << "Reading: Data NOT ready"_sv;
    }
    return return_value;
}

template<typename dataType>
bool PersistentMemAccessor::ReadVariantCodingData(
    const variantCodingKeys key_to_read, dataType& read_value)
{
    bool return_value = false;
    ara::core::String key = kvs_enum_to_string_key(key_to_read);
    try {
        if (key.empty()) {
            throw std::invalid_argument("invalid key");
        }
        /* We first need to store some data before reading it. If application tries to read a data
         * which doesn't exist then GetValue API return an error.
         * Here we have implemented lazy switching approach. If the first read is not successful
         * then its assumed that data might not be initialized. So, initialize the kvs data base and
         * try reading the same key again. If it still fails then it's due to an issue in accessing
         * persistent memory.
         */
        return_value = PersistentMemAccessor::TryReadingDataFromKvs<uint8_t>(key, read_value);
        if (!return_value && !has_kvs_initialized_with_default_values) {
            // data not found in the database, try initializing the data
            logger_ctx.LogInfo()
                << "Initializing: data not found in the database, try initializing the database."_sv;
            if (!InitializeVcMemoryWithDefaultValues()) {
                logger_ctx.LogFatal() << "Initializing: unable to initialize persistent data."_sv;
            } else {
                logger_ctx.LogInfo() << "Initializing: kvs initialized with default values."_sv;
                return_value = PersistentMemAccessor::TryReadingDataFromKvs<uint8_t>(
                    key, read_value); // try reading once again
            }
            has_kvs_initialized_with_default_values = true; // set to true, don't try multiple times
        }
    } catch (const std::invalid_argument& e) {
        logger_ctx.LogError() << "Caught std::exception! Message = " << e.what();
    } catch (const std::exception& e) {
        logger_ctx.LogError() << "Caught std::exception! Message = " << e.what();
    } catch (...) {
        logger_ctx.LogError() << "Caught unknown exception!"_sv;
    }
    return return_value;
}

bool PersistentMemAccessor::ReadDataForConfigureSarTriggerEvents0136VcEvent(
    configureSarTriggerEvents0136VcEventDataType& configureSarTriggerEvents0136VcEventData)
{
    bool return_value = true;
    std::uint8_t read_value = 0;
    if (ReadVariantCodingData<uint8_t>(
            variantCodingKeys::triggerEventActivationStatusByte1, read_value)) {
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1 = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(
            variantCodingKeys::triggerEventActivationStatusByte2, read_value)) {
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2 = read_value;
    } else {
        return_value = false;
    }

    return return_value;
}

bool PersistentMemAccessor::ReadDataForActivateSarStorage0131VcEvent(
    activateSarStorage0131VcEventDataType& activateSarStorage0131VcEventData)
{
    bool return_value = true;
    std::uint8_t read_value = 0;
    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::sarDataStorageStatus, read_value)) {
        activateSarStorage0131VcEventData.sarDataStorageStatus = read_value;
    } else {
        return_value = false;
    }

    return return_value;
}

bool PersistentMemAccessor::ReadDataForVechicleInformation0400VcEvent(
    vechicleInformation0400VcEventDataType& vechicleInformation0400VcEventData)
{
    std::uint8_t read_value = 0;
    bool return_value = true;

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::bodyStyle, read_value)) {
        vechicleInformation0400VcEventData.body_style = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::vehLine, read_value)) {
        vechicleInformation0400VcEventData.veh_line = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::amgType, read_value)) {
        vechicleInformation0400VcEventData.amg_type = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::guardLvlB4, read_value)) {
        vechicleInformation0400VcEventData.guard_lvl_b4 = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::reserved400, read_value)) {
        vechicleInformation0400VcEventData.reserved = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::guardLvlB7, read_value)) {
        vechicleInformation0400VcEventData.guard_lvl_b7 = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::hybridAvl, read_value)) {
        vechicleInformation0400VcEventData.hybrid_avl = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::pluginHybridAvl, read_value)) {
        vechicleInformation0400VcEventData.plugin_hybrid_avl = read_value;
    } else {
        return_value = false;
    }

    if (ReadVariantCodingData<uint8_t>(variantCodingKeys::vehBackdoorsAvl, read_value)) {
        vechicleInformation0400VcEventData.veh_backdoors_avl = read_value;
    } else {
        return_value = false;
    }

    return return_value;
}

} // namespace VariantCodingApp

} // namespace application
