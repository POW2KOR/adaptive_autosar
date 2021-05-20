cc_library(
    name = "mt_memory_accessor",
    srcs = ["linux_memory_accessor.cpp"],
    hdrs = glob(["**/*.h"]),
    copts =
        [
            "-std=c++14",
        ],
    visibility = ["//application/idc6mt:__subpackages__"],
    deps = [
        "//bsw:amsr_vector_fs_log_api",
    ],
)
