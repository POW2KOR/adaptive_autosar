load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "TestBaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "update_app_demo_idc6.*",
    ],
    outs_list_dict = {
        "applicationbase_init_deinit_srcs": [
            "shutdown_app_demo_idc6/src/ara/core/initialization.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "TestBaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "update_app_demo_idc6.*",
        "amsr_vector_fs_sec_cryptostack_daemon.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "shutdown_app_demo_idc6/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "TestBaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "update_app_demo_idc6.*",
        "amsr_vector_fs_sec_cryptostack_daemon.*",
    ],
    outs_list_dict = {
        "updatemanager_swcluster_meta": [
            "shutdown_app_demo_idc6/swcl_package_metadata.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_daemon_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "TestBaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "update_app_demo_idc6.*",
        "amsr_vector_fs_sec_cryptostack_daemon.*",
    ],
    outs_list_dict = {
        "updatemanager_daemon": [
            "shutdown_app_demo_idc6/etc/updatemanager.json",
        ],
        "updatemanager_swcl_db_daemon": [
            "shutdown_app_demo_idc6/etc/swcl_db.json",
        ],
    },
)

filegroup(
    name = "logging_config",
    srcs = [
        "config/logging_config.json",
    ],
)

cc_binary(
    name = "app",
    srcs = [
        ":applicationbase_init_deinit_srcs",
        "@starter_kit_adaptive_xavier//:shutdown_app_demo_idc6_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    deps = [
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
    ],
)
