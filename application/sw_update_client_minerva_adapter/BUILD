load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

filegroup(
    name = "app_arxml",
    srcs = [
        "sw_update_client_minerva_adapter_app/arxml/sw_update_client_minerva_adapter_app.arxml",
        "sw_update_client_minerva_adapter_interface/arxml/swuc_if.arxml",
        "@starter_kit_adaptive_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:ncd_arxml",
        "@starter_kit_adaptive_xavier//:standard_types_arxml",
    ],
)

minerva_aa_codegen_rule(
    name = "sw_update_client_minerva_adapter_app_gen_rule",
    arxml_srcs = [":app_arxml"],
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_swcluster_meta",
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_daemon",
        "@starter_kit_adaptive_xavier//:generator_amsr_em_exec_config",
        "@starter_kit_adaptive_xavier//:generator_amsr_applicationbase_init_deinit",
        "@starter_kit_adaptive_xavier//:generator_amsr_someipbinding",
        "@starter_kit_adaptive_xavier//:generator_amsr_someipprotocol",
        "@starter_kit_adaptive_xavier//:generator_amsr_socal",
        "@starter_kit_adaptive_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = [
        "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable.*",
        "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable.*",
    ],
    outs_list_dict = {
        "sw_update_client_minerva_adapter_app_updatemanager_daemon_db": [
            "sw_update_client_minerva_adapter_app/etc/swcl_db.json",
            "sw_update_client_minerva_adapter_app/etc/updatemanager.json",
        ],
        "sw_update_client_minerva_adapter_app_updatemanager_swcluser_meta": [
            "sw_update_client_minerva_adapter_app/swcl_package_metadata.json",
        ],
        "sw_update_client_minerva_adapter_app_exec_config": [
            "sw_update_client_minerva_adapter_app/configuration/exec_config.json",
        ],
        "sw_update_client_minerva_adapter_app_applicationbase_init_deinit_srcs": [
            "sw_update_client_minerva_adapter_app/src/ara/core/initialization.cpp",
        ],
        "sw_update_client_minerva_adapter_app_someip_config": [
            "sw_update_client_minerva_adapter_app/configuration/someip_config.json",
        ],
        "sw_update_client_minerva_adapter_app_someipprotocol_srcs": [
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/fields/serializer_progress.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/fields/serializer_status.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_GetResumePositionid.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_GetResumePositionposition.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_GetResumePositionversion.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Processfile.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_ProcessresumeOffset.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Activateswitch_ok.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Rollbackswitch_ok.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Verifymemory_ok.cpp",
        ],
        "sw_update_client_minerva_adapter_app_someipprotocol_hdrs": [
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/fields/serializer_progress.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/fields/serializer_status.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_GetResumePositionid.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_GetResumePositionposition.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_GetResumePositionversion.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/fields/deserializer_Request_progressGet.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/fields/deserializer_Request_statusGet.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Request_GetResumePosition.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_serialization/mb_swuc_service_interfaces_plugin/fields/serializer_Response_progressGet.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_serialization/mb_swuc_service_interfaces_plugin/fields/serializer_Response_statusGet.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Response_GetResumePosition.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Processfile.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_ProcessresumeOffset.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Activateswitch_ok.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Rollbackswitch_ok.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/dataprototype_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Verifymemory_ok.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Request_Activate.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Request_CleanUp.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Request_Process.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Request_Revert.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Request_Rollback.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_deserialization/mb_swuc_service_interfaces_plugin/methods/deserializer_Request_Verify.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Response_Activate.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Response_Rollback.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_protocol/internal/method_serialization/mb_swuc_service_interfaces_plugin/methods/serializer_Response_Verify.h",
        ],
        "sw_update_client_minerva_adapter_app_someipbinding_hdrs": [
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_skeleton_someip_binding.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_skeleton_someip_binding_init.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_skeleton_someip_event_manager.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_skeleton_someip_methods.h",
            "sw_update_client_minerva_adapter_app/includes/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_someip_skeleton_factory.h",
        ],
        "sw_update_client_minerva_adapter_app_someipbinding_srcs": [
            "sw_update_client_minerva_adapter_app/src/amsr/someip_binding_transformation_layer/internal/aracom_someip_binding_init.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_skeleton_someip_binding.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_skeleton_someip_binding_init.cpp",
            "sw_update_client_minerva_adapter_app/src/amsr/someip_binding_transformation_layer/internal/mb/swuc/service_interfaces/plugin/SwdlPlugin_skeleton_someip_event_manager.cpp",
        ],
        "sw_update_client_minerva_adapter_app_socal_srcs": [
            "sw_update_client_minerva_adapter_app/src/ara/com/resource_manager.cpp",
            "sw_update_client_minerva_adapter_app/src/ara/com/runtime_gen.cpp",
            "sw_update_client_minerva_adapter_app/src/ara/com/someip_resource_manager.cpp",
            "sw_update_client_minerva_adapter_app/src/mb/swuc/service_interfaces/plugin/swdlplugin.cpp",
            "sw_update_client_minerva_adapter_app/src/mb/swuc/service_interfaces/plugin/swdlplugin_resource_manager.cpp",
            "sw_update_client_minerva_adapter_app/src/mb/swuc/service_interfaces/plugin/swdlplugin_skeleton.cpp",
            "sw_update_client_minerva_adapter_app/src/mb/swuc/service_interfaces/plugin/swdlplugin_skeleton_resource_manager.cpp",
        ],
        "sw_update_client_minerva_adapter_app_socal_hdrs": [
            "sw_update_client_minerva_adapter_app/includes/ara/com/resource_manager.h",
            "sw_update_client_minerva_adapter_app/includes/ara/com/someip_resource_manager.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/service_interfaces/plugin/SwdlPlugin.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/service_interfaces/plugin/SwdlPlugin_proxy_backend_interface.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/service_interfaces/plugin/SwdlPlugin_types.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/service_interfaces/plugin/swdlplugin_common.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/service_interfaces/plugin/swdlplugin_resource_manager.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/service_interfaces/plugin/swdlplugin_skeleton.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/service_interfaces/plugin/swdlplugin_skeleton_resource_manager.h",
        ],
        "sw_update_client_minerva_adapter_app_modeldatatypes_hdrs": [
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/types/impl_type_bytevector.h",
            "sw_update_client_minerva_adapter_app/includes/mb/swuc/types/impl_type_pluginstatus.h",
        ],
    },
)

