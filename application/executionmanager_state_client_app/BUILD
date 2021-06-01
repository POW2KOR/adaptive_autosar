load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = ["arxml/executionmanager_state_client_app.arxml"],
)

minerva_aa_codegen_rule(
    name = "executionmanager_state_client_app_gen_rule",
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
        "executionmanager_state_client_app.*exec_config.*",
    ],
    outs_list_dict = {
        "updatemanager_daemon_db": [
            "executionmanager_state_client_app/etc/swcl_db.json",
        ],
        "updatemanager_swcluser_meta": [
            "executionmanager_state_client_app/swcl_package_metadata.json",
        ],
        "applicationbase_init_deinit_srcs": [
            "executionmanager_state_client_app/src/ara/core/initialization.cpp",
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

cc_binary(
    name = "app",
    srcs = [
        ":applicationbase_init_deinit_srcs",
        "@amsr_xavier//:amsr_vector_fs_em_executionmanager_addon_demo_application_srcs",
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
