load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "//arxmls:civic_export_with_roller_bliner_rear_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
)

filegroup(
    name = "logging_config_json",
    srcs = ["configs/logging_config.json"],
)

filegroup(
    name = "com_application_json",
    srcs = ["configs/com_application.json"],
)

filegroup(
    name = "exec_config_json",
    srcs = ["configs/exec_config.json"],
)

genr_ignore_patterns = [
    "SelfDiagnosticAgent_Executable.*",
    "DiagnosticManagerDeamon_Executable.*",
    "amsr_ssadiag.*",
    "amsr_ssasecd.*",

]

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "exec_config": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "applicationbase_init_deinit_srcs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/ara/core/initialization.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "swcluster_meta": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/swcl_package_metadata.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_daemon_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "swcl_db": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/etc/swcl_db.json",
            "InternalRouting_CIVIC_M_P_ST35_Executable/etc/updatemanager.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "modeldatatypes_api_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "modeldatatypes_hdrs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/DataTypes/REC_ECU_Stat_CIVIC_M_P_ST3/impl_type_rec_ecu_stat_civic_m_p_st3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/DataTypes/TypeRef/impl_type_c02_idle_opn_cls_sna.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/DataTypes/TypeRef/impl_type_c10_wakeuprsn_st3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/DataTypes/TypeRef/impl_type_c12_0_4094_1_sna.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/DataTypes/TypeRef/impl_type_dc_bool.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10/REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj/impl_type_rec_tssr_sw_stat_pr5_st3_7y1dtnin6c6u002o0wilpj2zj.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/PSI_5250_WiperWasher_UI_Ctrl_Wpr_Service_ST3_0/REC_WprWashSw_Stat_Pr5_ST3_en7lekos3iwo0omdqk2zxsfat/impl_type_rec_wprwashsw_stat_pr5_st3_en7lekos3iwo0omdqk2zxsfat.h",     
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipbinding_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipbinding",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "someipbinding_config": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/configuration/someip_config.json",
        ],
        "someipbinding_sd_config": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/configuration/static_sd_config.json",
        ],
        "someipbinding_hdrs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_ECU_Stat_CIVIC_M_P_ST3/serializer_REC_ECU_Stat_CIVIC_M_P_ST3_3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10/REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj/deserializer_REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj_1.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/PSI_5250_WiperWasher_UI_Ctrl_Wpr_Service_ST3_0/REC_WprWashSw_Stat_Pr5_ST3_en7lekos3iwo0omdqk2zxsfat/deserializer_REC_WprWashSw_Stat_Pr5_ST3_en7lekos3iwo0omdqk2zxsfat_2.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_someip_binding.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_someip_binding_init.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_someip_event_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_someip_methods.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_someip_skeleton_factory.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/TypeRef/serializer_c02_Idle_Opn_Cls_SNA_4.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_someip_binding.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_someip_binding_init.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_someip_event_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_someip_methods.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_someip_skeleton_factory.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_someip_binding.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_someip_binding_init.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_someip_event_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_someip_methods.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_someip_proxy_factory.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_someip_binding.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_someip_binding_init.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_someip_event_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_someip_methods.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_someip_proxy_factory.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/TypeRef/deserializer_c02_Idle_Opn_Cls_SNA_5.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_someip_binding.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_someip_binding_init.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_someip_event_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_someip_methods.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_someip_proxy_factory.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10/REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj/serializer_REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj_6.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_someip_binding.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_someip_binding_init.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_someip_event_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_someip_methods.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_someip_skeleton_factory.h",
        ],
        "someipbinding_srcs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_ECU_Stat_CIVIC_M_P_ST3/serializer_REC_ECU_Stat_CIVIC_M_P_ST3_3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10/REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj/deserializer_REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj_1.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/PSI_5250_WiperWasher_UI_Ctrl_Wpr_Service_ST3_0/REC_WprWashSw_Stat_Pr5_ST3_en7lekos3iwo0omdqk2zxsfat/deserializer_REC_WprWashSw_Stat_Pr5_ST3_en7lekos3iwo0omdqk2zxsfat_2.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_someip_binding.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_someip_binding_init.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_someip_event_manager.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/TypeRef/serializer_c02_Idle_Opn_Cls_SNA_4.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_someip_binding.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_someip_binding_init.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_someip_event_manager.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_someip_binding.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_someip_binding_init.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_someip_event_manager.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_someip_binding.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_someip_binding_init.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_someip_event_manager.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/someip_binding_initializer.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/TypeRef/deserializer_c02_Idle_Opn_Cls_SNA_5.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_someip_binding.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_someip_binding_init.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_someip_event_manager.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10/REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj/serializer_REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj_6.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_someip_binding.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_someip_binding_init.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_someip_event_manager.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipprotocol_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipprotocol",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "someipprotocol_hdrs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_rollerblindrear_ui_ctrl_hu_service_st3/events/serializer_RB_R_Rq_HU_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_tssr_ui_ctrl_rq_service_st3/events/deserializer_TSSR_UI_Ctrl_Rq_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_wiperwasher_ui_ctrl_wpr_service_st3/events/deserializer_WprWashSw_Stat_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_ecu_stat_civic_m_p_service_st3/events/serializer_ECU_Stat_CIVIC_M_P_Service_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10/REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj/deserializer_REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/PSI_5250_WiperWasher_UI_Ctrl_Wpr_Service_ST3_0/REC_WprWashSw_Stat_Pr5_ST3_en7lekos3iwo0omdqk2zxsfat/deserializer_REC_WprWashSw_Stat_Pr5_ST3_en7lekos3iwo0omdqk2zxsfat.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/REC_ECU_Stat_CIVIC_M_P_ST3/serializer_REC_ECU_Stat_CIVIC_M_P_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_rollerblindrear_ui_ctrl_hu_service_st3_210/events/deserializer_RB_R_Rq_HU_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_tssr_ui_ctrl_rq_service_st3_210/events/serializer_TSSR_UI_Ctrl_Rq_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/amsr/someip_protocol/internal/datatype_serialization/PSI_4234_TSSR_UI_Ctrl_Rq_Service_ST3_10/REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj/serializer_REC_TSSR_Sw_Stat_Pr5_ST3_7y1dtnin6c6u002o0wilpj2zj.h",

        ],
        "someipprotocol_srcs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_rollerblindrear_ui_ctrl_hu_service_st3/events/serializer_RB_R_Rq_HU_ST3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_tssr_ui_ctrl_rq_service_st3/events/deserializer_TSSR_UI_Ctrl_Rq_ST3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_wiperwasher_ui_ctrl_wpr_service_st3/events/deserializer_WprWashSw_Stat_ST3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_ecu_stat_civic_m_p_service_st3/events/serializer_ECU_Stat_CIVIC_M_P_Service_ST3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_rollerblindrear_ui_ctrl_hu_service_st3_210/events/deserializer_RB_R_Rq_HU_ST3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_tssr_ui_ctrl_rq_service_st3_210/events/serializer_TSSR_UI_Ctrl_Rq_ST3.cpp",
        ]
    },
)

