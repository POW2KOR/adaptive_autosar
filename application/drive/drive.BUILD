load("@rules_pkg//:pkg.bzl", "pkg_tar")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "drive_includes",
    srcs = glob(["drive-t186ref-linux/include/**/*.h"]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "drive_include_lib",
    hdrs = glob(["drive-t186ref-linux/include/**/*.h"]),
    strip_include_prefix = "drive-t186ref-linux/include/",
    visibility = ["//visibility:public"],
)

cc_import(
    name = "libnvducc",
    shared_library = "drive-t186ref-linux/lib-target/libnvducc.so",
)

cc_import(
    name = "libnvdulink",
    shared_library = "drive-t186ref-linux/lib-target/libnvdulink.so",
)
