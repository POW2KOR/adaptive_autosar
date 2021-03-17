load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool",
    "tool_path",
    "variable_with_value",
    "with_feature_set",
)
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

# New configuration file is needed since bazel by default
# doesn't provide configuration for the aarch64 gcc.
# This file is used for setup of the compiler, linker,
# archiver flags and all gcc tools. This template
# is used by aarch64_linux_ubuntu_configure.bzl.

def _impl(ctx):
    tool_paths = [
        tool_path(
            name = "gcc",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-gcc",
        ),
        tool_path(
            name = "ld",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-ld",
        ),
        tool_path(
            name = "ar",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-ar",
        ),
        tool_path(
            name = "cpp",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-cpp",
        ),
        tool_path(
            name = "gcov",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-gcov",
        ),
        tool_path(
            name = "nm",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-nm",
        ),
        tool_path(
            name = "objdump",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-objdump",
        ),
        tool_path(
            name = "strip",
            path = "%{USER_PATH}%/bin/aarch64-linux-gnu-strip",
        ),
    ]

    features = [
        feature(
            name = "random_seed",
            enabled = True,
        ),
        feature(
            name = "strip_debug_symbols",
            enabled = True,
        ),
        feature(
            name = "linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = [
                        ACTION_NAMES.cpp_link_executable,
                    ],
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-lstdc++",
                                "-lm",
                                "-fuse-ld=gold",
                                "-Wl,-no-as-needed",
                                "-Wl,-z,relro,-z,now",
                                "-pass-exit-codes",
                                "-Wl,--gc-sections",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
        feature(
            name = "compiler_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = [
                        ACTION_NAMES.c_compile,
                        ACTION_NAMES.cpp_compile,
                        ACTION_NAMES.linkstamp_compile,
                        ACTION_NAMES.cc_flags_make_variable,
                        ACTION_NAMES.cpp_module_codegen,
                        ACTION_NAMES.cpp_header_parsing,
                        ACTION_NAMES.cpp_module_compile,
                        ACTION_NAMES.assemble,
                        ACTION_NAMES.preprocess_assemble,
                        ACTION_NAMES.lto_indexing,
                        ACTION_NAMES.lto_backend,
                        ACTION_NAMES.lto_index_for_executable,
                        ACTION_NAMES.lto_index_for_dynamic_library,
                        ACTION_NAMES.lto_index_for_nodeps_dynamic_library,
                        ACTION_NAMES.cpp_link_dynamic_library,
                        ACTION_NAMES.cpp_link_nodeps_dynamic_library,
                        ACTION_NAMES.strip,
                        ACTION_NAMES.objc_archive,
                        ACTION_NAMES.objc_compile,
                        ACTION_NAMES.objc_executable,
                        ACTION_NAMES.objc_fully_link,
                        ACTION_NAMES.objcpp_compile,
                        ACTION_NAMES.objcpp_executable,
                        ACTION_NAMES.clif_match,
                    ],
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-U_FORTIFY_SOURCE",
                                "-fstack-protector",
                                "-Wall",
                                "-Wunused-but-set-parameter",
                                "-Wno-free-nonheap-object",
                                "-fno-omit-frame-pointer",
                                "-D_FORTIFY_SOURCE=1",
                            ],
                        ),
                    ]),
                ),
                flag_set(
                    actions = [
                        ACTION_NAMES.assemble,
                        ACTION_NAMES.preprocess_assemble,
                        ACTION_NAMES.linkstamp_compile,
                        ACTION_NAMES.c_compile,
                        ACTION_NAMES.cpp_compile,
                        ACTION_NAMES.cpp_header_parsing,
                        ACTION_NAMES.cpp_module_compile,
                        ACTION_NAMES.cpp_module_codegen,
                        ACTION_NAMES.lto_backend,
                        ACTION_NAMES.clif_match,
                    ],
                    flag_groups = [
                        flag_group(
                            flags = [
                                "-g",
                                "-O2",
                                "-DNDEBUG",
                                "-ffunction-sections",
                                "-fdata-sections",
                            ],
                        ),
                    ],
                ),
            ],
        ),

        feature(
            name = "sysroot",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = [
                        ACTION_NAMES.preprocess_assemble,
                        ACTION_NAMES.linkstamp_compile,
                        ACTION_NAMES.c_compile,
                        ACTION_NAMES.cpp_compile,
                        ACTION_NAMES.cpp_header_parsing,
                        ACTION_NAMES.cpp_module_compile,
                        ACTION_NAMES.cpp_module_codegen,
                        ACTION_NAMES.lto_backend,
                        ACTION_NAMES.clif_match,
                        ACTION_NAMES.cpp_link_executable,
                        ACTION_NAMES.cpp_link_dynamic_library,
                        ACTION_NAMES.cpp_link_nodeps_dynamic_library,
                    ],
                    flag_groups = [
                        flag_group(
                            flags = ["--sysroot=%{sysroot}"],
                            expand_if_available = "sysroot",
                        ),
                    ],
                ),
            ],
        ),

        feature(
            name = "unfiltered_compile_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = [
                        ACTION_NAMES.assemble,
                        ACTION_NAMES.preprocess_assemble,
                        ACTION_NAMES.linkstamp_compile,
                        ACTION_NAMES.c_compile,
                        ACTION_NAMES.cpp_compile,
                        ACTION_NAMES.cpp_header_parsing,
                        ACTION_NAMES.cpp_module_compile,
                        ACTION_NAMES.cpp_module_codegen,
                        ACTION_NAMES.lto_backend,
                        ACTION_NAMES.clif_match,
                    ],
                    flag_groups = [
                        flag_group(
                            flags = [
                                "-Wno-builtin-macro-redefined",
                                "-D__DATE__=\"redacted\"",
                                "-D__TIMESTAMP__=\"redacted\"",
                                "-D__TIME__=\"redacted\"",
                                "-no-canonical-prefixes",
                                "-fno-canonical-system-headers",
                            ],
                        ),
                    ],
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            "%{USER_PATH}%/aarch64-linux-gnu/include/c++/7/",
            "%{USER_PATH}%/aarch64-linux-gnu/include/c++/7/backward",
            "%{USER_PATH}%/aarch64-linux-gnu/include/",
            "%{USER_PATH}%/lib/gcc-cross/aarch64-linux-gnu/7/include",
            "%{USER_PATH}%/lib/gcc-cross/aarch64-linux-gnu/7/include-fixed",
        ],
        toolchain_identifier = "aarch64-linux-gnu",
        host_system_name = "",
        target_system_name = "linux",
        target_cpu = "aarch64",
        target_libc = "",
        compiler = "aarch64_linux_ubuntu",
        abi_version = "",
        abi_libc_version = "",
        tool_paths = tool_paths,
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {
    },
    provides = [CcToolchainConfigInfo],
)
