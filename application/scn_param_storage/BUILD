load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "arxml/scn_param_storage.arxml",
        "@starter_kit_adaptive_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:ncd_arxml",
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
        "@starter_kit_adaptive_xavier//:generator_amsr_em_exec_config",
        "@starter_kit_adaptive_xavier//:generator_amsr_applicationbase_init_deinit",
        "@starter_kit_adaptive_xavier//:generator_amsr_socal",
        "@starter_kit_adaptive_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = [
        "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable.*",
        "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable.*",
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
        "main.cpp",
        "scn_param_storage_error_domain.h",

        # This a workaround to resolve cyclic dependency. This is the reason why the target scn_param_storage
        # build in 2 steps.
        # The code generators depend on libSocal.a, contained in the @minerva_mpu_adaptive//:socal_lib_for_scn_param_storage below.
        # That is why we put it in sources. It is important that this `:socal_lib_for_scn_param_storage` is positioned earlier in
        # the list than the generated sources in `:scn_param_storage_socal_srcs_lib` and
        # `:scn_param_storage_applicationbase_init_deinit_srcs`
        #"@minerva_mpu_adaptive//:socal_lib_for_scn_param_storage",
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
