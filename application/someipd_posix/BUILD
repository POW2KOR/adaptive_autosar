load("@rules_pkg//:pkg.bzl", "pkg_tar")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "logging_config",
    srcs = [
        "config/logging_config.json",
    ],
)

filegroup(
    name = "exec_config",
    srcs = [
        "config/exec_config.json",
    ],
)

filegroup(
    name = "someip_config",
    srcs = [
        "config/someipd-posix.json",
    ],
)

# This filegroup is necessary so that we isolate the output group corresponding
# to the binary of the cmake_external. Otherwise, it adds a lot of noise and
# annoying stuff. Maybe we can find a better way in the future.
# To list the output groups, I used this method:
# https://stackoverflow.com/a/61282031
# More information here:
# - https://docs.bazel.build/versions/master/skylark/rules.html#requesting-output-files
# - https://github.com/bazelbuild/rules_foreign_cc/blob/d54c78ab86b40770ee19f0949db9d74a831ab9f0/tools/build_defs/framework.bzl#L400

filegroup(
    name = "app",
    srcs = ["//bsw:someipd_posix"],
    output_group = "someipd_posix",
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/someipd_posix",
        ":exec_config": "etc/exec_config.json",
        ":logging_config": "etc/logging_config.json",
        ":someip_config": "etc/someipd-posix.json",
        "//application/x6aa_config_manager:static_sd_config": "etc/static_sd_config.json",
    },
    mode = "0755",
    package_dir = "opt/someipd_posix",
)
