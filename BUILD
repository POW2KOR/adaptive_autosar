load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")

package(default_visibility = ["//visibility:public"])


string_flag(name = "build-target", build_setting_default = "minerva-host")

config_setting(
    name = "minerva-host",
    flag_values = {
        ":build-target": "minerva-host",
    },
)

config_setting(
    name = "minerva-drive-sdk",
    flag_values = {
        ":build-target": "minerva-drive-sdk",
    },
)

config_setting(
    name = "minerva-target",
    flag_values = {
        ":build-target": "minerva-target",
    },
)
