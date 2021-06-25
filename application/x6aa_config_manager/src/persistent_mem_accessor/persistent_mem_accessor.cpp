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

// Define the static SingletonPersistentMemAccessor pointer
SingletonPersistentMemAccessor* SingletonPersistentMemAccessor::persistentMemAccessorInstance = nullptr;

SingletonPersistentMemAccessor* SingletonPersistentMemAccessor::getInstance() {
   if (persistentMemAccessorInstance == nullptr) {
      persistentMemAccessorInstance = new SingletonPersistentMemAccessor();
   }
   return(persistentMemAccessorInstance);
}

SingletonPersistentMemAccessor::SingletonPersistentMemAccessor()
{
    ara::core::Result<ara::core::InstanceSpecifier> kvs_instance_specifier
        = ara::core::InstanceSpecifier::MakeInstanceSpecifier(
            "X6AA_Cnfg_Mngr_Executable/X6AA_Cnfg_Mngr_ExecutableRootSwc/MyPersistencyKvsPrPortPrototype"_sv);

    if (kvs_instance_specifier.HasValue()) {
        ara::per::Result<ara::per::SharedHandle<ara::per::KeyValueStorage>> opened_kvs
            = ara::per::OpenKeyValueStorage(kvs_instance_specifier.Value());

        if (opened_kvs.HasValue()) {
            key_value_storage = std::make_unique<ara::per::SharedHandle<ara::per::KeyValueStorage>>(
                opened_kvs.Value());
            logger_ctx.LogInfo() << "config manager is able to open key value storage."_sv;
        } else {
            throw "Failed to create instance specifier for persistency port.";
        }
    } else {
        throw "Failed to open key value storage DB.";
    }
    has_kvs_initialized_with_default_values = false;
    logger_ctx.SetPrefix("VcPersistentMemAccessor : "_sv);
}

template<typename dataType>
ara::core::Result<void> SingletonPersistentMemAccessor::StoreVariantCodingData(
    const variantCodingKeys key_to_store, dataType data_to_store)
{
    ara::core::Result<void> write_result{
        X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed};
    ara::core::String key = kvs_enum_to_string_key(key_to_store);
    try {
        if (key.empty()) {
            throw std::invalid_argument("invalid key for storing data");
        }
        // Insert values into the database.
        write_result
            = (*key_value_storage)->SetValue<dataType>(ara::core::StringView(key), data_to_store);

        logger_ctx.LogDebug() << "Writing to store key: " << key << " with value: " << data_to_store;

        if (write_result.HasValue()) {
            logger_ctx.LogInfo() << "The value written for : "
                                 << kvs_enum_to_string_key(key_to_store)
                                 << " is: " << data_to_store;
            // Persist the database.
            (*key_value_storage)->SyncToStorage();
        } else {
            logger_ctx.LogInfo() << "Data NOT ready"_sv;
            logger_ctx.LogError() << write_result.Error().Message();
            write_result.FromError(
                X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed, "Writing Failed");
        }
    } catch (const std::invalid_argument& e) {
        logger_ctx.LogError() << "Caught std::invalid_argument! Message = " << e.what();
    } catch (const std::exception& e) {
        logger_ctx.LogError() << "Caught std::exception! Message = " << e.what();
    } catch (...) {
        logger_ctx.LogError() << "Caught unknown exception!"_sv;
    }
    return write_result;
}

