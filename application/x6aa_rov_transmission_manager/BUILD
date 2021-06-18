load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        # Workaround to overcome the issue for the missing reference for
        # /design/IF_Persistency_KVS from the x6aa_config_manager,
        "//application/x6aa_config_manager:app_arxml",
    ],
)

filegroup(
    name = "logging_config",
    srcs = [
        "config/logging_config.json",
    ],
)

filegroup(
    name = "com_application",
    srcs = [
        "config/com_application.json",
    ],
)

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "TransmissionManager_ROVExecutable/configuration/exec_config.json",
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
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "rov_init_deinit_srcs": [
            "TransmissionManager_ROVExecutable/src/ara/core/initialization.cpp",
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
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "swcluster_meta": [
            "TransmissionManager_ROVExecutable/swcl_package_metadata.json",
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
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "swcl_db": [
            "TransmissionManager_ROVExecutable/etc/swcl_db.json",
        ],
        "updatemanager_daemon": [
            "TransmissionManager_ROVExecutable/etc/updatemanager.json",
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
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "modeldatatypes_hdrs": [
            "TransmissionManager_ROVExecutable/include/DataTypes/NS_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt/impl_type_rec_camsenssoil_mpc_st3_cp6wyrd9cg7ec7y2w3khz1gyt.h",
            "TransmissionManager_ROVExecutable/include/DataTypes/NS_VSLim_LimitConditions/impl_type_vslim_limitconditions.h",
            "TransmissionManager_ROVExecutable/include/DataTypes/STD_UUCategory/impl_type_std_uucategory.h",
            "TransmissionManager_ROVExecutable/include/DataTypes/VSLim_GetCapabilities_Out_b0ko81o0x5jgvwtduf99gvzi0/impl_type_vslim_getcapabilities_out_b0ko81o0x5jgvwtduf99gvzi0.h",
            "TransmissionManager_ROVExecutable/include/DataTypes/VSLim_RequestLimit_In/impl_type_vslim_requestlimit_in.h",
            "TransmissionManager_ROVExecutable/include/DataTypes/VSLim_SpeedLimiterState_71njeubj9ico1p8v4pmslfcno/impl_type_vslim_speedlimiterstate_71njeubj9ico1p8v4pmslfcno.h",
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
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "someip_binding_initializer": [
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/someip_binding_initializer.cpp",
        ],
        "someip_config": [
            "TransmissionManager_ROVExecutable/configuration/someip_config.json",
        ],
        "someipbinding_hdrs": [
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/DataTypes/NS_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt/serializer_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt_1.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_proxy_someip_binding.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_proxy_someip_binding_init.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_proxy_someip_event_manager.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_proxy_someip_methods.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_someip_proxy_factory.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_someip_binding.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_someip_binding_init.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_someip_event_manager.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_someip_methods.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_someip_skeleton_factory.h",
        ],
        "someipbinding_srcs": [
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/DataTypes/NS_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt/serializer_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt_1.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_proxy_someip_binding.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_proxy_someip_binding_init.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/services/ns_speedlimiter/SI_SpeedLimiter_proxy_someip_event_manager.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_someip_binding.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_someip_binding_init.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_binding_transformation_layer/internal/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_someip_event_manager.cpp",
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
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "someipprotocol_hdrs": [
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_speedlimiter/events/deserializer_Ev_Capabilities.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_speedlimiter/events/deserializer_Ev_SpeedLimiterState.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_speedlimiter/methods/deserializer_Meth_GetCapabilitiesOutParameters.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_speedlimiter/methods/serializer_Meth_RequestSpeedLimitInParameters.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_suppfunctions_mpc_service_st3/events/serializer_Ev_CamSensSoil_MPC_ST3.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/NS_VSLim_LimitConditions/deserializer_VSLim_LimitConditions.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/STD_UUCategory/deserializer_STD_UUCategory.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/VSLim_GetCapabilities_Out_b0ko81o0x5jgvwtduf99gvzi0/deserializer_VSLim_GetCapabilities_Out_b0ko81o0x5jgvwtduf99gvzi0.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/VSLim_SpeedLimiterState_71njeubj9ico1p8v4pmslfcno/deserializer_VSLim_SpeedLimiterState_71njeubj9ico1p8v4pmslfcno.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/NS_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt/serializer_REC_CamSensSoil_MPC_ST3_cp6wyrd9cg7ec7y2w3khz1gyt.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/STD_UUCategory/serializer_STD_UUCategory.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/datatype_serialization/DataTypes/VSLim_RequestLimit_In/serializer_VSLim_RequestLimit_In.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/method_deserialization/services_ns_speedlimiter/methods/deserializer_Response_Meth_GetCapabilities.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/method_deserialization/services_ns_speedlimiter/methods/deserializer_Response_Meth_RequestSpeedLimit.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/method_serialization/services_ns_speedlimiter/methods/serializer_Request_Meth_GetCapabilities.h",
            "TransmissionManager_ROVExecutable/include/amsr/someip_protocol/internal/method_serialization/services_ns_speedlimiter/methods/serializer_Request_Meth_RequestSpeedLimit.h",
        ],
        "someipprotocol_srcs": [
            "TransmissionManager_ROVExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_speedlimiter/events/deserializer_Ev_Capabilities.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_speedlimiter/events/deserializer_Ev_SpeedLimiterState.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_speedlimiter/methods/deserializer_Meth_GetCapabilitiesOutParameters.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_speedlimiter/methods/serializer_Meth_RequestSpeedLimitInParameters.cpp",
            "TransmissionManager_ROVExecutable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_suppfunctions_mpc_service_st3/events/serializer_Ev_CamSensSoil_MPC_ST3.cpp",
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
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgentExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "runtime_gen": [
            "TransmissionManager_ROVExecutable/src/ara/com/runtime_gen.cpp",
        ],
        "socal_hdrs": [
            "TransmissionManager_ROVExecutable/include/services/ns_speedlimiter/SI_SpeedLimiter.h",
            "TransmissionManager_ROVExecutable/include/services/ns_speedlimiter/SI_SpeedLimiter_proxy_internal.h",
            "TransmissionManager_ROVExecutable/include/services/ns_speedlimiter/SI_SpeedLimiter_proxy_update_manager.h",
            "TransmissionManager_ROVExecutable/include/services/ns_speedlimiter/SI_SpeedLimiter_types.h",
            "TransmissionManager_ROVExecutable/include/services/ns_speedlimiter/si_speedlimiter_common.h",
            "TransmissionManager_ROVExecutable/include/services/ns_speedlimiter/si_speedlimiter_proxy.h",
            "TransmissionManager_ROVExecutable/include/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3.h",
            "TransmissionManager_ROVExecutable/include/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_skeleton_impl_interface.h",
            "TransmissionManager_ROVExecutable/include/services/ns_suppfunctions_mpc_service_st3/SI_SuppFunctions_MPC_Service_ST3_types.h",
            "TransmissionManager_ROVExecutable/include/services/ns_suppfunctions_mpc_service_st3/si_suppfunctions_mpc_service_st3_common.h",
            "TransmissionManager_ROVExecutable/include/services/ns_suppfunctions_mpc_service_st3/si_suppfunctions_mpc_service_st3_skeleton.h",
        ],
        "socal_srcs": [
            "TransmissionManager_ROVExecutable/src/services/ns_speedlimiter/si_speedlimiter.cpp",
            "TransmissionManager_ROVExecutable/src/services/ns_speedlimiter/si_speedlimiter_proxy.cpp",
            "TransmissionManager_ROVExecutable/src/services/ns_suppfunctions_mpc_service_st3/si_suppfunctions_mpc_service_st3.cpp",
            "TransmissionManager_ROVExecutable/src/services/ns_suppfunctions_mpc_service_st3/si_suppfunctions_mpc_service_st3_skeleton.cpp",
        ],
    },
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/TransmissionManager_ROVExecutable/include",
)

cc_library(
    name = "modeldatatypes_hdrs_lib",
    hdrs = [
        ":modeldatatypes_hdrs",
    ],
    strip_include_prefix = "modeldatatypes_hdrs/output/TransmissionManager_ROVExecutable/include",
)

cc_library(
    name = "someipbinding_hdrs_lib",
    hdrs = [
        ":someipbinding_hdrs",
    ],
    strip_include_prefix = "someipbinding_hdrs/output/TransmissionManager_ROVExecutable/include",
)

cc_library(
    name = "someipprotocol_hdrs_lib",
    hdrs = [
        ":someipprotocol_hdrs",
    ],
    strip_include_prefix = "someipprotocol_hdrs/output/TransmissionManager_ROVExecutable/include",
)

cc_library(
    name = "socal_srcs_lib",
    srcs = [
        ":runtime_gen",
        ":socal_srcs",
        ":someipbinding_srcs",
        ":someipprotocol_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    deps = [
        ":modeldatatypes_hdrs_lib",
        ":socal_hdrs_lib",
        ":someipbinding_hdrs_lib",
        ":someipprotocol_hdrs_lib",
        "//bsw:amsr_vector_fs_ipcbinding",
        "//bsw:amsr_vector_fs_someipbinding",
        "//bsw:amsr_vector_fs_vajson",
    ],
)

cc_binary(
    name = "app",
    srcs = [
        "src/main.cpp",
        "src/rov_application.cpp",
        "src/rov_application.h",
        ":rov_init_deinit_srcs",
        ":someip_binding_initializer",
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
        ":socal_srcs_lib",
        "//application/common:application_base",
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libiostream",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_socal",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/TransmissionManager_ROVExecutable",
        ":exec_config": "etc/exec_config.json",
        ":com_application": "etc/com_application.json",
        ":logging_config": "etc/logging_config.json",
        ":swcl_db": "etc/swcl_db.json",
        ":swcluster_meta": "etc/swcl_package_metadata.json",
        ":someip_config": "etc/someip_config.json",
        ":updatemanager_daemon": "etc/updatemanager.json",
    },
    mode = "0755",
    package_dir = "opt/TransmissionManager_ROVExecutable",
)
