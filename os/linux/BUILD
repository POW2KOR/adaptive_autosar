load("@rules_pkg//:pkg.bzl", "pkg_tar")

package(default_visibility = ["//visibility:public"])

pkg_tar(
    name = "package",
    srcs = glob([
        "configs/services/**/*",
    ]),
    mode = "0644",
    package_dir = "/usr/share/apricot",
)