minerva_aa_codegen_rule(
    name = "socal_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_socal",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "socal_scrs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/ara/com/runtime_gen.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_ecu_stat_civic_m_p_service_st3/ecu_stat_civic_m_p_service_st3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_ecu_stat_civic_m_p_service_st3/ecu_stat_civic_m_p_service_st3_skeleton.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/rollerblindrear_ui_ctrl_hu_service_st3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/rollerblindrear_ui_ctrl_hu_service_st3_skeleton.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_tssr_ui_ctrl_rq_service_st3/tssr_ui_ctrl_rq_service_st3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_tssr_ui_ctrl_rq_service_st3/tssr_ui_ctrl_rq_service_st3_proxy.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/wiperwasher_ui_ctrl_wpr_service_st3.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/wiperwasher_ui_ctrl_wpr_service_st3_proxy.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/rollerblindrear_ui_ctrl_hu_service_st3_210.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/rollerblindrear_ui_ctrl_hu_service_st3_210_proxy.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_tssr_ui_ctrl_rq_service_st3_210/tssr_ui_ctrl_rq_service_st3_210.cpp",
            "InternalRouting_CIVIC_M_P_ST35_Executable/src/services/ns_tssr_ui_ctrl_rq_service_st3_210/tssr_ui_ctrl_rq_service_st3_210_skeleton.cpp",
        ],
        "socal_hdrs": [
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_skeleton_impl_interface.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_ecu_stat_civic_m_p_service_st3/ECU_Stat_CIVIC_M_P_Service_ST3_types.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_ecu_stat_civic_m_p_service_st3/ecu_stat_civic_m_p_service_st3_common.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_ecu_stat_civic_m_p_service_st3/ecu_stat_civic_m_p_service_st3_skeleton.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_types.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/rollerblindrear_ui_ctrl_hu_service_st3_common.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/RollerBlindRear_UI_Ctrl_HU_Service_ST3_skeleton_impl_interface.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3/rollerblindrear_ui_ctrl_hu_service_st3_skeleton.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_internal.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_proxy_update_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3/TSSR_UI_Ctrl_Rq_Service_ST3_types.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3/tssr_ui_ctrl_rq_service_st3_common.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3/tssr_ui_ctrl_rq_service_st3_proxy.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_internal.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_proxy_update_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/WiperWasher_UI_Ctrl_Wpr_Service_ST3_types.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/wiperwasher_ui_ctrl_wpr_service_st3_common.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_wiperwasher_ui_ctrl_wpr_service_st3/wiperwasher_ui_ctrl_wpr_service_st3_proxy.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_internal.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_proxy_update_manager.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/RollerBlindRear_UI_Ctrl_HU_Service_ST3_210_types.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/rollerblindrear_ui_ctrl_hu_service_st3_210_common.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_rollerblindrear_ui_ctrl_hu_service_st3_210/rollerblindrear_ui_ctrl_hu_service_st3_210_proxy.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_skeleton_impl_interface.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3_210/TSSR_UI_Ctrl_Rq_Service_ST3_210_types.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3_210/tssr_ui_ctrl_rq_service_st3_210_common.h",
            "InternalRouting_CIVIC_M_P_ST35_Executable/include/services/ns_tssr_ui_ctrl_rq_service_st3_210/tssr_ui_ctrl_rq_service_st3_210_skeleton.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "ipcbinding_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_ipcbinding",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        # No Files generated for ipc_binding
    },
)

