package(default_visibility = ["//visibility:public"])

filegroup(
    name = "gcc",
    srcs = [
        "bin/aarch64-linux-gnu-gcc",
    ],
)

filegroup(
    name = "ar",
    srcs = [
        "bin/aarch64-linux-gnu-ar",
    ],
)

filegroup(
    name = "ld",
    srcs = [
        "bin/aarch64-linux-gnu-ld",
    ],
)

filegroup(
    name = "dwp",
    srcs = [
        "bin/aarch64-linux-gnu-dwp",
    ],
)

filegroup(
    name = "nm",
    srcs = [
        "bin/aarch64-linux-gnu-nm",
    ],
)

filegroup(
    name = "objcopy",
    srcs = [
        "bin/aarch64-linux-gnu-objcopy",
    ],
)

filegroup(
    name = "objdump",
    srcs = [
        "bin/aarch64-linux-gnu-objdump",
    ],
)

filegroup(
    name = "strip",
    srcs = [
        "bin/aarch64-linux-gnu-strip",
    ],
)

filegroup(
    name = "as",
    srcs = [
        "bin/aarch64-linux-gnu-as",
    ],
)

filegroup(
    name = "compiler_pieces",
    srcs = glob([
        "lib/gcc-cross/aarch64-linux-gnu/7/**",
        "aarch64-linux-gnu/**",
    ]),
)

filegroup(
    name = "dynamic_lib",
    srcs = glob(
        ["aarch64-linux-gnu/**/*.so"],
    ),
)

filegroup(
    name = "static_lib",
    srcs = glob(
        ["aarch64-linux-gnu/**/*.a"],
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
