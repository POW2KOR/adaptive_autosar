load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "amsr_vector_fs_log_daemon_arxml",
    srcs = [
        "arxml/logdaemon.arxml",
    ],
)

minerva_aa_codegen_rule(
    name = "minerva_amsr_fs_log_daemon_config_gen_rule",
    arxml_srcs = [
        "//application:complete_arxml",
        ":amsr_vector_fs_log_daemon_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_logdaemon_config",
        "@amsr_xavier//:generator_amsr_logapi_config",
    ],
    outs_list_dict = {
        "logd_config": [
            "amsr_vector_fs_log_daemon/etc/logd_config.json",
        ],
        "logging_config": [
            "amsr_vector_fs_log_daemon/etc/logging_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        "//application:complete_arxml",
        ":amsr_vector_fs_log_daemon_arxml",
    ],
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
        "shutdown_app_demo_idc6.*",
        "update_app_demo_idc6.*",
        "restart_app_demo_idc6.*",
        "amsr_vector_fs_sec_cryptostack_daemon.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "amsr_vector_fs_log_daemon/configuration/exec_config.json",
        ],
    },
)
