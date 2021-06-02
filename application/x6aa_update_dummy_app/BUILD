load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "app_arxml",
    srcs = [
        "arxml/app.arxml",
        "arxml/states.arxml",
    ],
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    outs_list_dict = {
        "app_v1_applicationbase_init_deinit_srcs": [
            "x6aa_update_dummy_v1_app/src/ara/core/initialization.cpp",
        ],
        "app_v2_applicationbase_init_deinit_srcs": [
            "x6aa_update_dummy_v2_app/src/ara/core/initialization.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    outs_list_dict = {
        "app_v1_exec_config": [
            "x6aa_update_dummy_v1_app/configuration/exec_config.json",
        ],
        "app_v2_exec_config": [
            "x6aa_update_dummy_v2_app/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
    outs_list_dict = {
        "app_v1_updatemanager_swcluster_meta": [
            "x6aa_update_dummy_v1_app/swcl_package_metadata.json",
        ],
        "app_v2_updatemanager_swcluster_meta": [
            "x6aa_update_dummy_v2_app/swcl_package_metadata.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_daemon_gen_rule",
    arxml_srcs = [
        ":app_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
    ],
    outs_list_dict = {
        "app_v1_updatemanager_swcl_db": [
            "x6aa_update_dummy_v1_app/etc/swcl_db.json",
        ],
        "app_v2_updatemanager_swcl_db": [
            "x6aa_update_dummy_v2_app/etc/swcl_db.json",
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
    name = "app_v1",
    srcs = [
        ":app_v1_applicationbase_init_deinit_srcs",
        "src/application_v1.cpp",
        "src/application.h",
        "src/main.cpp",
        "src/update_app_demo_error_domain.cpp",
        "src/update_app_demo_error_domain.h",
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

cc_binary(
    name = "app_v2",
    srcs = [
        ":app_v1_applicationbase_init_deinit_srcs",
        "src/application_v2.cpp",
        "src/application.h",
        "src/main.cpp",
        "src/update_app_demo_error_domain.cpp",
        "src/update_app_demo_error_domain.h",
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

pkg_tar(
    name = "package_v1",
    files = {
        ":app_v1": "bin/x6aa_update_dummy_v1_app",
        ":app_v1_exec_config": "etc/exec_config.json",
        ":app_v1_updatemanager_swcl_db": "etc/swcl_db.json",
        ":app_v1_updatemanager_swcluster_meta": "etc/swcl_package_metadata.json",
        ":logging_config": "etc/logging_config.json",
    },
    mode = "0755",
    package_dir = "opt/x6aa_update_dummy_v1_app",
)

pkg_tar(
    name = "package_v2",
    files = {
        ":app_v2": "bin/x6aa_update_dummy_v2_app",
        ":app_v2_exec_config": "etc/exec_config.json",
        ":app_v2_updatemanager_swcl_db": "etc/swcl_db.json",
        ":app_v2_updatemanager_swcluster_meta": "etc/swcl_package_metadata.json",
        ":logging_config": "etc/logging_config.json",
    },
    mode = "0755",
    package_dir = "opt/x6aa_update_dummy_v2_app",
)

alias(
    name = "package",
    actual = ":package_v1",
)
