load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "arxml/states.arxml",
        "arxml/avatar_router.arxml",
        "@amsr_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:standard_types_arxml",
    ],
)

filegroup(
    name = "logging_config_json",
    srcs = ["configs/logging_config.json"],
)

filegroup(
    name = "com_application_json",
    srcs = ["configs/com_application.json"],
)

minerva_aa_codegen_rule(
    name = "avatar_router_gen_rule",
    arxml_srcs = [":app_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    outs_list_dict = {
        "exec_config": [
            "avatar_router/configuration/exec_config.json",
        ],
        "applicationbase_init_deinit_srcs": [
            "avatar_router/src/ara/core/initialization.cpp",
        ],
    },
)

cc_binary(
    name = "app",
    srcs = [
        "main.cpp",
        "avatar_router_error_domain.h",
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
        ":exec_config": "etc/exec_config.json",
        ":logging_config_json": "etc/logging_config.json",
        ":com_application_json": "etc/com_application.json",
        ":app": "bin/avatar_router"
    },
    mode = "0755",
    package_dir = "opt/avatar_router",
)
