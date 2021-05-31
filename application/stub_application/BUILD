load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "arxml/states.arxml",
        "arxml/stub_application.arxml",
        "@amsr_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:standard_types_arxml",
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
    name = "stub_application_gen_rule",
    arxml_srcs = [":app_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    outs_list_dict = {
        "exec_config": [
            "stub_application/configuration/exec_config.json",
        ],
        "applicationbase_init_deinit_srcs": [
            "stub_application/src/ara/core/initialization.cpp",
        ],
    },
)

cc_binary(
    name = "stub_application",
    srcs = [
        "main.cpp",
        "stub_application_error_domain.h",
        ":applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    deps = [
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_vajson",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":stub_application": "bin/stub_application",
        ":exec_config": "etc/exec_config.json",
        ":com_application": "etc/com_application.json",
        ":logging_config": "etc/logging_config.json",
    },
    mode = "0755",
    package_dir = "opt/stub_application",
)
