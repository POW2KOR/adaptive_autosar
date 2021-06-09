package(default_visibility = ["//visibility:public"])

cc_test(
    name = "calculator_test",
    srcs = [
        "calc_test.cpp",
    ],
    includes = ["src/"],
    deps = [
        "//test/src:calculator",
        "@google//:gtest",
        "@google//:gtest_main",  # Only if hello_test.cc has no main()
    ],
)
