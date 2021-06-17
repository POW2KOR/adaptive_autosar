load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "SelfDiagnosticAgent_Executable/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "applicationbase_init_deinit_srcs": [
            "SelfDiagnosticAgent_Executable/src/ara/core/initialization.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "swcluster_meta": [
            "SelfDiagnosticAgent_Executable/swcl_package_metadata.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_daemon_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
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
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_persistency_config",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
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
        "persistency_config": [
            "SelfDiagnosticAgent_Executable/etc/per_file_storage_config.json",
            "SelfDiagnosticAgent_Executable/etc/per_key_value_storage_config.json",
        ],
        "persistency_cmake": [
            "SelfDiagnosticAgent_Executable/amsr-vector-fs-per-libpersistency.cmake",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "modeldatatypes_api_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
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
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_hpcsoftwareinformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_stringtype.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_stringvector.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_versioninformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/swuc/impl_type_versioninformationlist.h",
            "SelfDiagnosticAgent_Executable/include/ara/diag/impl_type_string.h",
            "SelfDiagnosticAgent_Executable/include/self_diag_agent/impl_type_arraybytes2.h",
            "SelfDiagnosticAgent_Executable/include/self_diag_agent/impl_type_bytevector.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipbinding_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipbinding",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "someip_binding_initializer": [
            "SelfDiagnosticAgent_Executable/src/amsr/someip_binding_transformation_layer/internal/someip_binding_initializer.cpp",
        ],
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
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetBootSoftwareVersionInformationversion_information.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetHCPSoftwareInformationhpc_software_information.h",
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
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/swuc/deserializer_HPCSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/swuc/deserializer_VersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetBootSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetHCPSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwarePartNumbers.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwareVersionInformationShadow.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetBootSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetHCPSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwarePartNumbers.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwareVersionInformationShadow.h",
        ],
        "someipbinding_srcs": [
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
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetBootSoftwareVersionInformationversion_information.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetHCPSoftwareInformationhpc_software_information.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwarePartNumbersSoftwarePartNumbers.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationShadowversion_information_list.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationversion_information_list.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_immobilizer_master_service_st3/events/deserializer_Ev_Ign_Stat_Pr5_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_odospeedometer_service_st3/events/deserializer_Ev_DI_Odo_Pr5_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pn14_master_service_st3/events/deserializer_Ev_PN14_DDP_SwStat_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pt4_ptcoor_service_st3/events/deserializer_Ev_PT4_PTCoor4_Pr5_ST3.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipprotocol_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipprotocol",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "someipprotocol_hdrs": [
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetBootSoftwareVersionInformationversion_information.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetHCPSoftwareInformationhpc_software_information.h",
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
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/swuc/deserializer_HPCSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/swuc/deserializer_VersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetBootSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetHCPSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwarePartNumbers.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Response_GetSoftwareVersionInformationShadow.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetBootSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetHCPSoftwareInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwarePartNumbers.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwareVersionInformation.h",
            "SelfDiagnosticAgent_Executable/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Request_GetSoftwareVersionInformationShadow.h",
        ],
        "someipprotocol_srcs": [
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetBootSoftwareVersionInformationversion_information.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetHCPSoftwareInformationhpc_software_information.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwarePartNumbersSoftwarePartNumbers.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationShadowversion_information_list.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_swuc/methods/deserializer_GetSoftwareVersionInformationversion_information_list.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_immobilizer_master_service_st3/events/deserializer_Ev_Ign_Stat_Pr5_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_odospeedometer_service_st3/events/deserializer_Ev_DI_Odo_Pr5_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pn14_master_service_st3/events/deserializer_Ev_PN14_DDP_SwStat_ST3.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_pt4_ptcoor_service_st3/events/deserializer_Ev_PT4_PTCoor4_Pr5_ST3.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "socal_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_socal",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
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

minerva_aa_codegen_rule(
    name = "ipcbinding_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@sda_xavier//:sda_model",
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
    ],
    outs_list_dict = {
        "ipc_binding_life_cycle_manager": [
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/ipc_binding_life_cycle_manager.cpp",
        ],
        "ipcbinding_hdrs": [
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_binding.h",
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_event_manager.h",
            "SelfDiagnosticAgent_Executable/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_methods.h",
        ],
        "ipcbinding_srcs": [
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_binding.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_event_manager.cpp",
            "SelfDiagnosticAgent_Executable/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_proxy_ipc_methods.cpp",
        ],
    },
)
