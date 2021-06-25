/*****************************************************************************
 * \file   persistent_mem_accessor.h
 *
 * \brief  persistent_mem_accessor class representing the variant coding application.
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#ifndef PERSISTENT_MEM_ACCESSOR_H_
#define PERSISTENT_MEM_ACCESSOR_H_

#include "ara/core/result.h"
#include "ara/log/logging.h"
#include "ara/per/file_storage.h"
#include "ara/per/key_value_storage.h"
#include "ara/per/read_write_accessor.h"
#include "ara/per/shared_handle.h"
#include "services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.h"
#include "x6aa_cnfg_mngr_kvs_keys.h"

#include <string>

namespace application {

namespace VariantCodingApp {

using activateSarStorage0131VcEventDataType = ::DataTypes::
    NS_REC_activateSarStorage0131VcEventType_t::REC_activateSarStorage0131VcEventType_t;
using configureSarTriggerEvents0136VcEventDataType
    = ::DataTypes::NS_REC_configureSarTriggerEvents0136VcEventType_t::
        REC_configureSarTriggerEvents0136VcEventType_t;
using vechicleInformation0400VcEventDataType = ::DataTypes::
    NS_REC_vechicleInformation0400VcEventType_t::REC_vechicleInformation0400VcEventType_t;

using variantCodingKeys = application::VariantCodingApp::X6aaConfigManagerKvsKeys;

class SingletonPersistentMemAccessor {
public:
    /**
     * \brief Funtion for getting SingletonPersistentMemAccessor instance.
     */
    static SingletonPersistentMemAccessor* getInstance();
    /**
     * \brief SingletonPersistentMemAccessor should not be cloneable.
     */
    SingletonPersistentMemAccessor(SingletonPersistentMemAccessor& other) = delete;

    /**
     * \brief SingletonPersistentMemAccessor should not be assignable.
     */
    void operator=(const SingletonPersistentMemAccessor&) = delete;

    /**
     * \brief Function to read all information required for sending out ara::com event
     * `configureSarTriggerEvents0136VcEvent`.
     * \param configureSarTriggerEvents0136VcEventDataType data
     * \return bool   success
     */
    ara::core::Result<configureSarTriggerEvents0136VcEventDataType>
    ReadDataForConfigureSarTriggerEvents0136VcEvent();

    /**
     * \brief Function to read all information required for sending out ara::com event
     * `activateSarStorage0131VcEvent`.
     * \param activateSarStorage0131VcEventDataType  data
     * \return bool   success
     */
    ara::core::Result<activateSarStorage0131VcEventDataType>
    ReadDataForActivateSarStorage0131VcEvent();

    /**
     * \brief Function to read all information required for sending out ara::com event
     * `vechicleInformation0400VcEvent`.
     * \param vechicleInformation0400VcEventDataType data
     * \return bool   success
     */
    ara::core::Result<vechicleInformation0400VcEventDataType>
    ReadDataForVechicleInformation0400VcEvent();

    /**
     * \brief Function to retrive data of each individual element of struct
     * `configureSarTriggerEvents0136VcEventDataType` passed as an argument and to store
     * each individual struct element as a key-value pair to kvs data base.
     * \param configureSarTriggerEvents0136VcEventDataType Input data
     * \return bool   success
     */
    ara::core::Result<void> StoreDataForConfigureSarTriggerEvents0136VcEvent(
        configureSarTriggerEvents0136VcEventDataType& configureSarTriggerEvents0136VcEventData);

    /**
     * \brief Function to retrive data of each individual element of struct
     * `activateSarStorage0131VcEventDataType` passed as an argument and to store
     * each individual struct element as a key-value pair to kvs data base.
     * \param activateSarStorage0131VcEventDataType Input data
     * \return bool   success
     */
    ara::core::Result<void> StoreDataForActivateSarStorage0131VcEvent(
        activateSarStorage0131VcEventDataType& activateSarStorage0131VcEventData);

    /**
     * \brief Function to retrive data of each individual element of struct
     * `vechicleInformation0400VcEventDataType` passed as an argument and to store
     * each individual struct element as a key-value pair to kvs data base.
     * \param vechicleInformation0400VcEventDataType Input data
     * \return bool   success
     */
    ara::core::Result<void> StoreDataForVechicleInformation0400VcEvent(
        vechicleInformation0400VcEventDataType& vechicleInformation0400VcEventData);
    /**
     * \brief For checking if the initialization was successfull
     */
    bool has_kvs_initialized_with_default_values = false;

private:
    /**
     * \brief Make the SingletonPersistentMemAccessor constructor private to prevent direct
     * construction calls with the `new` operator.
     */
    SingletonPersistentMemAccessor();

    /**
     * \brief The one, single instance.
     */
    static SingletonPersistentMemAccessor* persistentMemAccessorInstance;

    /**
     * \brief KeyValueStorage.
     */
    std::unique_ptr<ara::per::SharedHandle<ara::per::KeyValueStorage>> key_value_storage;

    /**
     * \brief Holds the logging context
     */
    ara::log::Logger& logger_ctx{ara::log::CreateLogger("VPER", "VcPersistentMemAccessor")};

    /**
     * \brief Function to read data in key value storage
     * \param key_to_read enum key to be read from kvs
     * \param dataType    read data
     * \return bool       success
     */
    template<typename dataType>
    ara::core::Result<dataType> ReadVariantCodingData(const variantCodingKeys key_to_read);

    /**
     * \brief A sub Function to read data in key value storage.
     * \param key_to_read string key to be read from kvs
     * \param dataType    read data
     * \return bool       success
     */
    template<typename dataType>
    ara::core::Result<dataType> TryReadingDataFromKvs(const ara::core::String& key_to_read);

    /**
     * \brief Function to write data in key value storage.
     * \param data_to_store Input data which should be written in to the file
     * \param key_to_store Input data which defines the key be written in to the kvs
     * \return bool       success
     */
    template<typename dataType>
    ara::core::Result<void> StoreVariantCodingData(
        const variantCodingKeys key_to_store, dataType data_to_store);

    /**
     * \brief Initialize key value storage with default values
     */
    ara::core::Result<void> InitializeVcMemoryWithDefaultValues();
};

} // namespace VariantCodingApp

} // namespace application

#endif // PERSISTENT_MEM_ACCESSOR_H_
