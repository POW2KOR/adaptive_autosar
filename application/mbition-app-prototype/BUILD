load("@rules_cc//cc:defs.bzl", "cc_library")
package(default_visibility = ["//visibility:public"])

# Exports for root BUILD file visibility
exports_files(["src/main.cc"])

cc_library(
    name = "mbition_use_case_1",
    srcs = [
        "lib/mbition_use_case_1/use_case_1.cc",
        "src/config/logging_cfg.h",
    ],
    hdrs = [
        "lib/mbition_use_case_1/includes/use_case_1.h"
    ],
    includes = [
        "lib/mbition_use_case_1/includes/",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic=1,
    deps = [
        "@vector_sip_aa//:mbition_app_prototype_src_gen",
        "@vector_sip_aa//:amsr-vector-fs-communicationmiddleware-headers",
        "@vector_sip_aa//:amsr-vector-fs-comcommon",
    ],
)

cc_library(
    name = "command_line_parser",
    srcs = [
        "lib/command_line_parser/command_line_parser.cpp",
    ],
    hdrs = [
        "lib/command_line_parser/command_line_parser.h"
     ],
    includes = [
        "lib/command_line_parser/",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic=1,
)
