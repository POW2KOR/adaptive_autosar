/*****************************************************************************
 * \file   x6aa_cnfg_mngr_kvs_keys.h
 *
 * \brief  VVcCnfgMngrServer application
 * \author MBition - Copyright (c) 2019-2020 Daimler AG
 * \date
 * \note   TODO: additional notes
 ******************************************************************************/

#ifndef X6AA_CNFG_MNGR_KVS_KEYS_DOMAIN_H
#define X6AA_CNFG_MNGR_KVS_KEYS_DOMAIN_H

namespace application {

namespace VariantCodingApp {

/*!
 * \brief Enumeration for all key value storage database keys
 */
enum class X6aaConfigManagerKvsKeys : uint8_t {
    triggerEventActivationStatusByte1 = 0,
    triggerEventActivationStatusByte2,
    sarDataStorageStatus,
    bodyStyle,
    vehLine,
    amgType,
    guardLvlB4,
    reserved400,
    guardLvlB7,
    hybridAvl,
    pluginHybridAvl,
    vehBackdoorsAvl,
};

/* TODO: find a better way of doing it, any c++ builtin functionality for stringing enums?? */
inline ara::core::String kvs_enum_to_string_key(X6aaConfigManagerKvsKeys key)
{
    switch (key) {
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::triggerEventActivationStatusByte1:
        return "triggerEventActivationStatusByte1";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::triggerEventActivationStatusByte2:
        return "triggerEventActivationStatusByte2";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::sarDataStorageStatus:
        return "sarDataStorageStatus";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::bodyStyle:
        return "bodyStyle";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::vehLine:
        return "vehLine";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::amgType:
        return "amgType";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::guardLvlB4:
        return "guardLvlB4";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::guardLvlB7:
        return "guardLvlB7";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::reserved400:
        return "reserved400";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::hybridAvl:
        return "hybridAvl";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::pluginHybridAvl:
        return "pluginHybridAvl";
    case application::VariantCodingApp::X6aaConfigManagerKvsKeys::vehBackdoorsAvl:
        return "vehBackdoorsAvl";
    default:
        return ""; // returning empty string
    }
}

} // namespace VariantCodingApp

} // namespace application

#endif /* end of include guard: X6AA_CNFG_MNGR_KVS_KEYS_DOMAIN_H */
