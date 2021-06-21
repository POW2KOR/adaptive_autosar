load("@bazel_skylib//rules:common_settings.bzl", "bool_flag", "string_flag")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "append_and_select")
load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")

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

pkg_tar(
    name = "minerva_mpu_adaptive_filesystem",
    files = {
        "//machine/idc6_m_p1_xavier:machine_exec_config": "/etc/machine_exec_config.json",
    },
    deps =
        append_and_select(
            {
                ":mt_present": [
                    "//application/idc6mt:package",
                    "//application/stub_application:package",
                ],
                "//conditions:default": [],
            },
            [
                "//application/amsr_vector_fs_em_executionmanager:package",
                "//application/amsr_vector_fs_sec_cryptostack:package",
                "//application/x6aa_update_dummy_app:package",
                "//application/someipd_posix:package",
                "//application/x6aa_config_manager:package",
                "//application/x6aa_dummy_swc_1:package",
                "//application/x6aa_em_state_client_app:package",
                "//application/x6aa_logging_manager:package",
                "//application/amsr_vector_fs_log_daemon:package",
                "//application/x6aa_resource_monitor:package",
                "//application/x6aa_rov_transmission_manager:package",
                "//application/x6aa_dummy_2_app:package",
                "//application/diagnostic_manager_deamon_executable:package",
            ],
        ),
)

pkg_deb(
    name = "minerva_mpu_adaptive_deb",
    # We are using architecture = "all" since it seems `select` doesn't work well with this parameter and we weren't
    # able to find a quick fix.
    architecture = "all",
    data = ":minerva_mpu_adaptive_filesystem",
    description = "Distribution of the Minerva Adaptive AUTOSAR stack",
    homepage = "http://swf.daimler.com",
    maintainer = "Minerva Platform",
    package = "minerva_mpu_adaptive",
    version = "0.0.0",
)
