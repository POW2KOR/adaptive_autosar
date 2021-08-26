load("@bazel_skylib//rules:common_settings.bzl", "bool_flag", "string_flag")

package(default_visibility = ["//visibility:public"])

string_flag(
    name = "os",
    build_setting_default = "linux",
)

config_setting(
    name = "qnx",
    flag_values = {
        ":os": "qnx",
    },
)

config_setting(
    name = "linux",
    flag_values = {
        ":os": "linux",
    },
)

config_setting(
    name = "aarch64",
    values = {
        "cpu": "aarch64",
    },
)

config_setting(
    name = "k8",
    values = {
        "cpu": "k8",
    },
)

bool_flag(
    name = "mt",
    build_setting_default = False,
)

config_setting(
    name = "mt_present",
    flag_values = {
        ":mt": "True",
    },
)
