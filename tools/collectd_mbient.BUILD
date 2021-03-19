load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
package(default_visibility = ["//visibility:public"])


filegroup(
    name = "collectd_srcs",
    srcs = glob(["src/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "all_files",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "m4_files",
    srcs = glob(["m4/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "build_sh",
    srcs = ["build.sh"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "configure_file",
    srcs = [
        "configure.ac",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "version_gen_sh",
    srcs = [
        "version-gen.sh",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "makefile_am",
    srcs = [
        "Makefile.am",
    ],
    visibility = ["//visibility:public"],
)


## Approach 2

configure_make(
    name = "build_collectd_1",
    configure_options = [
        "--host x86_64-ubuntu-linux-gnu",
        "--disable-all-plugins",
        "--enable-buddyinfo",
        "--enable-cgroups",
        "--enable-contextswitch",
        "--enable-cpu",
        "--enable-df",
        "--enable-disk",
        "--enable-entropy",
        "--enable-ethstat",
        "--enable-interface",
        "--enable-irq",
        "--enable-load",
        "--enable-logfile",
        "--enable-match_empty_counter",
        "--enable-match_regex",
        "--enable-match_value",
        "--enable-memory",
        "--enable-processes",
        "--enable-rrdtool",
        "--enable-unixsock",
        "--enable-vmem",
        "--enable-write_graphite",
        "--enable-write_log",
        "--enable-gps",
        "--enable-csv",
    ],
    visibility = ["//visibility:public"],
    lib_source = ":all_files",
    make_commands = ["make all"],
)
