load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

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
    srcs = ["configs/logging_config.json"],
)

filegroup(
    name = "com_application",
    srcs = ["configs/com_application.json"],
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
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "X6AA_Dummy_SWC_1_Executable/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        # The generator seems unable to generate the required files without
        # the symbols /design/IF_Persistency_KVS from the x6aa_config_manager,
        # even though they are not required for x6aa_dummy_swc_1.
        # We will pursue this with Vector
        "//application/x6aa_config_manager:app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "applicationbase_init_deinit_srcs": [
            "X6AA_Dummy_SWC_1_Executable/src/ara/core/initialization.cpp",
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
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "swcluster_meta": [
            "X6AA_Dummy_SWC_1_Executable/swcl_package_metadata.json",
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
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "swcl_db": [
            "X6AA_Dummy_SWC_1_Executable/etc/swcl_db.json",
        ],
        "updatemanager_daemon": [
            "X6AA_Dummy_SWC_1_Executable/etc/updatemanager.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "modeldatatypes_api_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        # The generator seems unable to generate the required files without
        # the symbols /design/IF_Persistency_KVS from the x6aa_config_manager,
        # even though they are not required for x6aa_dummy_swc_1.
        # We will pursue this with Vector
        "//application/x6aa_config_manager:app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "modeldatatypes_hdrs": [
            "X6AA_Dummy_SWC_1_Executable/include/DataTypes/NS_REC_vechicleInformation0400VcEventType_t/impl_type_rec_vechicleinformation0400vceventtype_t.h",
            "X6AA_Dummy_SWC_1_Executable/include/DataTypes/NS_REC_configureSarTriggerEvents0136VcEventType_t/impl_type_rec_configuresartriggerevents0136vceventtype_t.h",
            "X6AA_Dummy_SWC_1_Executable/include/DataTypes/NS_REC_activateSarStorage0131VcEventType_t/impl_type_rec_activatesarstorage0131vceventtype_t.h",
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
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "someipprotocol_hdrs": [
            "X6AA_Dummy_SWC_1_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/NS_REC_vechicleInformation0400VcEventType_t/deserializer_REC_vechicleInformation0400VcEventType_t.h",
            "X6AA_Dummy_SWC_1_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/NS_REC_configureSarTriggerEvents0136VcEventType_t/deserializer_REC_configureSarTriggerEvents0136VcEventType_t.h",
            "X6AA_Dummy_SWC_1_Executable/include/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/NS_REC_activateSarStorage0131VcEventType_t/deserializer_REC_activateSarStorage0131VcEventType_t.h",
            "X6AA_Dummy_SWC_1_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_cnfg_mngr_to_dummyswc/events/deserializer_Ev_activateSarStorage0131VcEvent.h",
            "X6AA_Dummy_SWC_1_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_cnfg_mngr_to_dummyswc/events/deserializer_Ev_configureSarTriggerEvents0136VcEvent.h",
            "X6AA_Dummy_SWC_1_Executable/include/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_cnfg_mngr_to_dummyswc/events/deserializer_Ev_vechicleInformation0400VcEvent.h",
        ],
        "someipprotocol_srcs": [
            "X6AA_Dummy_SWC_1_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_cnfg_mngr_to_dummyswc/events/deserializer_Ev_configureSarTriggerEvents0136VcEvent.cpp",
            "X6AA_Dummy_SWC_1_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_cnfg_mngr_to_dummyswc/events/deserializer_Ev_activateSarStorage0131VcEvent.cpp",
            "X6AA_Dummy_SWC_1_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/services_ns_si_cnfg_mngr_to_dummyswc/events/deserializer_Ev_vechicleInformation0400VcEvent.cpp",
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
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "runtime_gen": [
            "X6AA_Dummy_SWC_1_Executable/src/ara/com/runtime_gen.cpp",
        ],
        "socal_hdrs": [
            "X6AA_Dummy_SWC_1_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_types.h",
            "X6AA_Dummy_SWC_1_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_update_manager.h",
            "X6AA_Dummy_SWC_1_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_proxy.h",
            "X6AA_Dummy_SWC_1_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_common.h",
            "X6AA_Dummy_SWC_1_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved.h",
            "X6AA_Dummy_SWC_1_Executable/include/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_internal.h",
        ],
        "socal_srcs": [
            "X6AA_Dummy_SWC_1_Executable/src/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved.cpp",
            "X6AA_Dummy_SWC_1_Executable/src/services/ns_si_cnfg_mngr_to_dummyswc/si_x6aa_cnfg_mngr_service_reserved_proxy.cpp",
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
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "ipc_binding_life_cycle_manager": [
            "X6AA_Dummy_SWC_1_Executable/src/amsr/ipc_binding_transformation_layer/internal/ipc_binding_life_cycle_manager.cpp",
        ],
        "ipcbinding_hdrs": [
            "X6AA_Dummy_SWC_1_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_ipc_methods.h",
            "X6AA_Dummy_SWC_1_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_ipc_event_manager.h",
            "X6AA_Dummy_SWC_1_Executable/include/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_ipc_binding.h",
        ],
        "ipcbinding_srcs": [
            "X6AA_Dummy_SWC_1_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_ipc_methods.cpp",
            "X6AA_Dummy_SWC_1_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_ipc_binding.cpp",
            "X6AA_Dummy_SWC_1_Executable/src/amsr/ipc_binding_transformation_layer/internal/services/ns_si_cnfg_mngr_to_dummyswc/SI_X6AA_Cnfg_Mngr_Service_Reserved_proxy_ipc_event_manager.cpp",
        ],
    },
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/X6AA_Dummy_SWC_1_Executable/include",
)

cc_library(
    name = "modeldatatypes_hdrs_lib",
    hdrs = [
        ":modeldatatypes_hdrs",
    ],
    strip_include_prefix = "modeldatatypes_hdrs/output/X6AA_Dummy_SWC_1_Executable/include",
)

cc_library(
    name = "ipcbinding_hdrs_lib",
    hdrs = [
        ":ipcbinding_hdrs",
    ],
    strip_include_prefix = "ipcbinding_hdrs/output/X6AA_Dummy_SWC_1_Executable/include",
)

cc_library(
    name = "someipprotocol_hdrs_lib",
    hdrs = [
        ":someipprotocol_hdrs",
    ],
    strip_include_prefix = "someipprotocol_hdrs/output/X6AA_Dummy_SWC_1_Executable/include",
)

cc_library(
    name = "socal_srcs_lib",
    srcs = [
        ":ipcbinding_srcs",
        ":runtime_gen",
        ":socal_srcs",
        ":someipprotocol_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    deps = [
        ":ipcbinding_hdrs_lib",
        ":modeldatatypes_hdrs_lib",
        ":socal_hdrs_lib",
        ":someipprotocol_hdrs_lib",
        "//bsw:amsr_vector_fs_ipcbinding",
        "//bsw:amsr_vector_fs_someipbinding",
        "//bsw:amsr_vector_fs_vajson",
    ],
)

cc_binary(
    name = "app",
    srcs = [
        "src/dummy_swc1_application.cpp",
        "src/dummy_swc1_application.h",
        "src/main.cpp",
        "src/variant_coding_consumer.cpp",
        "src/variant_coding_consumer.h",
        ":applicationbase_init_deinit_srcs",
        ":ipc_binding_life_cycle_manager",
        "//bsw:amsr_vector_fs_socal_libsocal_a",
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
        ":socal_srcs_lib",
        "//application/common:application_base",
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libiostream",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_socal",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/X6AA_Dummy_SWC_1_Executable",
        ":logging_config": "etc/logging_config.json",
        ":com_application": "etc/com_application.json",
        ":exec_config": "etc/exec_config.json",
        ":swcl_db": "etc/swcl_db.json",
        ":swcluster_meta": "etc/swcl_package_metadata.json",
        ":updatemanager_daemon": "etc/updatemanager.json",
    },
    mode = "0755",
    package_dir = "opt/X6AA_Dummy_SWC_1_Executable",
)
