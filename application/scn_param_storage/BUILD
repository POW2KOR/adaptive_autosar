load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "model/arxml/deployment/deployment.arxml",
        "model/arxml/design/executable.arxml",
        "model/arxml/machine/states.arxml",
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
    name = "scn_param_storage_gen_rule",
    arxml_srcs = [":app_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    outs_list_dict = {
        "scn_param_storage_exec_config": [
            "scn_param_storage/configuration/exec_config.json",
        ],
        "scn_param_storage_applicationbase_init_deinit_srcs": [
            "scn_param_storage/src/ara/core/initialization.cpp",
        ],
    },
)

cc_binary(
    name = "scn_param_storage",
    srcs = [
        "src/main.cpp",
        "src/scn_param_storage_error_domain.h",
        ":scn_param_storage_applicationbase_init_deinit_srcs",
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
