package(default_visibility = ["//visibility:public"])

filegroup(
    name = "gcc",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-gcc",
    ],
)

filegroup(
    name = "ar",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-ar",
    ],
)

filegroup(
    name = "ld",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-ld",
    ],
)

filegroup(
    name = "dwp",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-dwp",
    ],
)

filegroup(
    name = "nm",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-nm",
    ],
)

filegroup(
    name = "objcopy",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-objcopy",
    ],
)

filegroup(
    name = "objdump",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-objdump",
    ],
)

filegroup(
    name = "strip",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-strip",
    ],
)

filegroup(
    name = "as",
    srcs = [
        "qnx_host/usr/bin/x86_64-pc-nto-qnx7.0.0-as",
    ],
)

filegroup(
    name = "compiler_pieces",
    srcs = glob([
        "qnx_host/usr/**",
        "qnx_target/**",
    ]),
)

filegroup(
    name = "dynamic_lib",
    srcs = glob(
        ["qnx_host/usr/lib/gcc/x86_64-pc-nto-qnx7.0.0/5.4.0/**/*.so"],
        ["qnx_target/x86_64/lib/**/*.so"],
    ),
)

filegroup(
    name = "static_lib",
    srcs = glob(
        ["qnx_host/usr/lib/gcc/x86_64-pc-nto-qnx7.0.0/5.4.0/**/*.a"],
        ["qnx_target/x86_64/lib/**/*.a"],
    ),
)

filegroup(
    name = "compiler_components",
    srcs = [
        ":ar",
        ":as",
        ":gcc",
        ":ld",
        ":nm",
        ":objcopy",
        ":objdump",
        ":strip",
    ],
)
