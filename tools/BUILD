package(default_visibility = ["//visibility:public"])

load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
# https://github.com/bazelbuild/rules_foreign_cc/tree/main/docs#configure_make

configure_make(
    name = "build_collectd",
    configure_in_place = True,
    autogen = True,
    autogen_command = "build.sh",
    configure_command = "configure",
    configure_options = 
        select({
            "//:aarch64":
            [
                "--host aarch64-ubuntu-linux-gnu",
            ],
            "//:k8":
            [
                "--host x86_64-ubuntu-linux-gnu",
            ],
        }) + [
        "--with-fp-layout=nothing",
        "--disable-werror",
        "--without-java",
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
        "collectd/cpu.so",
        "collectd/csv.so",
    ],
)
