load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
    "with_feature_set",
)
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

# New configuration file is needed since bazel by default
# doesn't provide configuration for the qnx gcc.
# This file is used for setup of the compiler, linker,
# archiver flags and all gcc tools. This template
# is used by x86_64_qnx_configure.bzl.


all_compile_actions = [
    ACTION_NAMES.c_compile,
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.assemble,
    ACTION_NAMES.preprocess_assemble,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.cpp_module_codegen,
    ACTION_NAMES.clif_match,
    ACTION_NAMES.lto_backend,
]

all_cpp_compile_actions = [
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.cpp_module_codegen,
    ACTION_NAMES.clif_match,
]

preprocessor_compile_actions = [
    ACTION_NAMES.c_compile,
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.preprocess_assemble,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.clif_match,
]

codegen_compile_actions = [
    ACTION_NAMES.c_compile,
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.assemble,
    ACTION_NAMES.preprocess_assemble,
    ACTION_NAMES.cpp_module_codegen,
    ACTION_NAMES.lto_backend,
]

all_link_actions = [
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    tool_paths = [
        tool_path(
            name = "gcc",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-gcc",
        ),
        tool_path(
            name = "ld",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-ld",
        ),
        tool_path(
            name = "ar",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-ar",
        ),
        tool_path(
            name = "cpp",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-cpp",
        ),
        tool_path(
            name = "gcov",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-gcov",
        ),
        tool_path(
            name = "nm",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-nm",
        ),
        tool_path(
            name = "objdump",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-objdump",
        ),
        tool_path(
            name = "strip",
            path = "%{HOST_PATH}%/usr/bin/x86_64-pc-nto-qnx7.0.0-strip",
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
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-fuse-ld=gold",
                                "-Wl,-no-as-needed",
                                "-Wl,-z,relro,-z,now",
                                "-pass-exit-codes",

                                "-L%{HOST_PATH}%/usr/lib/gcc/x86_64-pc-nto-qnx7.0.0/5.4.0/",
                                "-L%{TARGET_PATH}%/x86_64/lib/gcc/5.4.0",
                                "-L%{TARGET_PATH}%/usr/x86_64-pc-nto-qnx7.0.0/lib/",
		                        "-L%{TARGET_PATH}%/x86_64/lib/",
                                "-L%{TARGET_PATH}%/x86_64/lib",
                                "-L%{TARGET_PATH}%/x86_64/usr/lib",
                                "-L%{TARGET_PATH}%/x86_64/opt/lib",
                                
                                "-lm",
                                "-lc++",
                            ],
                        ),
                    ]),
                ),
                flag_set(
                    actions = all_link_actions,
                    flag_groups = [flag_group(flags = ["-Wl,--gc-sections"])],
                    with_features = [with_feature_set(features = ["opt"])],
                ),
            ],
        ),
        feature(
            name = "compiler_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_compile_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-U_FORTIFY_SOURCE",
                                "-D_FORTIFY_SOURCE=1",

                                "-Wall",
                                "-Wextra",
                                "-Wconversion",
                                "-Wpedantic",
                                "-Wshadow",

                                "-Wunused-but-set-parameter",
                                "-Wno-free-nonheap-object",

                                "-fstack-protector",
                                "-fno-omit-frame-pointer",

                                "-no-canonical-prefixes",
                                "-fno-canonical-system-headers",

                                # We use gnu++14 for now because otherwise the
                                # libosabstraction BSW module does not build
                                "-std=gnu++14",

                                "-D_QNX_SOURCE",
                                "-D__QNXNTO__",
                                "-D__QNX__",
                                "-D__GNUC__=5",
                                "-D__GNUC_MINOR__=4",
                                "-D__GNUC_PATCHLEVEL__=0",
                                "-D__unix__",
                                "-D__unix",
                                "-D__ELF__",
                                "-D__X86_64__",
                                "-D__LITTLEENDIAN__",
                                
                                "-nostdinc",
                                "-nostdinc++",

                                # C headers
                                "-isystem%{TARGET_PATH}%/usr/include",
                                "-isystem%{HOST_PATH}%/usr/lib/gcc/x86_64-pc-nto-qnx7.0.0/5.4.0/include",
                                
                                # C++ headers
                                "-isystem%{TARGET_PATH}%/usr/include/c++/v1"
                            ],
                        ),
                    ]),
                ),
                flag_set(
                    actions = [
                        ACTION_NAMES.cpp_compile,
                        ACTION_NAMES.cpp_module_codegen,
                        ACTION_NAMES.cpp_header_parsing,
                        ACTION_NAMES.cpp_module_compile,
                    ],
                    flag_groups = [
                        flag_group(flags = [
                            "-Wold-style-cast",
                            "-Wnon-virtual-dtor",
                        ])
                    ],
                ),
                flag_set(
                    actions = all_compile_actions,
                    flag_groups = [flag_group(flags = ["-g"])],
                    with_features = [with_feature_set(features = ["dbg"])],
                ),
                flag_set(
                    actions = all_compile_actions,
                    flag_groups = [
                        flag_group(
                            flags = [
                                "-g0",
                                "-O2",
                                "-DNDEBUG",
                                "-ffunction-sections",
                                "-fdata-sections",
                            ],
                        ),
                    ],
                    with_features = [with_feature_set(features = ["opt"])],
                ),
            ],
        ),

        feature(
            name = "sysroot",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_compile_actions + all_link_actions,
                    flag_groups = [
                        flag_group(
                            flags = ["--sysroot=%{TARGET_PATH}%/x86_64"],
                        ),
                    ],
                ),
            ],
        ),

        feature(
            name = "socket",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = [flag_group(flags = ["-lsocket"])],
                    with_features = [with_feature_set(features = ["socket"])],
                ),
            ],
        ),
        feature(
            name = "pthread",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    # We keep this flag empty for the QNX toolchain since it is implicit
                    # For other toolchains, we populate this with the correct flag
                    flag_groups = [flag_group(flags = [""])],
                    with_features = [with_feature_set(features = ["pthread"])],
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            "%{HOST_PATH}%/usr/lib/gcc/x86_64-pc-nto-qnx7.0.0/5.4.0/include/",
            "%{TARGET_PATH}%/usr/include/",
        ],
        toolchain_identifier = "x86_64-pc-nto-qnx7.0.0",
        host_system_name = "",
        target_system_name = "qnx",
        target_cpu = "k8",
        target_libc = "",
        compiler = "x86_64-pc-nto-qnx7.0.0",
        abi_version = "",
        abi_libc_version = "",
        builtin_sysroot = "%{TARGET_PATH}%/x86_64",
        tool_paths = tool_paths,
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {
    },
    provides = [CcToolchainConfigInfo],
)
