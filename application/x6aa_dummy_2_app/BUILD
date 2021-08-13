load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
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
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "TransmissionManager_ROVExecutable.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "X6AA_Dummy_SWC_2_Executable/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        # Workaround to overcome the issue for the missing reference for
        # /design/IF_Persistency_KVS from the x6aa_config_manager,
        "//application/x6aa_config_manager:app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "TransmissionManager_ROVExecutable.*",
    ],
    outs_list_dict = {
        "init_deinit_srcs": [
            "X6AA_Dummy_SWC_2_Executable/src/ara/core/initialization.cpp",
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
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "TransmissionManager_ROVExecutable.*",
    ],
    outs_list_dict = {
        "swcluster_meta": [
            "X6AA_Dummy_SWC_2_Executable/swcl_package_metadata.json",
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
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "TransmissionManager_ROVExecutable.*",
    ],
    outs_list_dict = {
        "swcl_db": [
            "X6AA_Dummy_SWC_2_Executable/etc/swcl_db.json",
        ],
        "updatemanager_daemon": [
            "X6AA_Dummy_SWC_2_Executable/etc/updatemanager.json",
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
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "TransmissionManager_ROVExecutable.*",
    ],
    outs_list_dict = {
        "someip_binding_initializer": [
            "X6AA_Dummy_SWC_2_Executable/src/amsr/someip_binding_transformation_layer/internal/someip_binding_initializer.cpp",
        ],
        "someip_config": [
            "X6AA_Dummy_SWC_2_Executable/configuration/someip_config.json",
        ],
        "someipbinding_hdrs": [
            "X6AA_Dummy_SWC_2_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_someip_binding.h",
            "X6AA_Dummy_SWC_2_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_someip_binding_init.h",
            "X6AA_Dummy_SWC_2_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_someip_event_manager.h",
            "X6AA_Dummy_SWC_2_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_someip_methods.h",
            "X6AA_Dummy_SWC_2_Executable/include/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_someip_skeleton_factory.h",
        ],
        "someipbinding_srcs": [
            "X6AA_Dummy_SWC_2_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_someip_binding.cpp",
            "X6AA_Dummy_SWC_2_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_someip_binding_init.cpp",
            "X6AA_Dummy_SWC_2_Executable/src/amsr/someip_binding_transformation_layer/internal/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_someip_event_manager.cpp",
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
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "TransmissionManager_ROVExecutable.*",
    ],
    outs_list_dict = {
        "someipprotocol_hdrs": [
            "X6AA_Dummy_SWC_2_Executable/include/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_dummyswc_2_to_cnfg_mngr/events/serializer_Ev_CalculationResult.h",
        ],
        "someipprotocol_srcs": [
            "X6AA_Dummy_SWC_2_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/services_ns_si_dummyswc_2_to_cnfg_mngr/events/serializer_Ev_CalculationResult.cpp",
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
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "TransmissionManager_ROVExecutable.*",
    ],
    outs_list_dict = {
        "runtime_gen": [
            "X6AA_Dummy_SWC_2_Executable/src/ara/com/runtime_gen.cpp",
        ],
        "socal_hdrs": [
            "X6AA_Dummy_SWC_2_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved.h",
            "X6AA_Dummy_SWC_2_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_skeleton_impl_interface.h",
            "X6AA_Dummy_SWC_2_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/SI_X6AA_Dummy_B2_Service_Reserved_types.h",
            "X6AA_Dummy_SWC_2_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_common.h",
            "X6AA_Dummy_SWC_2_Executable/include/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_skeleton.h",
        ],
        "socal_srcs": [
            "X6AA_Dummy_SWC_2_Executable/src/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved.cpp",
            "X6AA_Dummy_SWC_2_Executable/src/services/ns_si_dummyswc_2_to_cnfg_mngr/si_x6aa_dummy_b2_service_reserved_skeleton.cpp",
        ],
    },
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/X6AA_Dummy_SWC_2_Executable/include",
)

cc_library(
    name = "someipbinding_hdrs_lib",
    hdrs = [
        ":someipbinding_hdrs",
    ],
    strip_include_prefix = "someipbinding_hdrs/output/X6AA_Dummy_SWC_2_Executable/include",
)

cc_library(
    name = "someipprotocol_hdrs_lib",
    hdrs = [
        ":someipprotocol_hdrs",
    ],
    strip_include_prefix = "someipprotocol_hdrs/output/X6AA_Dummy_SWC_2_Executable/include",
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
        "src/dummy_ssa_server.cpp",
        "src/dummy_ssa_server.h",
        "src/main.cpp",
        ":init_deinit_srcs",
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
        ":app": "bin/X6AA_Dummy_SWC_2_Executable",
        ":exec_config": "etc/exec_config.json",
        ":com_application": "etc/com_application.json",
        ":logging_config": "etc/logging_config.json",
        ":swcl_db": "etc/swcl_db.json",
        ":swcluster_meta": "etc/swcl_package_metadata.json",
        ":someip_config": "etc/someip_config.json",
        ":updatemanager_daemon": "etc/updatemanager.json",
    },
    mode = "0755",
    package_dir = "opt/X6AA_Dummy_SWC_2_Executable",
)
