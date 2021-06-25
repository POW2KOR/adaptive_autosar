load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

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

genr_ignore_patterns = [
    "X6AA_DLT_Executable.*",
    "X6AA_Dummy_SWC_1_Executable.*",
    "X6AA_Dummy_SWC_2_Executable.*",
    "X6AA_Ressource_Executable.*",
    "X6AA_Cnfg_Mngr_Executable.*",
    "TransmissionManager_ROVExecutable.*",
    "SelfDiagnosticAgent_Executable.*",
]

filegroup(
    name = "logging_config",
    srcs = ["configs/logging_config.json"],
)

filegroup(
    name = "com_application",
    srcs = ["configs/com_application.json"],
)

filegroup(
    name = "diagnosticmanager_doip_config",
    srcs = ["configs/diagnosticmanager_doip.json"],
)

filegroup(
    name = "diagnosticmanager_config",
    srcs = ["configs/diagnosticmanager.json"],
)

# When we run our file system it runs the DiagnosticManager. It then checks for
# the files inside the nv_data folder. On the first run it doesn't find the
# files. So it throws some error and continue running. Than it create these
# files with particular Header and body for each of them. So that in the
# subsequent run it can use those files. Now As we run our stack from
# minerva_filesystem.tar each time and the file getting generated are not being
# saved as part of fie system, we will see these errors every time we run the
# stack.

# So the solution was to copy the generated files and provide it statically in
# our file system, so that DiagnosticManager finds it.
filegroup(
    name = "diagnostic_manager_nv_data",
    srcs = ["configs/nv_data"],
)

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
            "DiagnosticManagerDeamonExecutable/configuration/exec_config.json",
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
            "DiagnosticManagerDeamonExecutable/src/ara/core/initialization.cpp",
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
            "DiagnosticManagerDeamonExecutable/swcl_package_metadata.json",
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
            "DiagnosticManagerDeamonExecutable/etc/swcl_db.json",
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
        "persistency_config_cmake": [
            "DiagnosticManagerDeamonExecutable/amsr-vector-fs-per-libpersistency.cmake",
        ],
        "persistency_file_storage_config_json": [
            "DiagnosticManagerDeamonExecutable/etc/per_file_storage_config.json",
        ],
        "persistency_config_hdrs": [
            "DiagnosticManagerDeamonExecutable/include/ara/per/detail/dynamic_key_value_storage_decl.h",
            "DiagnosticManagerDeamonExecutable/include/ara/per/internal/config_validation_keys.h",
            "DiagnosticManagerDeamonExecutable/include/ara/per/key_value_storage_data_visitor.h",
            "DiagnosticManagerDeamonExecutable/include/ara/per/key_value_storage_variant.h",
        ],
        "persistency_config_srcs": [
            "DiagnosticManagerDeamonExecutable/src/ara/per/dynamic_object_parser.cpp",
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
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_bytevectortype.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_conversationhandle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_daemonrequestresponsetype.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_diagrequesttype.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_handletype.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_instancehandle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_jobidentifier.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/com_api/impl_type_metainfotype.h",
            "DiagnosticManagerDeamonExecutable/include/ara/diag/impl_type_string.h",
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
        # Currently there are no files generated for diagmanager
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
        "someipprotocol_config_hdrs": [
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/events/deserializer_DaemonRequestResponse.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/events/deserializer_DiagRequest.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_Canceljob_identifier.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyResponsebyte_vector.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyResponsejob_identifier.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyResponseresponse_type.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValuebyte_vector.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValueconversation_handle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValuehandle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValueinstance_handle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDataconversation_handle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatahandle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatainstance_handle.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatajob_identifier.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatameta_info.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatarequest_data.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/diag/com_api/deserializer_DaemonRequestResponseType.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/datatype_deserialization/amsr/diag/com_api/deserializer_DiagRequestType.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/method_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_Request_Cancel.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/method_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_Request_NotifyResponse.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/method_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_Request_NotifyValue.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/someip_protocol/internal/method_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_Request_RequestData.h",
        ],
        "someipprotocol_config_srcs": [
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/events/deserializer_DaemonRequestResponse.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/amsr_diag_service_interfaces_diag_com_api/events/deserializer_DiagRequest.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_Canceljob_identifier.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyResponsebyte_vector.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyResponsejob_identifier.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyResponseresponse_type.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValuebyte_vector.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValueconversation_handle.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValuehandle.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_NotifyValueinstance_handle.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDataconversation_handle.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatahandle.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatainstance_handle.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatajob_identifier.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatameta_info.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/amsr_diag_service_interfaces_diag_com_api/methods/serializer_RequestDatarequest_data.cpp",
        ],
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
            "DiagnosticManagerDeamonExecutable/src/amsr/diag/service_interfaces/diag_com_api/diagcomapi.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/diag/service_interfaces/diag_com_api/diagcomapi_proxy.cpp",
            "DiagnosticManagerDeamonExecutable/src/ara/com/runtime_gen.cpp",
        ],
        "socal_hdrs": [
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_internal.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_update_manager.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/service_interfaces/diag_com_api/DiagComApi_types.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/service_interfaces/diag_com_api/diagcomapi_common.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/diag/service_interfaces/diag_com_api/diagcomapi_proxy.h",
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
        "ipcbinding_hdrs": [
            "DiagnosticManagerDeamonExecutable/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_ipc_binding.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_ipc_event_manager.h",
            "DiagnosticManagerDeamonExecutable/include/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_ipc_methods.h",
        ],
        "ipcbinding_srcs": [
            "DiagnosticManagerDeamonExecutable/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_ipc_binding.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_ipc_event_manager.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/ipc_binding_transformation_layer/internal/amsr/diag/service_interfaces/diag_com_api/DiagComApi_proxy_ipc_methods.cpp",
            "DiagnosticManagerDeamonExecutable/src/amsr/ipc_binding_transformation_layer/internal/ipc_binding_life_cycle_manager.cpp",
        ],
    },
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
        "diag_uds_srcs": [
            "DiagnosticManagerDeamonExecutable/src/amsr/dm/uds_transport/uds_transport_protocol_creator.cpp",
        ],
        "dm_server_config_json": [
            "DiagnosticManagerDeamonExecutable/etc/dm_server_config_SoftwareClusterPlatform.json",
        ],
        "dm_global_settings_json": [
            "DiagnosticManagerDeamonExecutable/etc/dm_global_settings.json",
        ],
    },
)

