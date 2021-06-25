load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_bsw_module")

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
    name = "software_update_arxml",
    srcs = [
        "arxmls/SWUC_DiagCore_Deployment.arxml",
        "arxmls/SWUC_TPUM_Design.arxml",
        "arxmls/SWUC_DiagCore_Design.arxml",
        "arxmls/SWUC_TPUM_Types.arxml",
        "arxmls/SWUC_TPUM_Deployment.arxml",
        #"arxmls/example_em_app.arxml",
        "arxmls/SWUC_Deployment.arxml",
        "arxmls/SWUC_Design.arxml",
        "arxmls/SWUC_DiagCore_SDA_Interface_Deployment.arxml",
        "arxmls/SWUC_Diag_Design.arxml",
        "arxmls/SWUC_DiagCore_Types.arxml",
        "arxmls/SWUC_Diag_Deployment.arxml",
        "arxmls/softwarecluster_extensions.arxml",
        #"arxmls/SWUC_Types.arxml",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "per_sw_packages",
    srcs = ["per/amsr_swupdateclient/var/sw_packages"],
)

filegroup(
    name = "com_application",
    srcs = ["configs/com_application.json"],
)

genr_ignore_patterns = [
    "X6AA_DLT_Executable.*",
    "X6AA_Dummy_SWC_1_Executable.*",
    "X6AA_Dummy_SWC_2_Executable.*",
    "X6AA_Ressource_Executable.*",
    "X6AA_Cnfg_Mngr_Executable.*",
    "TransmissionManager_ROVExecutable.*",
    "SelfDiagnosticAgent_Executable.*",
    "DiagnosticManagerDeamonExecutable.*",
]

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "exec_config": [
            "amsr_swupdateclient/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "applicationbase_init_deinit_srcs": [
            "amsr_swupdateclient/src/ara/core/initialization.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "swcluster_meta": [
            "amsr_swupdateclient/swcl_package_metadata.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_daemon_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "swcl_db": [
            "amsr_swupdateclient/etc/swcl_db.json",
        ],
        "updatemanager": [
            "amsr_swupdateclient/etc/updatemanager.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "persistency_config_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_persistency_config",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "persistency_config_cmake": [
            "amsr_swupdateclient/amsr-vector-fs-per-libpersistency.cmake",
        ],
        "persistency_file_storage_config": [
            "amsr_swupdateclient/etc/per_file_storage_config.json",
        ],
        "persistency_key_value_storage_config": [
            "amsr_swupdateclient/etc/per_key_value_storage_config.json",
        ],
        "persistency_config_hdrs": [
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_currenttransfersession3289819023.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_fingerprint3090312903.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_hcpsoftwareinformation1287818765.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_regulationsoftwareidentification2851051036.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_reprogrammingattemptcounter4176763096.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_softwarecluster862934.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_swclusterinfotype961444321.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_swfile900479517.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_swpackage4162560005.h",
            "amsr_swupdateclient/include/amsr/per/deserializer/deserialize_versioninformation2214549969.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_currenttransfersession3289819023.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_fingerprint3090312903.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_hcpsoftwareinformation1287818765.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_regulationsoftwareidentification2851051036.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_reprogrammingattemptcounter4176763096.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_softwarecluster862934.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_swclusterinfotype961444321.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_swfile900479517.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_swpackage4162560005.h",
            "amsr_swupdateclient/include/amsr/per/serializer/serialize_versioninformation2214549969.h",
            "amsr_swupdateclient/include/ara/per/detail/dynamic_key_value_storage_decl.h",
            "amsr_swupdateclient/include/ara/per/internal/config_validation_keys.h",
            "amsr_swupdateclient/include/ara/per/key_value_storage_data_visitor.h",
            "amsr_swupdateclient/include/ara/per/key_value_storage_variant.h",
        ],
        "persistency_config_srcs": [
            "amsr_swupdateclient/src/ara/per/dynamic_object_parser.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "modeldatatypes_api_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "modeldatatypes_hdrs": [
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_bytevectortype.h",
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_conversationhandle.h",
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_daemonrequestresponsetype.h",
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_diagrequesttype.h",
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_handletype.h",
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_instancehandle.h",
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_jobidentifier.h",
            "amsr_swupdateclient/include/amsr/diag/com_api/impl_type_metainfotype.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_currenttransfersession.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_fingerprint.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_fingerprintid.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_hcpsoftwareinformation.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_regulationsoftwareidentification.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_reprogrammingattemptcounter.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_reprogrammingprocessstate.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_routinecheckmemorysignature.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_softwarecluster.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_softwareclusterlist.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_stringtype.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_stringvector.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_swclusterinfotype.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_swclusterstatetype.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_swfile.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_swfilelist.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_swpackage.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_swpackagestatetype.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_transferid.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_uint16vector.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_versioninformation.h",
            "amsr_swupdateclient/include/amsr/swuc/impl_type_versioninformationlist.h",
            "amsr_swupdateclient/include/ara/diag/impl_type_string.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipbinding_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipbinding",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        # Currently there are no files generated for diagmanager
    },
)

