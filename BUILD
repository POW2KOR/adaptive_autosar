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
                "//application/x6aa_update_dummy_app:package",
                "//application/someipd_posix:package",
                "//application/scn_param_storage:package",
                "//application/x6aa_em_state_client_app:package",
                "//application/amsr_vector_fs_log_daemon:package",
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

# We need it as a temporary workaround to resolve cyclic dependency between code generator and
# socal library. The issue reported and confirmed by Vector.
# Desision to put it here is due to the bazel nature of the relative pates. So we left it in
# the root. The file is used in bsw/BUILD file later.

target_build_dir_for_socal_scn_param_storage = select({
    ":k8": [
        "bazel-out/k8-fastbuild/bin/bsw/amsr_vector_fs_socal_for_scn_param_storage/lib/libSocal.a",
    ],
    ":aarch64": [
        "bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_scn_param_storage/lib/libSocal.a",
    ],
})

filegroup(
    name = "socal_lib_for_scn_param_storage",
    srcs = target_build_dir_for_socal_scn_param_storage,
)
