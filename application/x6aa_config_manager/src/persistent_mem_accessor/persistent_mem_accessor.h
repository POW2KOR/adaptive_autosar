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

#include "ara/log/logging.h"
#include "services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.h"

#include <string>

// #include "ara/per/file_storage.h"
// #include "ara/per/key_value_storage.h"
// #include "ara/per/read_write_accessor.h"
// #include "ara/per/shared_handle.h"

namespace application {

namespace VariantCodingApp {

using activateSarStorage0131VcEventDataType = ::DataTypes::
    NS_REC_activateSarStorage0131VcEventType_t::REC_activateSarStorage0131VcEventType_t;
using configureSarTriggerEvents0136VcEventDataType
    = ::DataTypes::NS_REC_configureSarTriggerEvents0136VcEventType_t::
        REC_configureSarTriggerEvents0136VcEventType_t;
using vechicleInformation0400VcEventDataType = ::DataTypes::
    NS_REC_vechicleInformation0400VcEventType_t::REC_vechicleInformation0400VcEventType_t;

class PersistentMemAccessor {
public:
    /*!
     * \brief Constructor.
     */
    PersistentMemAccessor();

    /**
     * \brief Funktion to construct and read ReadConfigureSarTriggerEvents0136VcEventData in key
     * value storage. \return configureSarTriggerEvents0136VcEventDataType Output data
     */
    configureSarTriggerEvents0136VcEventDataType ReadConfigureSarTriggerEvents0136VcEventData();

    /**
     * \brief Funktion to construct and read ReadActivateSarStorage0131VcEventData in key value
     * storage. \return activateSarStorage0131VcEventDataType Output data
     */
    activateSarStorage0131VcEventDataType ReadActivateSarStorage0131VcEventData();

    /**
     * \brief Funktion to construct and read ReadVechicleInformation0400VcEventData in key value
     * storage. \return vechicleInformation0400VcEventDataType Output data
     */
    vechicleInformation0400VcEventDataType ReadVechicleInformation0400VcEventData();

private:
    /**
     * \brief KeyValueStorage.
     */
    /**
     * TODO: uncomment
     */
    // ara::core::Optional<ara::per::SharedHandle<ara::per::KeyValueStorage>> key_value_storage;

    /**
     * \brief Holds the logging context
     */
    ara::log::Logger& logger_ctx{
        ara::log::CreateLogger("VPER", "Context for variant coding persistency")};

    /**
     * \brief Funktion to read data in key value storage.
     * \param key_to_read Input data which defines the key be written in to the kvs
     * \return uint32_t    Output data
     */
    uint32_t ReadVariantCodingData(const std::string& key_to_read);

    /**
     * \brief Funktion to write data in key value storage.
     * \param data_to_store Input data which should be written in to the file
     * \param key_to_store Input data which defines the key be written in to the kvs
     */
    void StoreVariantCodingData(uint32_t data_to_store, const std::string& key_to_store);

    /**
     * \brief Intialize key value storage with default values
     */
    void InitializeVcMemoryWithDefaultValues();
};

} // namespace VariantCodingApp

} // namespace application

#endif // PERSISTENT_MEM_ACCESSOR_H_
