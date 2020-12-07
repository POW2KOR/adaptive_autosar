load("@aarch64_linux_linaro_compiler//:aarch64_linux_linaro_toolchain_config.bzl", "cc_toolchain_config")
load("@rules_cc//cc:defs.bzl", "cc_toolchain", "cc_toolchain_suite")

package(default_visibility = ["//visibility:public"])

cc_toolchain_config(name = "aarch64_linux_linaro_toolchain_config")

cc_toolchain_suite(
    name = "toolchain",
    toolchains = {
        "aarch64": ":gcc-linux-aarch64",
    },
)

filegroup(
    name = "empty",
    srcs = [],
)

filegroup(
    name = "arm_linux_all_files",
    srcs = [
        "@aarch64_linux_linaro_compiler//:compiler_pieces",
    ],
)

filegroup(
    name = "compiler",
    srcs = [
        "@aarch64_linux_linaro_compiler//:compiler",
    ],
)

filegroup(
    name = "archieve",
    srcs = [
        "@aarch64_linux_linaro_compiler//:ar",
    ],
)

filegroup(
    name = "dwp",
    srcs = [
        "@aarch64_linux_linaro_compiler//:dwp",
    ],
)

filegroup(
    name = "dynamic_lib",
    srcs = [
        "@aarch64_linux_linaro_compiler//:dynamic_lib",
    ],
)

filegroup(
    name = "linker",
    srcs = [
        "@aarch64_linux_linaro_compiler//:ld",
    ],
)

filegroup(
    name = "objcopy",
    srcs = [
        "@aarch64_linux_linaro_compiler//:objcopy",
    ],
)

filegroup(
    name = "static_lib",
    srcs = [
        "@aarch64_linux_linaro_compiler//:static_lib",
    ],
)

filegroup(
    name = "strip",
    srcs = [
        "@aarch64_linux_linaro_compiler//:strip",
    ],
)

filegroup(
    name = "compiler_components",
    srcs = [
        "@aarch64_linux_linaro_compiler//:compiler_components",
    ],
)

cc_toolchain(
    name = "gcc-linux-aarch64",
    all_files = ":arm_linux_all_files",
    ar_files = ":compiler_components",
    compiler_files = ":compiler_components",
    dwp_files = ":compiler_components",
    dynamic_runtime_lib = ":dynamic_lib",
    linker_files = ":linker",
    objcopy_files = ":compiler_components",
    static_runtime_lib = ":static_lib",
    strip_files = ":compiler_components",
    supports_param_files = 1,
    toolchain_config = ":aarch64_linux_linaro_toolchain_config",
    toolchain_identifier = "aarch64-linux-gnu",
)
