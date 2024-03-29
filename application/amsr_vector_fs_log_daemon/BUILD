load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "amsr_vector_fs_log_daemon_arxml",
    srcs = [
        "arxml/logdaemon.arxml",
    ],
)

minerva_aa_codegen_rule(
    name = "log_daemon_config_gen_rule",
    arxml_srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        ":amsr_vector_fs_log_daemon_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_logdaemon_config",
        "@amsr_xavier//:generator_amsr_logapi_config",
    ],
    outs_list_dict = {
        "logging_config": [
            "amsr_vector_fs_log_daemon/etc/logging_config.json",
        ],
        "logd_config": [
            "amsr_vector_fs_log_daemon/etc/logd_config.json",
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
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "X6AA_Ressource_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "amsr_vector_fs_log_daemon/configuration/exec_config.json",
        ],
    },
)

# This filegroup is necessary so that we isolate the output group corresponding
# to the binary of the cmake_external. Otherwise, it adds a lot of noise and
# annoying stuff. Maybe we can find a better way in the future.
# To list the output groups, I used this method:
# https://stackoverflow.com/a/61282031
# More information here:
# - https://docs.bazel.build/versions/master/skylark/rules.html#requesting-output-files
# - https://github.com/bazelbuild/rules_foreign_cc/blob/d54c78ab86b40770ee19f0949db9d74a831ab9f0/tools/build_defs/framework.bzl#L400

filegroup(
    name = "app",
    srcs = ["//bsw:amsr_vector_fs_log_daemon"],
    output_group = "amsr_vector_fs_log_daemon",
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/amsr_vector_fs_log_daemon",
        ":logd_config": "etc/logd_config.json",
        ":logging_config": "etc/logging_config.json",
        ":exec_config": "etc/exec_config.json",
    },
    mode = "0755",
    package_dir = "opt/amsr_vector_fs_log_daemon",
)
