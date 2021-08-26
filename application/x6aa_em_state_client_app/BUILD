load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = ["arxml/app.arxml"],
)

minerva_aa_codegen_rule(
    name = "app_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
        "@amsr_xavier//:generator_amsr_em_exec_config",
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        # We're not using this exec_config because the code generator isn't
        # able to generate a proper config file when category PLATFORM_LEVEL
        # is selected. So instead, config/exec_config.json gets used.
        "x6aa_em_state_client_app.*exec_config.*",
    ],
    outs_list_dict = {
        "updatemanager_swcl_db": [
            "x6aa_em_state_client_app/etc/swcl_db.json",
        ],
        "updatemanager_swcluser_meta": [
            "x6aa_em_state_client_app/swcl_package_metadata.json",
        ],
        "applicationbase_init_deinit_srcs": [
            "x6aa_em_state_client_app/src/ara/core/initialization.cpp",
        ],
    },
)

filegroup(
    name = "exec_config",
    srcs = [
        "config/exec_config.json",
    ],
)

filegroup(
    name = "logging_config",
    srcs = [
        "config/logging_config.json",
    ],
)

filegroup(
    name = "srcs",
    srcs = glob(["src/**"]),
)

cc_binary(
    name = "app",
    srcs = [
        ":applicationbase_init_deinit_srcs",
        ":srcs",
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
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libiostream",
        "//bsw:amsr_vector_fs_log_api",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/x6aa_em_state_client_app",
        ":logging_config": "etc/logging_config.json",
        ":exec_config": "etc/exec_config.json",
        ":updatemanager_swcl_db": "etc/swcl_db.json",
        ":updatemanager_swcluser_meta": "etc/swcl_package_metadata.json",
    },
    mode = "0755",
    package_dir = "opt/x6aa_em_state_client_app",
)
