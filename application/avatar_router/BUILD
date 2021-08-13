load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "//arxmls:Gen20x_Civic_i3_ECU_Extract",
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

minerva_aa_codegen_rule(
    name = "avatar_router_gen_rule",
    arxml_srcs = [":app_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],

    outs_list_dict = {
    #    "exec_config": [
    #        "X6AA_Cnfg_Mngr_Executable/configuration/exec_config.json",
    #    ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #    "applicationbase_init_deinit_srcs": [
    #        "X6AA_Cnfg_Mngr_Executable/src/ara/core/initialization.cpp",
    #    ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #    "swcluster_meta": [
    #        "X6AA_Cnfg_Mngr_Executable/swcl_package_metadata.json",
    #    ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #    "swcl_db": [
    #        "X6AA_Cnfg_Mngr_Executable/etc/swcl_db.json",
    #    ],
    #    "updatemanager_daemon": [
    #        "X6AA_Cnfg_Mngr_Executable/etc/updatemanager.json",
    #    ],
    },
)

minerva_aa_codegen_rule(
    name = "persistency_config_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_persistency_config",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "X6AA_Cnfg_Mngr_Executable.*amsr-vector-fs-per-libpersistency.*",
    ],
    outs_list_dict = {
    #    "persistency_config_json": [
    #        "X6AA_Cnfg_Mngr_Executable/etc/per_key_value_storage_config.json",
    #    ],
    #    "persistency_hdrs": [
    #        "X6AA_Cnfg_Mngr_Executable/include/ara/per/detail/dynamic_key_value_storage_decl.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/ara/per/internal/config_validation_keys.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/ara/per/key_value_storage_data_visitor.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/ara/per/key_value_storage_variant.h",
    #    ],
    #    "persistency_srcs": [
    #        "X6AA_Cnfg_Mngr_Executable/src/ara/per/dynamic_object_parser.cpp",
    #    ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #     "modeldatatypes_hdrs": [
    #         "X6AA_Cnfg_Mngr_Executable/include/DataTypes/NS_REC_activateSarStorage0131VcEventType_t/impl_type_rec_activatesarstorage0131vceventtype_t.h",
    #         "X6AA_Cnfg_Mngr_Executable/include/DataTypes/NS_REC_configureSarTriggerEvents0136VcEventType_t/impl_type_rec_configuresartriggerevents0136vceventtype_t.h",
    #         "X6AA_Cnfg_Mngr_Executable/include/DataTypes/NS_REC_vechicleInformation0400VcEventType_t/impl_type_rec_vechicleinformation0400vceventtype_t.h",
    #         "X6AA_Cnfg_Mngr_Executable/include/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/impl_type_rec_evc_cfgbit_01_26_pr5_st3_2nibgl9yx8nj74mt7kvhiab7f.h",
    #     ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #    "someip_binding_initializer": [
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/someip_binding_initializer.cpp",
    #    ],
    #    "someip_config": [
    #        "X6AA_Cnfg_Mngr_Executable/configuration/someip_config.json",
    #    ],
    #    "static_sd_config": [
    #        "X6AA_Cnfg_Mngr_Executable/configuration/static_sd_config.json",
    #    ],
    #    "someipbinding_hdrs": [
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/deserializer_REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f_1.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding_init.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_event_manager.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_methods.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_someip_proxy_factory.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding_init.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_event_manager.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_methods.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_someip_proxy_factory.h",
    #    ],
    #    "someipbinding_srcs": [
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/deserializer_REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f_1.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_binding_init.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_someip_event_manager.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_binding_init.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_someip_event_manager.cpp",
    #    ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #    "someipprotocol_hdrs": [
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_extvehicleconfig_service_st3/events/deserializer_Ev_EVC_CfgBit_01_26_Pr5_ST3.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_dummyswc_2_to_cnfg_mngr/events/deserializer_Ev_CalculationResult.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_activateSarStorage0131VcEvent.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_configureSarTriggerEvents0136VcEvent.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_vechicleInformation0400VcEvent.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f/deserializer_REC_EVC_CfgBit_01_26_Pr5_ST3_2nibgl9yx8nj74mt7kvhiab7f.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/NS_REC_activateSarStorage0131VcEventType_t/serializer_REC_activateSarStorage0131VcEventType_t.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/NS_REC_configureSarTriggerEvents0136VcEventType_t/serializer_REC_configureSarTriggerEvents0136VcEventType_t.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/NS_REC_vechicleInformation0400VcEventType_t/serializer_REC_vechicleInformation0400VcEventType_t.h",
    #    ],
    #    "someipprotocol_srcs": [
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_extvehicleconfig_service_st3/events/deserializer_Ev_EVC_CfgBit_01_26_Pr5_ST3.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_dummyswc_2_to_cnfg_mngr/events/deserializer_Ev_CalculationResult.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_activateSarStorage0131VcEvent.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_configureSarTriggerEvents0136VcEvent.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_cnfg_mngr_to_dummyswc/events/serializer_Ev_vechicleInformation0400VcEvent.cpp",
    #    ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #    "runtime_gen": [
    #        "X6AA_Cnfg_Mngr_Executable/src/ara/com/runtime_gen.cpp",
    #    ],
    #    "socal_hdrs": [
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_internal.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_proxy_update_manager.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_types.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_common.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_proxy.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_internal.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_proxy_update_manager.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/SI_ExtVehicleConfig_Service_ST3_types.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3_common.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3_proxy.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_impl_interface.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_types.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_common.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.h",
    #    ],
    #    "socal_srcs": [
    #        "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_proxy.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/services/ns_extvehicleconfig_service_st3/si_extvehicleconfig_service_st3_proxy.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_skeleton.cpp",
    #    ],
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",

        "DiagnosticManagerDeamon_Executable.*",
        "InternalRouting_CIVIC_M_P_ST35_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "amsr_ssadiag.*",
        "amsr_ssasecd.*",
    ],
    outs_list_dict = {
    #    "ipc_binding_life_cycle_manager": [
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/ipc_binding_life_cycle_manager.cpp",
    #    ],
    #    "ipcbinding_hdrs": [
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_binding.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_event_manager.h",
    #        "X6AA_Cnfg_Mngr_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_method_manager.h",
    #    ],
    #    "ipcbinding_srcs": [
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_binding.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_event_manager.cpp",
    #        "X6AA_Cnfg_Mngr_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_skeleton_ipc_method_manager.cpp",
    #    ],
    },
)

