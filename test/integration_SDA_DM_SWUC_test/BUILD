package(default_visibility = ["//visibility:public"])

cc_library(
    name = "communication_lib",
    srcs = [
        "communication.cpp",
    ],
    hdrs = [
        "include/communication.h",
    ],
    deps = [
    ],
)

cc_test(
    name = "read_did_from_sda",
    srcs = [
        "include/communicaton_fixture.h",
        "test.cpp",
    ],
    includes = [
        "include",
    ],
    deps = [
        ":communication_lib",
        "@google//:gtest",
        "@google//:gtest_main",
    ],
)
