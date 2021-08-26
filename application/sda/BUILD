load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "@sda_xavier//:sda_model",
        # Workaround to overcome the issue for the missing reference for
        # /design/IF_Persistency_KVS from the x6aa_config_manager,
        "//application/x6aa_config_manager:app_arxml",
        #"//arxmls:x6aa_idc_ecu_extract_arxml",
        #"@amsr_xavier//:mex_arxml",
    ],
)

filegroup(
    name = "logging_config",
    srcs = ["configs/logging_config.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "com_application",
    srcs = ["configs/com_application.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "config_ini",
    srcs = ["configs/config.ini"],
    visibility = ["//visibility:public"],
)

genr_ignore_patterns = [
    "X6AA_DLT_Executable.*",
    "X6AA_Dummy_SWC_1_Executable.*",
    "X6AA_Dummy_SWC_2_Executable.*",
    "X6AA_Ressource_Executable.*",
    "X6AA_Cnfg_Mngr_Executable.*",
    "TransmissionManager_ROVExecutable.*",
    "DiagnosticManagerDeamonExecutable.*",
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
            "SelfDiagnosticAgent_Executable/configuration/exec_config.json",
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
            "SelfDiagnosticAgent_Executable/src/ara/core/initialization.cpp",
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
            "SelfDiagnosticAgent_Executable/swcl_package_metadata.json",
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
            "SelfDiagnosticAgent_Executable/etc/swcl_db.json",
        ],
        "updatemanager": [
            "SelfDiagnosticAgent_Executable/etc/updatemanager.json",
        ],
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
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "persistency_config_gen_rule_hdrs": [
            "SelfDiagnosticAgent_Executable/include/ara/per/detail/dynamic_key_value_storage_decl.h",
            "SelfDiagnosticAgent_Executable/include/ara/per/internal/config_validation_keys.h",
            "SelfDiagnosticAgent_Executable/include/ara/per/key_value_storage_data_visitor.h",
            "SelfDiagnosticAgent_Executable/include/ara/per/key_value_storage_variant.h",
        ],
        "persistency_config_gen_rule_srcs": [
            "SelfDiagnosticAgent_Executable/src/ara/per/dynamic_object_parser.cpp",
        ],
        "persistency_file_storage_config": [
            "SelfDiagnosticAgent_Executable/etc/per_file_storage_config.json",
        ],
        "persistency_key_value_storage_config": [
            "SelfDiagnosticAgent_Executable/etc/per_key_value_storage_config.json",
        ],
        "persistency_cmake": [
            "SelfDiagnosticAgent_Executable/amsr-vector-fs-per-libpersistency.cmake",
        ],
    },
)

cc_library(
    name = "persistency_config_gen_rule_hdrs_lib",
    hdrs = [
        ":persistency_config_gen_rule_hdrs",
    ],
    strip_include_prefix = "persistency_config_gen_rule_hdrs/output/SelfDiagnosticAgent_Executable/include/",
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
            "SelfDiagnosticAgent_Executable/include/DataTypes/REC_DI_Odo_Pr5_ST3_9t50popkpz30is106xpis1iyh/impl_type_rec_di_odo_pr5_st3_9t50popkpz30is106xpis1iyh.h",
            "SelfDiagnosticAgent_Executable/include/DataTypes/REC_Ign_Stat_Pr5_ST3_b0ko81o0x5jgvwtduf99gvzi0/impl_type_rec_ign_stat_pr5_st3_b0ko81o0x5jgvwtduf99gvzi0.h",
            "SelfDiagnosticAgent_Executable/include/DataTypes/REC_PT4_PTCoor4_Pr5_ST3_a1o7mhv0xy8ny0vccjf09ttgc/impl_type_rec_pt4_ptcoor4_pr5_st3_a1o7mhv0xy8ny0vccjf09ttgc.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_bytevectortype.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_conversationhandle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_daemonrequestresponsetype.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_diagrequesttype.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_handletype.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_instancehandle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_jobidentifier.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/com_api/impl_type_metainfotype.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_stringtype.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_stringvector.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_versioninformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_versioninformationlist.h",
            "SelfDiagnosticAgent_Executable/include/ara/diag/impl_type_string.h",
            "SelfDiagnosticAgent_Executable/include/self_diag_agent/impl_type_arraybytes2.h",
            "SelfDiagnosticAgent_Executable/include/self_diag_agent/impl_type_bytevector.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_hcpsoftwareinformation.h",
            "SelfDiagnosticAgent_Executable/include/self_diag_agent/impl_type_identificationarray.h",
        ],
    },
)

