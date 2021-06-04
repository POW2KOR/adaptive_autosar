package(default_visibility = ["//visibility:public"])

config_setting(
    name = "k8",
    values = {
        "cpu": "k8",
    },
)

config_setting(
    name = "aarch64",
    values = {
        "cpu": "aarch64",
    },
)

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
            ":aarch64": 
            [
                # if we do not define the compiler and try to build on the system where only gcc x86_64 installed,
                # collectd will take x86 and build x86 without any warnings, just put in logs compiler
                "CXX=aarch64-linux-gnu-g++",
                "OS=linux",
                "AR=aarch64-linux-gnu-ar",
                "RANLIB=aarch64-linux-gnu-gcc-ranlib",
                "LDCXX=aarch64-linux-gnu-ld",
                "LD=aarch64-linux-gnu-ld",
                "--host aarch64-ubuntu-linux-gnu",
            ],
            ":k8": 
            [
                "CXX=x86_64-linux-gnu-g++",
                "OS=linux",
                "AR=x86_64-linux-gnu-ar",
                "RANLIB=x86_64-linux-gnu-gcc-ranlib",
                "LDCXX=x86_64-linux-gnu-ld",
                "LD=x86_64-linux-gnu-ld",
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
        "collectd"
    ],
)
