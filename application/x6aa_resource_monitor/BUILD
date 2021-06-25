load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])

configure_make(
    name = "build_collectd",
    autogen = True,
    autogen_command = "build.sh",
    configure_command = "configure",
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
        ],
    lib_source = "@collectd_mbient//:all_files",
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
    ],
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
    name = "collectd_logs_collectd_pid",
    srcs = [
        "collectd.pid",
    ],
)

pkg_tar(
    name = "package",
    files = {
        ":collectd_config": "etc/collectd.conf",
        ":collectd_types": "etc/types.db.mbient",
        ":collectd_logs_collectd_pid": "logs/collectd.pid",
        ":collectd_sbin_collectd": "sbin/collectd",
        ":collectd_sbin_collectdmon": "sbin/collectdmon",
        ":collectd_lib_libcollectdclient_so": "lib/libcollectdclient.so",
        ":collectd_lib_libcollectdclient_so_1": "lib/libcollectdclient.so.1",
        ":collectd_lib_libcollectdclient_so_1_1_0": "lib/libcollectdclient.so.1.1.0",
        ":collectd_lib_collectd_memory_so": "lib/collectd/memory.so",
        ":collectd_lib_collectd_cpu_so": "lib/collectd/cpu.so",
        ":collectd_lib_collectd_csv_so": "lib/collectd/csv.so",
    },
    mode = "0755",
    package_dir = "/opt/x6aa_resource_monitor",
)