cc_library(
    name = "modeldatatypes_hdrs_lib",
    hdrs = [
        ":modeldatatypes_hdrs",
    ],
    strip_include_prefix = "modeldatatypes_hdrs/output/SelfDiagnosticAgent_Executable/include/",
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
        "someip_config": [
            "SelfDiagnosticAgent_Executable/configuration/someip_config.json",
        ],
        "static_sd_config": [
            "SelfDiagnosticAgent_Executable/configuration/static_sd_config.json",
        ],
        "someipbinding_hdrs": [
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_DI_Odo_Pr5_ST3_9t50popkpz30is106xpis1iyh/deserializer_REC_DI_Odo_Pr5_ST3_9t50popkpz30is106xpis1iyh_1.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_Ign_Stat_Pr5_ST3_b0ko81o0x5jgvwtduf99gvzi0/deserializer_REC_Ign_Stat_Pr5_ST3_b0ko81o0x5jgvwtduf99gvzi0_2.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_PT4_PTCoor4_Pr5_ST3_a1o7mhv0xy8ny0vccjf09ttgc/deserializer_REC_PT4_PTCoor4_Pr5_ST3_a1o7mhv0xy8ny0vccjf09ttgc_4.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/deserializer_uint8_t_3.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_someip_binding.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_someip_binding_init.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_someip_event_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_someip_methods.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_someip_proxy_factory.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_someip_binding.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_someip_binding_init.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_someip_event_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_someip_methods.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_someip_proxy_factory.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_someip_binding.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_someip_binding_init.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_someip_event_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_someip_methods.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_someip_proxy_factory.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_someip_binding.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_someip_binding_init.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_someip_event_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_someip_methods.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_someip_proxy_factory.h",
        ],
        "someipbinding_srcs": [
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/someip_binding_initializer.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_DI_Odo_Pr5_ST3_9t50popkpz30is106xpis1iyh/deserializer_REC_DI_Odo_Pr5_ST3_9t50popkpz30is106xpis1iyh_1.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_Ign_Stat_Pr5_ST3_b0ko81o0x5jgvwtduf99gvzi0/deserializer_REC_Ign_Stat_Pr5_ST3_b0ko81o0x5jgvwtduf99gvzi0_2.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/REC_PT4_PTCoor4_Pr5_ST3_a1o7mhv0xy8ny0vccjf09ttgc/deserializer_REC_PT4_PTCoor4_Pr5_ST3_a1o7mhv0xy8ny0vccjf09ttgc_4.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/deserializer_uint8_t_3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_someip_binding.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_someip_binding_init.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_someip_event_manager.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_someip_binding.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_someip_binding_init.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_someip_event_manager.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_someip_binding.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_someip_binding_init.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_someip_event_manager.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_someip_binding.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_someip_binding_init.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_someip_event_manager.cpp",
        ],
    },
)