minerva_aa_codegen_rule(
    name = "someipprotocol_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_someipprotocol",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "someipprotocol_config_hdrs": [
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Canceljob_identifier.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsebyte_vector.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsejob_identifier.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponseresponse_type.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuebyte_vector.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueconversation_handle.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuehandle.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueinstance_handle.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDataconversation_handle.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatahandle.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatainstance_handle.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatajob_identifier.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatameta_info.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatarequest_data.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DaemonRequestResponse.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DiagRequest.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetHCPSoftwareInformationhcp_software_information.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetSoftwarePartNumbersSoftwarePartNumbers.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetSoftwareVersionInformationShadowversion_information_list.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetSoftwareVersionInformationversion_information_list.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/datatype_serialization/amsr/diag/com_api/serializer_DaemonRequestResponseType.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/datatype_serialization/amsr/diag/com_api/serializer_DiagRequestType.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/datatype_serialization/amsr/swuc/serializer_HCPSoftwareInformation.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/datatype_serialization/amsr/swuc/serializer_VersionInformation.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_Cancel.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_NotifyResponse.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_NotifyValue.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Request_RequestData.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Request_GetHCPSoftwareInformation.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Request_GetSoftwarePartNumbers.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Request_GetSoftwareVersionInformation.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_deserialization/amsr_swuc/methods/deserializer_Request_GetSoftwareVersionInformationShadow.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Response_GetHCPSoftwareInformation.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Response_GetSoftwarePartNumbers.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Response_GetSoftwareVersionInformation.h",
            "amsr_swupdateclient/include/amsr/someip_protocol/internal/method_serialization/amsr_swuc/methods/serializer_Response_GetSoftwareVersionInformationShadow.h",
        ],
        "someipprotocol_config_srcs": [
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_Canceljob_identifier.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsebyte_vector.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponsejob_identifier.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyResponseresponse_type.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuebyte_vector.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueconversation_handle.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValuehandle.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_NotifyValueinstance_handle.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDataconversation_handle.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatahandle.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatainstance_handle.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatajob_identifier.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatameta_info.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/methods/deserializer_RequestDatarequest_data.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DaemonRequestResponse.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/events/serializer_DiagRequest.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetHCPSoftwareInformationhcp_software_information.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetSoftwarePartNumbersSoftwarePartNumbers.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetSoftwareVersionInformationShadowversion_information_list.cpp",
            "amsr_swupdateclient/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_swuc/methods/serializer_GetSoftwareVersionInformationversion_information_list.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "socal_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_socal",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "socal_scrs": [
            "amsr_swupdateclient/src/amsr/diag/service_interfaces/diag_com_api/diagcomapi.cpp",
            "amsr_swupdateclient/src/amsr/diag/service_interfaces/diag_com_api/diagcomapi_skeleton.cpp",
            "amsr_swupdateclient/src/amsr/swuc/swuc_sda_serviceinterface.cpp",
            "amsr_swupdateclient/src/amsr/swuc/swuc_sda_serviceinterface_skeleton.cpp",
            "amsr_swupdateclient/src/ara/com/runtime_gen.cpp",
        ],
        "socal_hdrs": [
            "amsr_swupdateclient/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi.h",
            "amsr_swupdateclient/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_impl_interface.h",
            "amsr_swupdateclient/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi_types.h",
            "amsr_swupdateclient/include/amsr/diag/service_interfaces/diag_com_api/diagcomapi_common.h",
            "amsr_swupdateclient/include/amsr/diag/service_interfaces/diag_com_api/diagcomapi_skeleton.h",
            "amsr_swupdateclient/include/amsr/swuc/SWUC_SDA_ServiceInterface.h",
            "amsr_swupdateclient/include/amsr/swuc/SWUC_SDA_ServiceInterface_skeleton_impl_interface.h",
            "amsr_swupdateclient/include/amsr/swuc/SWUC_SDA_ServiceInterface_types.h",
            "amsr_swupdateclient/include/amsr/swuc/swuc_sda_serviceinterface_common.h",
            "amsr_swupdateclient/include/amsr/swuc/swuc_sda_serviceinterface_skeleton.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "ipcbinding_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_ipcbinding",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "ipcbinding_hdrs": [
            "amsr_swupdateclient/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_binding.h",
            "amsr_swupdateclient/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_event_manager.h",
            "amsr_swupdateclient/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_method_manager.h",
            "amsr_swupdateclient/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_skeleton_ipc_binding.h",
            "amsr_swupdateclient/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_skeleton_ipc_event_manager.h",
            "amsr_swupdateclient/include/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_skeleton_ipc_method_manager.h",
        ],
        "ipcbinding_srcs": [
            "amsr_swupdateclient/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_binding.cpp",
            "amsr_swupdateclient/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_event_manager.cpp",
            "amsr_swupdateclient/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_skeleton_ipc_method_manager.cpp",
            "amsr_swupdateclient/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_skeleton_ipc_binding.cpp",
            "amsr_swupdateclient/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_skeleton_ipc_event_manager.cpp",
            "amsr_swupdateclient/src/amsr/ipc_binding_transformation_layer/internal/amsr/swuc/SWUC_SDA_ServiceInterface_skeleton_ipc_method_manager.cpp",
            "amsr_swupdateclient/src/amsr/ipc_binding_transformation_layer/internal/ipc_binding_life_cycle_manager.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "diag_api_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        ":software_update_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_diag_api",
        "@amsr_xavier//:generator_amsr_diag_daemon",
        "@amsr_xavier//:generator_amsr_em_daemon",
        "@amsr_xavier//:generator_amsr_logapi_config",
    ],
    ignore_matches = genr_ignore_patterns,
    outs_list_dict = {
        "diag_srcs": [
            "amsr_swupdateclient/src/amsr/diag/ara_diag_application_config.cpp",
            "amsr_swupdateclient/src/amsr/diag/instance_specifier_mapping.cpp",
            "amsr_swupdateclient/src/amsr/diag_rpc_com/app/ara_com_config_generated.cpp",
            "amsr_swupdateclient/src/ara/diag/Diag_RoutineInterface_CheckMemory.cpp",
            "amsr_swupdateclient/src/ara/diag/Diag_RoutineInterface_CheckProgrammingDependencies.cpp",
            "amsr_swupdateclient/src/ara/diag/Diag_RoutineInterface_EraseMemory.cpp",
            "amsr_swupdateclient/src/ara/diag/Diag_RoutineInterface_VerifyMemoryContent.cpp",
        ],
        "diag_hdrs": [
            "amsr_swupdateclient/include/ara/diag/Diag_RoutineInterface_CheckMemory.h",
            "amsr_swupdateclient/include/ara/diag/Diag_RoutineInterface_CheckProgrammingDependencies.h",
            "amsr_swupdateclient/include/ara/diag/Diag_RoutineInterface_EraseMemory.h",
            "amsr_swupdateclient/include/ara/diag/Diag_RoutineInterface_VerifyMemoryContent.h",
        ],
        "logging_config": [
            "amsr_swupdateclient/etc/logging_config.json",
        ],
    },
)