ara::core::Result<void> SingletonPersistentMemAccessor::StoreDataForConfigureSarTriggerEvents0136VcEvent(
    configureSarTriggerEvents0136VcEventDataType& configureSarTriggerEvents0136VcEventData)
{
    ara::core::Result<void> result{X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed};

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

ara::core::Result<void> SingletonPersistentMemAccessor::StoreDataForActivateSarStorage0131VcEvent(
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

ara::core::Result<void> SingletonPersistentMemAccessor::StoreDataForVechicleInformation0400VcEvent(
    vechicleInformation0400VcEventDataType& vechicleInformation0400VcEventData)
{
    ara::core::Result<void> result{X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed};

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

ara::core::Result<void> SingletonPersistentMemAccessor::InitializeVcMemoryWithDefaultValues()
{
    ara::core::Result<void> result{X6aa_Config_Manager_Errc::kWritingToPersistentMemoryFailed};
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
ara::core::Result<dataType> SingletonPersistentMemAccessor::TryReadingDataFromKvs(
    const ara::core::String& key_to_read)
{
    ara::per::Result<dataType> result_data
        = (*key_value_storage)->GetValue<dataType>(ara::core::StringView(key_to_read));

    if (result_data.HasValue()) {
        logger_ctx.LogDebug() << "Reading: Data is ready to be read."_sv;
        logger_ctx.LogInfo() << "Reading: The read value from: "_sv << key_to_read
                             << " is: " << result_data.Value();
    } else {
        logger_ctx.LogError() << result_data.Error().Message();
    }
    return result_data;
}

template<typename dataType>
ara::core::Result<dataType> SingletonPersistentMemAccessor::ReadVariantCodingData(
    const variantCodingKeys key_to_read)
{
    ara::core::Result<dataType> result{
        X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed};
    ara::core::String key = kvs_enum_to_string_key(key_to_read);
    try {
        if (key.empty()) {
            throw std::invalid_argument("invalid key while reading data");
        }
        /* We first need to store some data before reading it. If application tries to read a data
         * which doesn't exist then GetValue API return an error.
         * Here we have implemented lazy switching approach. If the first read is not successful
         * then its assumed that data might not be initialized. So, initialize the kvs data base and
         * try reading the same key again. If it still fails then it's due to an issue in accessing
         * persistent memory.
         */
        result = SingletonPersistentMemAccessor::TryReadingDataFromKvs<uint8_t>(key);
        if (!result.HasValue() && !has_kvs_initialized_with_default_values) {
            // data not found in the database, try initializing the data
            logger_ctx.LogInfo()
                << "Initializing: data not found in the database, try initializing the database."_sv;
            if (!InitializeVcMemoryWithDefaultValues()) {
                throw "Unable to initialize persistent data.";
            } else {
                logger_ctx.LogInfo() << "Initializing: kvs initialized with default values."_sv;
                result = SingletonPersistentMemAccessor::TryReadingDataFromKvs<uint8_t>(key); // try reading once again
            }
            has_kvs_initialized_with_default_values = true; // set to true, don't try multiple times
        }
    } catch (const std::invalid_argument& e) {
        logger_ctx.LogError() << "Caught std::invalid_argument! Message = " << e.what();
    } catch (const std::exception& e) {
        logger_ctx.LogError() << "Caught std::exception! Message = " << e.what();
    } catch (...) {
        logger_ctx.LogError() << "Caught unknown exception!"_sv;
    }
    return result;
}

ara::core::Result<configureSarTriggerEvents0136VcEventDataType> SingletonPersistentMemAccessor::
    ReadDataForConfigureSarTriggerEvents0136VcEvent()
{
    ara::core::Result<configureSarTriggerEvents0136VcEventDataType> result{
        X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed};
    ara::core::Result<uint8_t> read_value{
        X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed};
    configureSarTriggerEvents0136VcEventDataType configureSarTriggerEvents0136VcEventData;
    read_value
        = ReadVariantCodingData<uint8_t>(variantCodingKeys::triggerEventActivationStatusByte1);
    if (read_value.HasValue()) {
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte1
            = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "triggerEventActivationStatusByte1 Reading Failed");
    }

    read_value
        = ReadVariantCodingData<uint8_t>(variantCodingKeys::triggerEventActivationStatusByte2);
    if (read_value.HasValue()) {
        configureSarTriggerEvents0136VcEventData.triggerEventActivationStatusByte2
            = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "triggerEventActivationStatusByte2 Reading Failed");
    }

    result = configureSarTriggerEvents0136VcEventData;

    return result;
}

ara::core::Result<activateSarStorage0131VcEventDataType> SingletonPersistentMemAccessor::
    ReadDataForActivateSarStorage0131VcEvent()
{
    ara::core::Result<activateSarStorage0131VcEventDataType> result{
        X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed};
    activateSarStorage0131VcEventDataType activateSarStorage0131VcEventData;
    ara::core::Result<uint8_t> read_value
        = ReadVariantCodingData<uint8_t>(variantCodingKeys::sarDataStorageStatus);
    if (read_value.HasValue()) {
        activateSarStorage0131VcEventData.sarDataStorageStatus = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "sarDataStorageStatus Reading Failed");
    }
    result = activateSarStorage0131VcEventData;

    return result;
}

ara::core::Result<vechicleInformation0400VcEventDataType> SingletonPersistentMemAccessor::
    ReadDataForVechicleInformation0400VcEvent()
{
    ara::core::Result<vechicleInformation0400VcEventDataType> result{
        X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed};
    ara::core::Result<uint8_t> read_value{
        X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed};
    vechicleInformation0400VcEventDataType vechicleInformation0400VcEventData;

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::bodyStyle);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.body_style = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "body_style Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::vehLine);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.veh_line = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "veh_line Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::amgType);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.amg_type = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "amg_type Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::guardLvlB4);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.guard_lvl_b4 = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "guard_lvl_b4 Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::reserved400);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.reserved = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "reserved Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::guardLvlB7);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.guard_lvl_b7 = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "guardLvlB7 Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::hybridAvl);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.hybrid_avl = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "hybridAvl Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::pluginHybridAvl);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.plugin_hybrid_avl = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "pluginHybridAvl Reading Failed");
    }

    read_value = ReadVariantCodingData<uint8_t>(variantCodingKeys::vehBackdoorsAvl);
    if (read_value.HasValue()) {
        vechicleInformation0400VcEventData.veh_backdoors_avl = read_value.Value();
    } else {
        return result.FromError(
            X6aa_Config_Manager_Errc::kReadingFromPersistentMemoryFailed,
            "vehBackdoorsAvl Reading Failed");
    }

    result = vechicleInformation0400VcEventData;

    return result;
}

} // namespace VariantCodingApp

} // namespace application