cc_library(
    name = "someipbinding_hdrs_lib",
    hdrs = [
        ":someipbinding_hdrs",
    ],
    strip_include_prefix = "someipbinding_hdrs/output/SelfDiagnosticAgent_Executable/include/",
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
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwarePartNumbersSoftwarePartNumbers.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationShadowversion_information_list.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationversion_information_list.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_immobilizer_master_service_st3/events/deserializer_Ev_Ign_Stat_Pr5_ST3.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_odospeedometer_service_st3/events/deserializer_Ev_DI_Odo_Pr5_ST3.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pn14_master_service_st3/events/deserializer_Ev_PN14_DDP_SwStat_ST3.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pt4_ptcoor_service_st3/events/deserializer_Ev_PT4_PTCoor4_Pr5_ST3.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/REC_DI_Odo_Pr5_ST3_9t50popkpz30is106xpis1iyh/deserializer_REC_DI_Odo_Pr5_ST3_9t50popkpz30is106xpis1iyh.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/REC_Ign_Stat_Pr5_ST3_b0ko81o0x5jgvwtduf99gvzi0/deserializer_REC_Ign_Stat_Pr5_ST3_b0ko81o0x5jgvwtduf99gvzi0.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/REC_PT4_PTCoor4_Pr5_ST3_a1o7mhv0xy8ny0vccjf09ttgc/deserializer_REC_PT4_PTCoor4_Pr5_ST3_a1o7mhv0xy8ny0vccjf09ttgc.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/swuc/deserializer_VersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetHCPSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwarePartNumbers.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwareVersionInformationShadow.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetHCPSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwarePartNumbers.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwareVersionInformationShadow.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Canceljob_identifier.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsebyte_vector.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsejob_identifier.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponseresponse_type.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuebyte_vector.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueconversation_handle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuehandle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueinstance_handle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDataconversation_handle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatahandle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatainstance_handle.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatajob_identifier.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatameta_info.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatarequest_data.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DaemonRequestResponse.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DiagRequest.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_serialization/amsr/diag/com_api/serializer_DaemonRequestResponseType.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_serialization/amsr/diag/com_api/serializer_DiagRequestType.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_Cancel.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_NotifyResponse.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_NotifyValue.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_RequestData.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetHCPSoftwareInformationhcp_software_information.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/swuc/deserializer_HCPSoftwareInformation.h",
        ],
        "someipprotocol_srcs": [
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwarePartNumbersSoftwarePartNumbers.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationShadowversion_information_list.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationversion_information_list.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_immobilizer_master_service_st3/events/deserializer_Ev_Ign_Stat_Pr5_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_odospeedometer_service_st3/events/deserializer_Ev_DI_Odo_Pr5_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pn14_master_service_st3/events/deserializer_Ev_PN14_DDP_SwStat_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pt4_ptcoor_service_st3/events/deserializer_Ev_PT4_PTCoor4_Pr5_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Canceljob_identifier.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsebyte_vector.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsejob_identifier.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponseresponse_type.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuebyte_vector.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueconversation_handle.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuehandle.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueinstance_handle.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDataconversation_handle.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatahandle.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatainstance_handle.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatajob_identifier.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatameta_info.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatarequest_data.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DaemonRequestResponse.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DiagRequest.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetHCPSoftwareInformationhcp_software_information.cpp",
        ],
    },
)

cc_library(
    name = "someipprotocol_hdrs_lib",
    hdrs = [
        ":someipprotocol_hdrs",
    ],
    strip_include_prefix = "someipprotocol_hdrs/output/SelfDiagnosticAgent_Executable/include/",
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
        "socal_hdrs": [
            "SelfDiagnosticAgent_Executable/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_impl_interface.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi_types.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/service_interfaces/diag_com_api/diagcomapi_common.h",
            "SelfDiagnosticAgent_Executable/include/amsr/diag/service_interfaces/diag_com_api/diagcomapi_skeleton.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/SWUC_SDA_ServiceInterface.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_internal.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_update_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/SWUC_SDA_ServiceInterface_types.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/swuc_sda_serviceinterface_common.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/swuc_sda_serviceinterface_proxy.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_internal.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_proxy_update_manager.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_immobilizer_master_service_st3/SI_Immobilizer_Master_Service_ST3_types.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_immobilizer_master_service_st3/si_immobilizer_master_service_st3_common.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_immobilizer_master_service_st3/si_immobilizer_master_service_st3_proxy.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_internal.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_proxy_update_manager.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_odospeedometer_service_st3/SI_DI_OdoSpeedometer_Service_ST3_types.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_odospeedometer_service_st3/si_di_odospeedometer_service_st3_common.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_odospeedometer_service_st3/si_di_odospeedometer_service_st3_proxy.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_internal.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_proxy_update_manager.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pn14_master_service_st3/SI_PN14_Master_Service_ST3_types.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pn14_master_service_st3/si_pn14_master_service_st3_common.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pn14_master_service_st3/si_pn14_master_service_st3_proxy.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_internal.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_proxy_update_manager.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pt4_ptcoor_service_st3/SI_PT4_PTCoor_Service_ST3_types.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pt4_ptcoor_service_st3/si_pt4_ptcoor_service_st3_common.h",
            "SelfDiagnosticAgent_Executable/include/services/ns_pt4_ptcoor_service_st3/si_pt4_ptcoor_service_st3_proxy.h",
        ],
        "socal_srcs": [
            "SelfDiagnosticAgent_Executable/src/amsr/diag/service_interfaces/diag_com_api/diagcomapi.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/diag/service_interfaces/diag_com_api/diagcomapi_skeleton.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/swuc/swuc_sda_serviceinterface.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/swuc/swuc_sda_serviceinterface_proxy.cpp",
            "SelfDiagnosticAgent_Executable/src/ara/com/runtime_gen.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_immobilizer_master_service_st3/si_immobilizer_master_service_st3.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_immobilizer_master_service_st3/si_immobilizer_master_service_st3_proxy.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_odospeedometer_service_st3/si_di_odospeedometer_service_st3.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_odospeedometer_service_st3/si_di_odospeedometer_service_st3_proxy.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_pn14_master_service_st3/si_pn14_master_service_st3.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_pn14_master_service_st3/si_pn14_master_service_st3_proxy.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_pt4_ptcoor_service_st3/si_pt4_ptcoor_service_st3.cpp",
            "SelfDiagnosticAgent_Executable/src/services/ns_pt4_ptcoor_service_st3/si_pt4_ptcoor_service_st3_proxy.cpp",
        ],
    },
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/SelfDiagnosticAgent_Executable/include/",
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
        "ipcbinding_hdrs": [
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_binding.h",
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_event_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_methods.h",
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_binding.h",
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_event_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_method_manager.h",
        ],
        "ipcbinding_srcs": [
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/ipc_binding_life_cycle_manager.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_binding.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_event_manager.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_methods.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_binding.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_event_manager.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_method_manager.cpp",
        ],
    },
)

