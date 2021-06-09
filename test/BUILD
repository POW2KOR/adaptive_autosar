package(default_visibility = ["//visibility:public"])

cc_library(
    name = "calculator",
    srcs = [
        "src/calc.cpp",
    ],
    hdrs = [
        "src/calc.h",
    ],
)

cc_test(
    name = "calculator_test",
    srcs = [
        "calc_test.cpp",
    ],
    includes = ["src/"],
    deps = [
        ":calculator",
        "@google//:gtest",
        "@google//:gtest_main",  # Only if hello_test.cc has no main()
    ],
)
