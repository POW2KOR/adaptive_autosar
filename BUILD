load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
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

# This filegroup is necessary so that we isolate the output group corresponding
# to the binary of the cmake_external. Otherwise, it adds a lot of noise and
# annoying stuff. Maybe we can find a better way in the future.
# To list the output groups, I used this method:
# https://stackoverflow.com/a/61282031
# More information here:
# - https://docs.bazel.build/versions/master/skylark/rules.html#requesting-output-files
# - https://github.com/bazelbuild/rules_foreign_cc/blob/d54c78ab86b40770ee19f0949db9d74a831ab9f0/tools/build_defs/framework.bzl#L400
filegroup(
    name = "adaptive_autosar_executionmanager_binary",
    srcs = ["//bsw:amsr_vector_fs_em_executionmanager"],
    output_group = "amsr_vector_fs_em_executionmanager",
)

filegroup(
    name = "adaptive_autosar_someipdaemon_binary",
    srcs = ["//bsw:someipd_posix"],
    output_group = "someipd_posix",
)

pkg_tar(
    name = "minerva_mpu_adaptive_binaries",
    files = {
        ":adaptive_autosar_someipdaemon_binary": "opt/someipd_posix/bin/someipd_posix",
        ":adaptive_autosar_executionmanager_binary": "sbin/amsr_vector_fs_em_executionmanager",
        "//application/update_app_demo_idc6:app_v1": "opt/update_app_demo_idc6/bin/update_app_demo_idc6",
        "//application/stub_application:stub_application": "opt/stub_application/bin/stub_application",
    },
    mode = "0755",
    package_dir = "/",
)

pkg_tar(
    name = "minerva_mpu_adaptive_etc",
    srcs = [
        "//machine/idc6_m_p1_xavier:machine_exec_config",
    ],
    files = {
        "//machine/idc6_m_p1_xavier:em_logging_config": "logging_config.json",
    },
    mode = "0755",
    package_dir = "/etc",
)

pkg_tar(
    name = "adaptive_autosar_someipdaemon_configs",
    srcs = {
        "//application/someipd_posix:logging_config": "logging_config.json",
        "//application/someipd_posix:exec_config": "exec_config.json",
        "//application/someipd_posix:someip_config": "someipd-posix.json",
    },
    mode = "0755",
    package_dir = "/opt/someipd_posix/etc/",
)

pkg_tar(
    name = "update_app_v1_demo_configs",
    srcs = {
        "//application/update_app_demo_idc6:exec_config": "exec_config.json",
        "//application/update_app_demo_idc6:updatemanager_swcluster_meta": "swcl_package_metadata.json",
        "//application/update_app_demo_idc6:updatemanager_daemon": "updatemanager.json",
        "//application/update_app_demo_idc6:updatemanager_swcl_db_daemon": "swcl_db.json",
        "//application/update_app_demo_idc6:logging_config": "logging_config.json",
    },
    mode = "0755",
    package_dir = "/opt/update_app_demo_idc6/etc/",
)

pkg_tar(
    name = "adaptive_stub_applications_configs",
    files = {
        "//application/stub_application:stub_application_exec_config": "opt/stub_application/etc/exec_config.json",
        "//application/stub_application:logging_config_json": "opt/stub_application/etc/logging_config.json",
        "//application/stub_application:com_application_json": "opt/stub_application/etc/com_application.json",
    },
    mode = "0755",
)

pkg_tar(
    name = "minerva_mpu_adaptive_configs",
    mode = "0755",
    package_dir = "",
    deps = [
        ":adaptive_autosar_someipdaemon_configs",
        ":adaptive_stub_applications_configs",
        ":update_app_v1_demo_configs",
    ],
)

pkg_tar(
    name = "minerva_mpu_adaptive_filesystem",
    deps = [
        ":minerva_mpu_adaptive_binaries",
        ":minerva_mpu_adaptive_configs",
        ":minerva_mpu_adaptive_etc",
        "//application/scn_param_storage:package",
        "//application/idc6mt:package",
        "//application/executionmanager_state_client_app:package",
        "//application/amsr_vector_fs_log_daemon:package",
    ],
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