cc_library(
    name = "ipcbinding_hdrs_lib",
    hdrs = [
        ":ipcbinding_hdrs",
    ],
    strip_include_prefix = "ipcbinding_hdrs/output/SelfDiagnosticAgent_Executable/include/",
)

minerva_aa_codegen_rule(
    name = "diag_api_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_diag_api",
        "@amsr_xavier//:generator_amsr_diag_daemon",
        "@amsr_xavier//:generator_amsr_em_daemon",
        "@amsr_xavier//:generator_amsr_logapi_config",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "sda_diag_hdrs": [
            "SelfDiagnosticAgent_Executable/include/ara/diag/ActiveDiagnosticInformation_Interface.h",
            "SelfDiagnosticAgent_Executable/include/ara/diag/Prepare_Vehicle_Systems_For_Reprogramming_Interface.h",
            "SelfDiagnosticAgent_Executable/include/ara/diag/SwucDataIdentifiers.h",
            "SelfDiagnosticAgent_Executable/include/ara/diag/SystemInfoDataIdentifier.h",
            "SelfDiagnosticAgent_Executable/include/ara/diag/Vehicle_Odometer_in_Low_Resolution.h",
        ],
        "sda_diag_srcs": [
            "SelfDiagnosticAgent_Executable/src/amsr/diag/ara_diag_application_config.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/diag/instance_specifier_mapping.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/diag_rpc_com/app/ara_com_config_generated.cpp",
            "SelfDiagnosticAgent_Executable/src/ara/diag/ActiveDiagnosticInformation_Interface.cpp",
            "SelfDiagnosticAgent_Executable/src/ara/diag/Prepare_Vehicle_Systems_For_Reprogramming_Interface.cpp",
            "SelfDiagnosticAgent_Executable/src/ara/diag/SwucDataIdentifiers.cpp",
            "SelfDiagnosticAgent_Executable/src/ara/diag/SystemInfoDataIdentifier.cpp",
            "SelfDiagnosticAgent_Executable/src/ara/diag/Vehicle_Odometer_in_Low_Resolution.cpp",
        ],
    },
)

cc_library(
    name = "sda_diag_hdrs_lib",
    hdrs = [
        ":sda_diag_hdrs",
    ],
    strip_include_prefix = "sda_diag_hdrs/output/SelfDiagnosticAgent_Executable/include/",
)

