load("@x86_64_qnx_compiler//:qnx_toolchain_config.bzl", "x86_64_cc_toolchain_config")
load("@aarch64_qnx_compiler//:qnx_toolchain_config.bzl", "aarch64_cc_toolchain_config")
load("@rules_cc//cc:defs.bzl", "cc_toolchain", "cc_toolchain_suite")

package(default_visibility = ["//visibility:public"])

x86_64_cc_toolchain_config(name = "x86_64_qnx_toolchain_config")

cc_toolchain(
    name = "x86_64-pc-nto-qnx7.0.0",
    # all_files is used to determine which compiler files are copied into the sandbox
    all_files = "@x86_64_qnx_compiler//:compiler_pieces",
    ar_files = "@x86_64_qnx_compiler//:compiler_components",
    compiler_files = "@x86_64_qnx_compiler//:compiler_components",
    dwp_files = "@x86_64_qnx_compiler//:compiler_components",
    dynamic_runtime_lib = "@x86_64_qnx_compiler//:dynamic_lib",
    linker_files = "@x86_64_qnx_compiler//:compiler_components",
    objcopy_files = "@x86_64_qnx_compiler//:compiler_components",
    static_runtime_lib = "@x86_64_qnx_compiler//:static_lib",
    strip_files = "@x86_64_qnx_compiler//:compiler_components",
    supports_param_files = 1,
    toolchain_config = ":x86_64_qnx_toolchain_config",
    toolchain_identifier = "x86_64-pc-nto-qnx7.0.0",
)

aarch64_cc_toolchain_config(name = "aarch64_qnx_toolchain_config")

cc_toolchain(
    name = "aarch64-unknown-nto-qnx7.0.0",
    # all_files is used to determine which compiler files are copied into the sandbox
    all_files = "@aarch64_qnx_compiler//:compiler_pieces",
    ar_files = "@aarch64_qnx_compiler//:compiler_components",
    compiler_files = "@aarch64_qnx_compiler//:compiler_components",
    dwp_files = "@aarch64_qnx_compiler//:compiler_components",
    dynamic_runtime_lib = "@aarch64_qnx_compiler//:dynamic_lib",
    linker_files = "@aarch64_qnx_compiler//:compiler_components",
    objcopy_files = "@aarch64_qnx_compiler//:compiler_components",
    static_runtime_lib = "@aarch64_qnx_compiler//:static_lib",
    strip_files = "@aarch64_qnx_compiler//:compiler_components",
    supports_param_files = 1,
    toolchain_config = ":aarch64_qnx_toolchain_config",
    toolchain_identifier = "aarch64-unknown-nto-qnx7.0.0",
)

cc_toolchain_suite(
    name = "toolchain",
    toolchains = {
        "k8": ":x86_64-pc-nto-qnx7.0.0",
        "aarch64": ":aarch64-unknown-nto-qnx7.0.0",
    },
)