cc_library(
    name = "modeldatatypes_hdrs_lib",
    hdrs = [
        ":modeldatatypes_hdrs",
    ],
    strip_include_prefix = "modeldatatypes_hdrs/output/amsr_swupdateclient/include/",
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/amsr_swupdateclient/include/",
)

cc_library(
    name = "ipcbinding_hdrs_lib",
    hdrs = [
        ":ipcbinding_hdrs",
    ],
    strip_include_prefix = "ipcbinding_hdrs/output/amsr_swupdateclient/include/",
)

cc_library(
    name = "someipprotocol_config_hdrs_lib",
    hdrs = [
        ":someipprotocol_config_hdrs",
    ],
    strip_include_prefix = "someipprotocol_config_hdrs/output/amsr_swupdateclient/include/",
)

cc_library(
    name = "persistency_config_hdrs_lib",
    hdrs = [
        ":persistency_config_hdrs",
    ],
    strip_include_prefix = "persistency_config_hdrs/output/amsr_swupdateclient/include/",
)

cc_library(
    name = "diag_hdrs_lib",
    hdrs = [
        ":diag_hdrs",
    ],
    strip_include_prefix = "diag_hdrs/output/amsr_swupdateclient/include/",
)

cc_binary(
    name = "app",
    srcs = [
        ":applicationbase_init_deinit_srcs",
        ":diag_srcs",
        ":ipcbinding_srcs",
        ":persistency_config_srcs",
        ":socal_scrs",
        ":someipprotocol_config_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_file_storage_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_key_value_storage_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_srcs",
        "@amsr_xavier//:amsr_vector_fs_swupdateclient_main",
        "@amsr_xavier//:ara_diag_src",
        "@amsr_xavier//:diag_com_api_srcs",
        "@amsr_xavier//:diag_com_deamon_srcs",
        "@amsr_xavier//:diag_deamon_rpc_srcs",
        "@amsr_xavier//:diag_rpc_com_binding_srcs",
        "@amsr_xavier//:lib_doip_binding_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    local_defines = [
        "ENABLE_NVIDIA_UPDATE_STRATEGY=ON",
        "VIRTUALMOCK=",
        "ENABLE_EXEC_MANAGER=ON",
    ],
    deps = [
        ":ipcbinding_hdrs_lib",
        ":socal_hdrs_lib",
        ":someipprotocol_config_hdrs_lib",
        "//bsw:amsr_vector_fs_ipcbinding",
        "@amsr_xavier//:amsr_swupdate_common",
        "@amsr_xavier//:amsr_swupdate_diag_core",
        "@amsr_xavier//:amsr_swupdate_ucm_client",
        "@amsr_xavier//:ara_diag_hdrs_lib",
        "@amsr_xavier//:ara_diag_src_hdrs_lib",
        "@amsr_xavier//:diag_com_api_hdrs_lib",
        "@amsr_xavier//:diag_com_deamon_hdrs_lib",
        "@amsr_xavier//:diag_com_deamon_src_hdrs_lib",
        "@amsr_xavier//:diag_daemon_impl",
        "@amsr_xavier//:diag_deamon_rpc_hdrs_lib",
        "@amsr_xavier//:diag_deamon_rpc_src_hdrs_lib",
        "@amsr_xavier//:diag_rpc_com_binding_srcs_lib",
        "@amsr_xavier//:lib_doip_binding_hdrs_lib",
        "@amsr_xavier//:lib_doip_binding_src_hdrs_lib",
        "@amsr_xavier//:nvidia_update_strategy",
        "@minerva_mpu_adaptive//application/diagnostic_manager_deamon_executable:socal_hdrs_lib",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/amsr_swupdateclient",
        ":logging_config": "etc/logging_config.json",
        ":com_application": "etc/com_application.json",
        ":exec_config": "etc/exec_config.json",
        ":swcl_db": "etc/swcl_db.json",
        ":swcluster_meta": "etc/swcl_package_metadata.json",
        ":persistency_file_storage_config": "etc/per_file_storage_config.json",
        ":persistency_key_value_storage_config": "etc/per_key_value_storage_config.json",
        ":updatemanager": "etc/updatemanager.json",
        # In the latest delivery the persistency related folders are created
        # outside the etc directory. It is created at the same level of sbin
        # directory. For achiving that the use of "../../" is needed.
        ":per_sw_packages": "../../per/amsr_swupdateclient/var/sw_packages",
    },
    mode = "0755",
    package_dir = "opt/amsr_swupdateclient",
)