cc_binary(
    name = "app",
    srcs = [
        ":applicationbase_init_deinit_srcs",
        ":ipcbinding_srcs",
        ":persistency_config_gen_rule_srcs",
        ":sda_diag_srcs",
        ":socal_srcs",
        ":someipbinding_srcs",
        ":someipprotocol_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_file_storage_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_key_value_storage_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_srcs",
        "@amsr_xavier//:ara_diag_src",
        "@amsr_xavier//:diag_com_api_srcs",
        "@amsr_xavier//:diag_com_deamon_srcs",
        "@amsr_xavier//:diag_deamon_rpc_srcs",
        "@amsr_xavier//:diag_rpc_com_binding_srcs",
        "@amsr_xavier//:lib_doip_binding_srcs",
        "@sda_xavier//:self_diag_agent_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    local_defines = [
        "VIRTUALMOCK=",
        "ENABLE_EXEC_MANAGER=ON",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":ipcbinding_hdrs_lib",
        ":modeldatatypes_hdrs_lib",
        ":persistency_config_gen_rule_hdrs_lib",
        ":sda_diag_hdrs_lib",
        ":socal_hdrs_lib",
        ":someipbinding_hdrs_lib",
        ":someipprotocol_hdrs_lib",
        "@amsr_xavier//:ara_diag_hdrs_lib",
        "@amsr_xavier//:ara_diag_src_hdrs_lib",
        "@amsr_xavier//:diag_com_api_hdrs_lib",
        "@amsr_xavier//:diag_com_deamon_hdrs_lib",
        "@amsr_xavier//:diag_com_deamon_src_hdrs_lib",
        "@amsr_xavier//:diag_daemon_impl",
        "@amsr_xavier//:diag_deamon_rpc_hdrs_lib",
        "@amsr_xavier//:diag_deamon_rpc_src_hdrs_lib",
        "@amsr_xavier//:diag_rpc_com_binding_srcs_lib",
        "@amsr_xavier//:lib_doip_binding_src_hdrs_lib",
        "@apricot_adaptive//application/diagnostic_manager_deamon_executable:socal_hdrs_lib",
        "@apricot_adaptive//bsw:amsr_vector_fs_applicationbase",
        "@apricot_adaptive//bsw:amsr_vector_fs_aradiag",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticrpc",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticrpccombinding",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticutility",
        "@apricot_adaptive//bsw:amsr_vector_fs_doipbinding",
        "@apricot_adaptive//bsw:amsr_vector_fs_ipcbinding",
        "@apricot_adaptive//bsw:amsr_vector_fs_per_libpersistency",
        "@apricot_adaptive//bsw:amsr_vector_fs_someipbinding",
        "@sda_xavier//:sda_hdrs_lib",
        "@sda_xavier//:self_diagnostic_agent_hdrs1",
        "@sda_xavier//:self_diagnostic_agent_hdrs10",
        "@sda_xavier//:self_diagnostic_agent_hdrs11",
        "@sda_xavier//:self_diagnostic_agent_hdrs12",
        "@sda_xavier//:self_diagnostic_agent_hdrs2",
        "@sda_xavier//:self_diagnostic_agent_hdrs3",
        "@sda_xavier//:self_diagnostic_agent_hdrs4",
        "@sda_xavier//:self_diagnostic_agent_hdrs5",
        "@sda_xavier//:self_diagnostic_agent_hdrs6",
        "@sda_xavier//:self_diagnostic_agent_hdrs7",
        "@sda_xavier//:self_diagnostic_agent_hdrs8",
        "@sda_xavier//:self_diagnostic_agent_hdrs9",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/SelfDiagnosticAgent_Executable",
        ":logging_config": "etc/logging_config.json",
        ":com_application": "etc/com_application.json",
        ":exec_config": "etc/exec_config.json",
        ":swcl_db": "etc/swcl_db.json",
        ":swcluster_meta": "etc/swcl_package_metadata.json",
        ":persistency_file_storage_config": "etc/per_file_storage_config.json",
        ":persistency_key_value_storage_config": "etc/per_key_value_storage_config.json",
        ":updatemanager": "etc/updatemanager.json",
        ":config_ini": "etc/config.ini",
        ":someip_config": "etc/someip_config.json",
        ":static_sd_config": "etc/static_sd_config.json",
    },
    mode = "0755",
    package_dir = "opt/SelfDiagnosticAgent_Executable",
)