cc_binary(
    name = "avatar_router_app",
    srcs = [
         "src/app/main.cpp",
         "src/app/avatar_router_error_domain.h",

         # ----------------------------------------------------------------------------------------------------------------------------------
         # The following is needed for the these errors until the proper file support to initialization.cpp file is generated by the genrules/generators in their output
	 # bazel-out/k8-fastbuild/bin/bsw/amsr_vector_fs_socal/lib/libSocal.a(runtime.cpp.o):runtime.cpp:function ara::com::Runtime::InitializeInternal(): error: undefined reference to 'ara::com::Runtime::InitializeBindings()'
         # bazel-out/k8-fastbuild/bin/bsw/amsr_vector_fs_socal/lib/libSocal.a(runtime.cpp.o):runtime.cpp:function ara::com::Runtime::InitializeInternal(): error: undefined reference to 'ara::com::Runtime::StartBindings()'
         # bazel-out/k8-fastbuild/bin/bsw/amsr_vector_fs_socal/lib/libSocal.a(runtime.cpp.o):runtime.cpp:function ara::com::Runtime::DeInitializeCommunication(): error: undefined reference to 'ara::com::Runtime::DeinitializeBindings()'
	 "src/stubs/ara_com_Runtime_stub.cpp",
         # ----------------------------------------------------------------------------------------------------------------------------------
         # The following is needed for the these errors until the proper src/ara/core/initialization.cpp file is generated by the genrules/generators in their output
	 # bazel-out/k8-fastbuild/bin/application/avatar_router/_objs/avatar_router_app/main.pic.o:main.cpp:function main: error: undefined reference to 'ara::core::Initialize()'
         # bazel-out/k8-fastbuild/bin/application/avatar_router/_objs/avatar_router_app/main.pic.o:main.cpp:function main: error: undefined reference to 'ara::core::Deinitialize()'
	 "src/stubs/ara_core_initialization_stub.cpp",
         #":applicationbase_init_deinit_srcs",   # this needs to be enabled later when proper file support to initialization.cpp file is generated by the genrules/generators
         # ----------------------------------------------------------------------------------------------------------------------------------

    #    "src/config_manager_application.cpp",
    #    "src/config_manager_application.h",
    #    "src/diagnostic_ssa_client/diagnostic_ssa_client.cpp",
    #    "src/diagnostic_ssa_client/diagnostic_ssa_client.h",
    #    "src/ext_vehicle_config_client/ext_vehicle_config_client.cpp",
    #    "src/ext_vehicle_config_client/ext_vehicle_config_client.h",
    #    "src/main.cpp",
    #    "src/persistent_mem_accessor/persistent_mem_accessor.cpp",
    #    "src/persistent_mem_accessor/persistent_mem_accessor.h",
    #    "src/vc_cnfg_mngr_server/vc_cnfg_mngr_server.cpp",
    #    "src/vc_cnfg_mngr_server/vc_cnfg_mngr_server.h",
    #    "src/x6aa_cnfg_mngr_kvs_keys.h",
    #    "src/x6aa_config_manager_error_domain.h",
    #    ":applicationbase_init_deinit_srcs",
    #    ":ipc_binding_life_cycle_manager",
    #    ":persistency_srcs",
    #    ":someip_binding_initializer",
    #    "//bsw:amsr_vector_fs_socal_libsocal_a",
    #    "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_file_storage_srcs",
    #    "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_key_value_storage_srcs",
    #    "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
        "socket",
    ],
    includes = [
	"app/src/",
	"stubs/src/",
	"deps/src/",
	"deps/src/ara/com/",
	"deps/src/ara/log/",
	"deps/src/ara/per/",
	"deps/src/ara/core/",
    ],
    linkstatic = 1,
    deps = [
        "//application/common:application_base",
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_characterconversion",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libiostream",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_per_libpersistency",
        "//bsw:amsr_vector_fs_socal",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_vajson",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":avatar_router_app": "bin/avatar_router",
        ":logging_config_json": "etc/logging_config.json",
        ":com_application_json": "etc/com_application.json",
    #    ":exec_config": "etc/exec_config.json",
    #    ":swcl_db": "etc/swcl_db.json",
    #    ":swcluster_meta": "etc/swcl_package_metadata.json",
    #    ":static_sd_config": "etc/static_sd_config.json",
    #    ":someip_config": "etc/someip_config.json",
    #    ":updatemanager_daemon": "etc/updatemanager.json",
    #    ":persistency_config_json": "etc/per_key_value_storage_config.json",
    },
    mode = "0755",
    package_dir = "opt/avatar_router",
)

