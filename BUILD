load("@bazel_skylib//rules:common_settings.bzl", "bool_flag", "string_flag")

package(default_visibility = ["//visibility:public"])

string_flag(
    name = "docker_entrypoint",
    build_setting_default = "execution_manager",
)

config_setting(
    name = "docker_entrypoint_shell",
    flag_values = {
        ":docker_entrypoint": "shell",
    },
)

config_setting(
    name = "docker_entrypoint_execution_manager",
    flag_values = {
        ":docker_entrypoint": "execution_manager",
    },
)

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

# Temporary targets kept around for backward compatibility

genrule(
    name = "minerva_mpu_adaptive_filesystem",
    srcs = ["//deployment/minerva_mpu_adaptive:filesystem_tar"],
    outs = ["minerva_mpu_adaptive_filesystem.tar"],
    cmd = "cp $(location //deployment/minerva_mpu_adaptive:filesystem_tar) $@",
)

genrule(
    name = "minerva_mpu_adaptive_deb",
    srcs = ["//deployment/minerva_mpu_adaptive:filesystem_deb"],
    outs = ["minerva_mpu_adaptive_deb.deb"],
    cmd = "cp $(location //deployment/minerva_mpu_adaptive:filesystem_deb) $@",
)
