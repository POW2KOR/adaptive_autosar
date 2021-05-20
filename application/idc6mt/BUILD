load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "arxml/idc6mt.arxml",
        "arxml/states.arxml",
        "@starter_kit_adaptive_xavier//:mex_arxml",
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
    name = "idc6mt_gen_rule",
    arxml_srcs = [":app_arxml"],
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_em_exec_config",
        "@starter_kit_adaptive_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    outs_list_dict = {
        "idc6mt_exec_config": [
            "idc6mt/configuration/exec_config.json",
        ],
        "idc6mt_applicationbase_init_deinit_srcs": [
            "idc6mt/src/ara/core/initialization.cpp",
        ],
    },
)

cc_binary(
    name = "idc6mt",
    srcs = [
        "idc6mt_error_domain.h",
        "main.cpp",
        ":idc6mt_applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    deps = [
        "//application/idc6mt/accessor:mt_memory_accessor",
        "//application/idc6mt/mtd:mt_logic",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_vajson",
    ],
)
