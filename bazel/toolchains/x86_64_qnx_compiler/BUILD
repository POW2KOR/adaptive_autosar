load("@x86_64_qnx_compiler//:x86_64_qnx_toolchain_config.bzl", "cc_toolchain_config")
load("@rules_cc//cc:defs.bzl", "cc_toolchain", "cc_toolchain_suite")

package(default_visibility = ["//visibility:public"])

cc_toolchain_config(name = "x86_64_qnx_toolchain_config")

cc_toolchain_suite(
    name = "toolchain",
    toolchains = {
        "k8": ":x86_64-pc-nto-qnx7.0.0",
    },
)

filegroup(
    name = "empty",
    srcs = [],
)

filegroup(
    name = "x86_64_qnx_all_files",
    srcs = [
        "@x86_64_qnx_compiler//:compiler_pieces",
    ],
)

filegroup(
    name = "compiler",
    srcs = [
        "@x86_64_qnx_compiler//:compiler",
    ],
)

filegroup(
    name = "archive",
    srcs = [
        "@x86_64_qnx_compiler//:ar",
    ],
)

filegroup(
    name = "dwp",
    srcs = [
        "@x86_64_qnx_compiler//:dwp",
    ],
)

filegroup(
    name = "dynamic_lib",
    srcs = [
        "@x86_64_qnx_compiler//:dynamic_lib",
    ],
)

filegroup(
    name = "linker",
    srcs = [
        "@x86_64_qnx_compiler//:ld",
    ],
)

filegroup(
    name = "objcopy",
    srcs = [
        "@x86_64_qnx_compiler//:objcopy",
    ],
)

filegroup(
    name = "static_lib",
    srcs = [
        "@x86_64_qnx_compiler//:static_lib",
    ],
)

filegroup(
    name = "strip",
    srcs = [
        "@x86_64_qnx_compiler//:strip",
    ],
)

filegroup(
    name = "compiler_components",
    srcs = [
        "@x86_64_qnx_compiler//:compiler_components",
    ],
)

cc_toolchain(
    name = "x86_64-pc-nto-qnx7.0.0",
    all_files = ":x86_64_qnx_all_files",
    ar_files = ":compiler_components",
    compiler_files = ":compiler_components",
    dwp_files = ":compiler_components",
    dynamic_runtime_lib = ":dynamic_lib",
    linker_files = ":linker",
    objcopy_files = ":compiler_components",
    static_runtime_lib = ":static_lib",
    strip_files = ":compiler_components",
    supports_param_files = 1,
    toolchain_config = ":x86_64_qnx_toolchain_config",
    toolchain_identifier = "x86_64-pc-nto-qnx7.0.0",
)