cc_library(
    name = "modeldatatypes_hdrs_lib",
    hdrs = [
        ":modeldatatypes_hdrs",
    ],
    strip_include_prefix = "modeldatatypes_hdrs/output/DiagnosticManagerDeamonExecutable/include/",
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/DiagnosticManagerDeamonExecutable/include/",
)

cc_library(
    name = "ipcbinding_hdrs_lib",
    hdrs = [
        ":ipcbinding_hdrs",
    ],
    strip_include_prefix = "ipcbinding_hdrs/output/DiagnosticManagerDeamonExecutable/include/",
)

cc_library(
    name = "someipprotocol_config_hdrs_lib",
    hdrs = [
        ":someipprotocol_config_hdrs",
    ],
    strip_include_prefix = "someipprotocol_config_hdrs/output/DiagnosticManagerDeamonExecutable/include/",
)

cc_library(
    name = "persistency_config_hdrs_lib",
    hdrs = [
        ":persistency_config_hdrs",
    ],
    strip_include_prefix = "persistency_config_hdrs/output/DiagnosticManagerDeamonExecutable/include/",
)

cc_binary(
    name = "app",
    srcs = [
        ":applicationbase_init_deinit_srcs",
        ":diag_uds_srcs",
        ":ipcbinding_srcs",
        ":persistency_config_srcs",
        ":socal_scrs",
        ":someipprotocol_config_srcs",
        "@amsr_xavier//:amsr_vector_fs_diagnosticmanager_main",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_file_storage_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_key_value_storage_srcs",
        "@amsr_xavier//:amsr_vector_fs_per_libpersistency_persistency_srcs",
        "@amsr_xavier//:diag_com_deamon_srcs",
        "@amsr_xavier//:diag_deamon_rpc_srcs",
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
        "VIRTUALMOCK=",
        "ENABLE_EXEC_MANAGER=ON",
    ],
    deps = [
        ":ipcbinding_hdrs_lib",
        ":modeldatatypes_hdrs_lib",
        ":persistency_config_hdrs_lib",
        ":socal_hdrs_lib",
        ":someipprotocol_config_hdrs_lib",
        "//bsw:amsr_vector_fs_ipcbinding",
        "//bsw:amsr_vector_fs_per_libpersistency",
        "@amsr_xavier//:diag_com_deamon_hdrs_lib",
        "@amsr_xavier//:diag_com_deamon_src_hdrs_lib",
        "@amsr_xavier//:diag_daemon_impl",
        "@amsr_xavier//:diag_deamon_rpc_hdrs_lib",
        "@amsr_xavier//:diag_deamon_rpc_src_hdrs_lib",
        "@amsr_xavier//:lib_doip_binding_hdrs_lib",
        "@minerva_mpu_adaptive//bsw:amsr_vector_fs_doipbinding",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/DiagnosticManagerDeamonExecutable",
        ":logging_config": "etc/logging_config.json",
        ":com_application": "etc/com_application.json",
        ":exec_config": "etc/exec_config.json",
        ":swcl_db": "etc/swcl_db.json",
        ":swcluster_meta": "etc/swcl_package_metadata.json",
        ":diagnosticmanager_doip_config": "etc/diagnosticmanager_doip.json",
        ":diagnosticmanager_config": "etc/diagnosticmanager.json",
        ":dm_global_settings_json": "etc/dm_global_settings.json",
        ":dm_server_config_json": "etc/dm_server_config_SoftwareClusterPlatform.json",
        ":persistency_file_storage_config_json": "etc/per_file_storage_config.json",
        "//application/sda:updatemanager": "etc/updatemanager.json",
        ":diagnostic_manager_nv_data": "etc/nv_data",
    },
    mode = "0755",
    package_dir = "opt/DiagnosticManagerDeamonExecutable",
)