cc_library(
    name = "sw_update_client_minerva_adapter_app_socal_hdrs_lib",
    hdrs = [
        ":sw_update_client_minerva_adapter_app_socal_hdrs",
    ],
    strip_include_prefix = "sw_update_client_minerva_adapter_app_socal_hdrs/output/sw_update_client_minerva_adapter_app/includes",
)

cc_library(
    name = "sw_update_client_minerva_adapter_app_modeldatatypes_hdrs_lib",
    hdrs = [
        ":sw_update_client_minerva_adapter_app_modeldatatypes_hdrs",
    ],
    strip_include_prefix = "sw_update_client_minerva_adapter_app_modeldatatypes_hdrs/output/sw_update_client_minerva_adapter_app/includes",
)

cc_library(
    name = "sw_update_client_minerva_adapter_app_someipbinding_hdrs_lib",
    hdrs = [
        ":sw_update_client_minerva_adapter_app_someipbinding_hdrs",
    ],
    strip_include_prefix = "sw_update_client_minerva_adapter_app_someipbinding_hdrs/output/sw_update_client_minerva_adapter_app/includes",
)

cc_library(
    name = "sw_update_client_minerva_adapter_app_someipprotocol_hdrs_lib",
    hdrs = [
        ":sw_update_client_minerva_adapter_app_someipprotocol_hdrs",
    ],
    strip_include_prefix = "sw_update_client_minerva_adapter_app_someipprotocol_hdrs/output/sw_update_client_minerva_adapter_app/includes",
)

cc_library(
    name = "sw_update_client_minerva_adapter_app_socal_srcs_lib",
    srcs = [
        ":sw_update_client_minerva_adapter_app_socal_srcs",
        ":sw_update_client_minerva_adapter_app_someipbinding_srcs",
        ":sw_update_client_minerva_adapter_app_someipprotocol_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    deps = [
        ":sw_update_client_minerva_adapter_app_modeldatatypes_hdrs_lib",
        ":sw_update_client_minerva_adapter_app_socal_hdrs_lib",
        ":sw_update_client_minerva_adapter_app_someipbinding_hdrs_lib",
        ":sw_update_client_minerva_adapter_app_someipprotocol_hdrs_lib",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_comcommon",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_headers",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_someipbinding",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_vajson",
    ],
)
