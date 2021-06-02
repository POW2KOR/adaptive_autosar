load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_exec_config": [
            "X6AA_Cnfg_Mngr_Executable/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_init_deinit_srcs": [
            "X6AA_Cnfg_Mngr_Executable/src/ara/core/initialization.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_swcluster_meta": [
            "X6AA_Cnfg_Mngr_Executable/swcl_package_metadata.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_daemon_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_swcl_db": [
            "X6AA_Cnfg_Mngr_Executable/etc/swcl_db.json",
        ],
        "x6aa_config_manager_updatemanager_daemon": [
            "X6AA_Cnfg_Mngr_Executable/etc/updatemanager.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "persistency_config_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_persistency_config",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        # Currently there are no ara::per interfaces
    },
)

minerva_aa_codegen_rule(
    name = "modeldatatypes_api_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_modeldatatypes_hdrs": [
            "X6AA_Cnfg_Mngr_Executable/include/DataTypes/NS_REC_activateSarStorage0131VcEventType_t/impl_type_rec_activatesarstorage0131vceventtype_t.h",
            "X6AA_Cnfg_Mngr_Executable/include/DataTypes/NS_REC_configureSarTriggerEvents0136VcEventType_t/impl_type_rec_configuresartriggerevents0136vceventtype_t.h",
            "X6AA_Cnfg_Mngr_Executable/include/DataTypes/NS_REC_vechicleInformation0400VcEventType_t/impl_type_rec_vechicleinformation0400vceventtype_t.h",
            "X6AA_Cnfg_Mngr_Executable/include/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/impl_type_rec_evc_cfgbit_01_26_pr5_st3_2nibgl9yx8nj74mt7kvhiab7f.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipbinding_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipbinding",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_someip_config": [
            "X6AA_Cnfg_Mngr_Executable/configuration/someip_config.json",
        ],
        "x6aa_config_manager_static_sd_config": [
            "X6AA_Cnfg_Mngr_Executable/configuration/static_sd_config.json",
        ],
        "x6aa_config_manager_someip_binding_hdrs": [
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/deserializer_REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f_1.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding_init.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_event_manager.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_methods.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_someip_proxy_factory.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding_init.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_event_manager.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_methods.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_someip_proxy_factory.h",
        ],
        "x6aa_config_manager_someip_binding_srcs": [
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/deserializer_REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f_1.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding_init.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_event_manager.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding_init.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_event_manager.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/someip_binding_initializer.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipprotocol_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipprotocol",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_someip_protocol_hdrs": [
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_extvehicleconfig_service_st3/events/deserializer_Ev_EVC_CfgBit_01_26_Pr5_ST3.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_dummyswc_2_to_cnfg_mngr/events/deserializer_Ev_CalculationResult.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_activateSarStorage0131VcEvent.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_configureSarTriggerEvents0136VcEvent.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_vechicleInformation0400VcEvent.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/deserializer_REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/NS_REC_activateSarStorage0131VcEventType_t/serializer_REC_activateSarStorage0131VcEventType_t.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/NS_REC_configureSarTriggerEvents0136VcEventType_t/serializer_REC_configureSarTriggerEvents0136VcEventType_t.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/NS_REC_vechicleInformation0400VcEventType_t/serializer_REC_vechicleInformation0400VcEventType_t.h",
        ],
        "x6aa_config_manager_someip_protocol_srcs": [
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_extvehicleconfig_service_st3/events/deserializer_Ev_EVC_CfgBit_01_26_Pr5_ST3.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_dummyswc_2_to_cnfg_mngr/events/deserializer_Ev_CalculationResult.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_activateSarStorage0131VcEvent.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_configureSarTriggerEvents0136VcEvent.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_vechicleInformation0400VcEvent.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "socal_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_socal",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_runtime_gen_cpp": [
            "X6AA_Cnfg_Mngr_Executable/src/ara/com/runtime_gen.cpp",
        ],
        "x6aa_config_manager_socal_extvehicleconfig_proxy_hdrs": [
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_internal.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_update_manager.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_types.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3_common.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3_proxy.h",
        ],
        "x6aa_config_manager_socal_extvehicleconfig_proxy_srcs": [
            "X6AA_Cnfg_Mngr_Executable/src/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3_proxy.cpp",
        ],
        "x6aa_config_manager_socal_proxy_hdrs": [
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_internal.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_update_manager.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_types.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_common.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_proxy.h",
        ],
        "x6aa_config_manager_socal_proxy_srcs": [
            "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_proxy.cpp",
        ],
        "x6aa_config_manager_socal_skeleton_hdrs": [
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_impl_interface.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_types.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_common.h",
            "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.h",
        ],
        "x6aa_config_manager_socal_skeleton_srcs": [
            "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "ipcbinding_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_ver2_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_ipcbinding",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "x6aa_config_manager_ipcbinding_hdrs": [
            "X6AA_Cnfg_Mngr_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_binding.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_event_manager.h",
            "X6AA_Cnfg_Mngr_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_method_manager.h",
        ],
        "x6aa_config_manager_ipcbinding_srcs": [
            "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/ipc_binding_life_cycle_manager.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_binding.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_event_manager.cpp",
            "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_method_manager.cpp",
        ],
    },
)

filegroup(
    name = "srcs",
    srcs = glob(["src/**"]),
)

cc_binary(
    name = "app",
    srcs = [
        #":srcs",
        ":x6aa_config_manager_updatemanager_daemon",
        ":x6aa_config_manager_swcluster_meta",
        ":x6aa_config_manager_swcl_db",
        ":x6aa_config_manager_static_sd_config",
        ":x6aa_config_manager_someip_protocol_srcs",
        ":x6aa_config_manager_someip_protocol_hdrs",
        ":x6aa_config_manager_someip_config",
        ":x6aa_config_manager_someip_binding_srcs",
        ":x6aa_config_manager_someip_binding_hdrs",
        ":x6aa_config_manager_socal_skeleton_srcs",
        ":x6aa_config_manager_socal_skeleton_hdrs",
        ":x6aa_config_manager_socal_proxy_srcs",
        ":x6aa_config_manager_socal_proxy_hdrs",
        ":x6aa_config_manager_socal_extvehicleconfig_proxy_srcs",
        ":x6aa_config_manager_socal_extvehicleconfig_proxy_hdrs",
        ":x6aa_config_manager_runtime_gen_cpp",
        ":x6aa_config_manager_modeldatatypes_hdrs",
        ":x6aa_config_manager_ipcbinding_srcs",
        ":x6aa_config_manager_ipcbinding_hdrs",
        ":x6aa_config_manager_init_deinit_srcs",
        ":x6aa_config_manager_exec_config",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
        "socket",
    ],
    linkstatic = 1,
    deps = [
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libiostream",
        "//bsw:amsr_vector_fs_log_api",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/x6aa_config_manager",
        #":logging_config": "etc/logging_config.json",
        ":x6aa_config_manager_exec_config": "etc/exec_config.json",
        ":x6aa_config_manager_swcl_db": "etc/swcl_db.json",
        ":updatemanager_swcluster_meta_gen_rule": "etc/swcl_package_metadata.json",
        ":x6aa_config_manager_static_sd_config": "configuration/static_sd_config.json",
        ":x6aa_config_manager_someip_config": "configuration/someip_config.json",
        ":x6aa_config_manager_updatemanager_daemon": "etc/updatemanager.json",
    },
    mode = "0755",
    package_dir = "opt/x6aa_config_manager",
)