cc_library(
    name = "modeldatatypes_hdrs_lib",
    hdrs = [
        ":modeldatatypes_hdrs",
    ],
    strip_include_prefix = "modeldatatypes_hdrs/output/InternalRouting_CIVIC_M_P_ST35_Executable/include/",
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/InternalRouting_CIVIC_M_P_ST35_Executable/include/",
)

cc_library(
    name = "someipbinding_hdrs_lib",
    hdrs = [
        ":someipbinding_hdrs",
    ],
    strip_include_prefix = "someipbinding_hdrs/output/InternalRouting_CIVIC_M_P_ST35_Executable/include/",
)

cc_library(
    name = "someipprotocol_hdrs_lib",
    hdrs = [
        ":someipprotocol_hdrs",
    ],
    strip_include_prefix = "someipprotocol_hdrs/output/InternalRouting_CIVIC_M_P_ST35_Executable/include/",
)

cc_binary(
    name = "app",
    srcs = [
        "main.cpp",
        "application.h",
        "application.cpp",
        "roller_blinder_rear_provider.h",
        "roller_blinder_rear_provider.cpp",
        "roller_blinder_rear_consumer.h",
        "roller_blinder_rear_consumer.cpp",
        "sunroof_roller_ctrl.h",
        "sunroof_roller_ctrl.cpp",
        ":applicationbase_init_deinit_srcs",
        ":socal_scrs",
        ":someipbinding_srcs",
        ":someipprotocol_srcs",
        "//bsw:amsr_vector_fs_socal_libsocal_a",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    includes = ["src/"],
    linkstatic = 1,
    deps = [
        ":modeldatatypes_hdrs_lib",
        ":socal_hdrs_lib",
        ":someipbinding_hdrs_lib",
        ":someipprotocol_hdrs_lib",
        "//application/common:application_base",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_vajson",
        "//bsw:amsr_vector_fs_socal",
        "//bsw:amsr_vector_fs_someipbinding",
    ],
)

pkg_tar(
    name = "package",
    files = {
        # currently we are using the static exec_config
        # and not the enerated ones as the Startup states
        # are missing
        ":exec_config_json": "etc/exec_config.json",
        ":logging_config_json": "etc/logging_config.json",
        ":com_application_json": "etc/com_application.json",
        ":someipbinding_config": "etc/someip_config.json",
        "someipbinding_sd_config": "etc/static_sd_config.json",
        ":app": "bin/InternalRouting_CIVIC_M_P_ST35_Executable"
    },
    mode = "0755",
    package_dir = "opt/InternalRouting_CIVIC_M_P_ST35_Executable",
)
