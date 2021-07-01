load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@rules_foreign_cc//foreign_cc:configure.bzl", "configure_make")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "logging_config",
    srcs = ["configs/logging_config.json"],
)

filegroup(
    name = "com_application",
    srcs = ["configs/com_application.json"],
)

filegroup(
    name = "app_arxml",
    srcs = [
        "//arxmls:x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        # Workaround to overcome the issue for the missing reference
        "//application/x6aa_config_manager:app_arxml",
    ],
)

minerva_aa_codegen_rule(
    name = "x6aa_resource_monitor_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_DLT_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
    ],
    outs_list_dict = {
        "x6aa_resource_monitor_applicationbase_init_deinit_srcs": [
            "X6AA_Ressource_Executable/src/ara/core/initialization.cpp",
        ],
    },
)

filegroup(
    name = "collectd_extended_sources",
    srcs = [
        "@collectd_mbient//:all_files",
    ],
)

cc_library(
    name = "extended_libs",
    srcs = [
        ":x6aa_resource_monitor_applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    deps = [
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
    ],
)

configure_make(
    name = "build_collectd",
    autogen = True,
    autogen_command = "build.sh",
    configure_command = "configure",
    configure_env_vars = {
        "CXXFLAGS": "-std=c++14",
    },
    configure_in_place = True,
    configure_options =
        select({
            "//:aarch64": [
                "--host aarch64-ubuntu-linux-gnu",
            ],
            "//:k8": [
                "--host x86_64-ubuntu-linux-gnu",
            ],
        }) + [
            "--disable-all-plugins",
            "--with-fp-layout=nothing",
            "--disable-werror",
            "--without-java",
            "--enable-memory",
            "--enable-cpu",
            "--enable-csv",
            "--enable-write_dlt",
        ],
    lib_source = ":collectd_extended_sources",
    out_bin_dir = "sbin",
    out_binaries = [
        "collectd",
        "collectdmon",
    ],
    out_shared_libs = [
        "libcollectdclient.so",
        "libcollectdclient.so.1",
        "libcollectdclient.so.1.1.0",
        "collectd/memory.so",
        "collectd/cpu.so",
        "collectd/csv.so",
        "collectd/write_dlt.so",
    ],
    deps = [
        ":extended_libs",
        "//bsw:amsr_vector_fs_applicationbase",
        "//bsw:amsr_vector_fs_characterconversion",
        "//bsw:amsr_vector_fs_libiostream",
        "//bsw:amsr_vector_fs_libosabstraction",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_thread",
        "//bsw:amsr_vector_fs_vajson",
    ],
)

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = [
        ":app_arxml",
    ],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = [
        "X6AA_DLT_Executable.*",
        "X6AA_Cnfg_Mngr_Executable.*",
        "X6AA_Dummy_SWC_1_Executable.*",
        "X6AA_Dummy_SWC_2_Executable.*",
        "SelfDiagnosticAgent_Executable.*",
        "TransmissionManager_ROVExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
    ],
    outs_list_dict = {
        "generated_exec_config": [
            "X6AA_Ressource_Executable/configuration/exec_config.json",
        ],
    },
)

genrule(
    name = "patched_exec_config",
    srcs = [":generated_exec_config"],
    outs = ["patched_exec_config.json"],
    cmd = """
        sed -E -e's#\"isAdaptiveApplication\" : 1,#\"isAdaptiveApplication\" : 0,#'# \
            -e's#\"-c\",#\"-f\",\\n\"-C\",#'# \
            -e's#./etc/application.json#/opt/X6AA_Ressource_Executable/etc/collectd.conf#' \
            $(location :generated_exec_config) > $@
    """,
)

filegroup(
    name = "collectd_config",
    srcs = [
        "collectd.conf",
    ],
)

filegroup(
    name = "collectd_types",
    srcs = [
        "types.db.mbient",
    ],
)

filegroup(
    name = "collectd_sbin_collectd",
    srcs = [
        ":build_collectd",
    ],
    output_group = "collectd",
)

filegroup(
    name = "collectd_sbin_collectdmon",
    srcs = [
        ":build_collectd",
    ],
    output_group = "collectdmon",
)

filegroup(
    name = "collectd_lib_libcollectdclient_so",
    srcs = [
        ":build_collectd",
    ],
    output_group = "libcollectdclient.so",
)

filegroup(
    name = "collectd_lib_libcollectdclient_so_1",
    srcs = [
        ":build_collectd",
    ],
    output_group = "libcollectdclient.so.1",
)

filegroup(
    name = "collectd_lib_libcollectdclient_so_1_1_0",
    srcs = [
        ":build_collectd",
    ],
    output_group = "libcollectdclient.so.1.1.0",
)

filegroup(
    name = "collectd_lib_collectd_memory_so",
    srcs = [
        ":build_collectd",
    ],
    output_group = "memory.so",
)

filegroup(
    name = "collectd_lib_collectd_cpu_so",
    srcs = [
        ":build_collectd",
    ],
    output_group = "cpu.so",
)

filegroup(
    name = "collectd_lib_collectd_csv_so",
    srcs = [
        ":build_collectd",
    ],
    output_group = "csv.so",
)

filegroup(
    name = "collectd_lib_collectd_write_dlt_so",
    srcs = [
        ":build_collectd",
    ],
    output_group = "write_dlt.so",
)

filegroup(
    name = "collectd_logs_collectd_pid",
    srcs = [
        "collectd.pid",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":patched_exec_config": "etc/exec_config.json",
        ":collectd_config": "etc/collectd.conf",
        ":collectd_types": "etc/types.db.mbient",
        ":collectd_logs_collectd_pid": "logs/collectd.pid",
        ":collectd_sbin_collectd": "bin/X6AA_Ressource_Executable",
        ":collectd_sbin_collectdmon": "bin/collectdmon",
        ":collectd_lib_libcollectdclient_so": "lib/libcollectdclient.so",
        ":collectd_lib_libcollectdclient_so_1": "lib/libcollectdclient.so.1",
        ":collectd_lib_libcollectdclient_so_1_1_0": "lib/libcollectdclient.so.1.1.0",
        ":collectd_lib_collectd_memory_so": "lib/collectd/memory.so",
        ":collectd_lib_collectd_cpu_so": "lib/collectd/cpu.so",
        ":collectd_lib_collectd_csv_so": "lib/collectd/csv.so",
        ":collectd_lib_collectd_write_dlt_so": "lib/collectd/write_dlt.so",
        ":logging_config": "etc/logging_config.json",
    },
    mode = "0755",
    package_dir = "/opt/X6AA_Ressource_Executable",
)
