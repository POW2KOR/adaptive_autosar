cc_library(
    name = "mt_logic",
    srcs =
        [
            "configuration_parser.cpp",
            "measurement_daemon.cpp",
        ],
    hdrs = glob(["**/*.h"]),
    copts =
        [
            "-std=c++14",
        ],
    visibility = ["//application/idc6mt:__pkg__"],
    deps = [
        "//application/idc6mt/accessor:mt_memory_accessor",
        "//bsw:amsr_vector_fs_log_api",
    ],
)
