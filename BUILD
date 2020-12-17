load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")
load("@io_bazel_rules_docker//container:container.bzl", "container_image")
load("@com_github_bazelbuild_buildtools//buildifier:def.bzl", "buildifier")

package(default_visibility = ["//visibility:public"])

string_flag(
    name = "build-target",
    build_setting_default = "minerva-host",
)

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
    srcs = ["@starter_kit_adaptive_xavier//:amsr-vector-fs-em-executionmanager"],
    output_group = "amsr_vector_fs_em_executionmanager",
)

filegroup(
    name = "adaptive_autosar_log_daemon_binary",
    srcs = ["@starter_kit_adaptive_xavier//:amsr_vector_fs_log_daemon"],
    output_group = "amsr_vector_fs_log_daemon",
)

filegroup(
    name = "adaptive_autosar_someipdaemon_binary",
    srcs = ["@starter_kit_adaptive_xavier//:amsr_vector_fs_someipdaemon"],
    output_group = "someipd_posix",
)

pkg_tar(
    name = "minerva_mpu_adaptive_sbin",
    srcs = [":adaptive_autosar_executionmanager_binary"],
    mode = "0755",
    package_dir = "/",
    # If you change strip_prefix, be aware of the following:
    # - https://github.com/bazelbuild/rules_pkg/issues/82
    strip_prefix =
        "./external/starter_kit_adaptive_xavier/amsr-vector-fs-em-executionmanager/",
)

pkg_tar(
    name = "minerva_mpu_adaptive_bsw_opts",
    srcs = [
        ":adaptive_autosar_log_daemon_binary",
        ":adaptive_autosar_someipdaemon_binary",
    ],
    package_dir = "/opt",
    mode = "0755",
    # If you change strip_prefix, be aware of the following:
    # - https://github.com/bazelbuild/rules_pkg/issues/82
    strip_prefix =
        "./external/starter_kit_adaptive_xavier/",
)

pkg_tar(
    name = "minerva_mpu_adaptive_etc",
    srcs = [
        "//bsw:src_gen/example-machine/machine_exec_config.json",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_log_daemon_configs",
    ],
    mode = "0755",
    package_dir = "/etc",
)

pkg_tar(
    name = "adaptive_autosar_log_daemon_configs",
    srcs = [
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_log_daemon_configs",
    ],
    mode = "0755",
    package_dir = "/amsr_vector_fs_log_daemon/etc/",
)

pkg_tar(
    name = "minerva_mpu_adaptive_configs",
    deps = [
        ":adaptive_autosar_log_daemon_configs",
    ],
    mode = "0755",
    package_dir = "/opt",
)

pkg_tar(
    name = "minerva_mpu_adaptive_filesystem",
    deps = [
        ":minerva_mpu_adaptive_bsw_opts",
        ":minerva_mpu_adaptive_etc",
        ":minerva_mpu_adaptive_configs",
        ":minerva_mpu_adaptive_sbin",
    ],
)

pkg_deb(
    name = "minerva_mpu_adaptive_deb",
    architecture = "amd64",
    data = ":minerva_mpu_adaptive_filesystem",
    description = "Distribution of the Minerva Adaptive AUTOSAR stack",
    homepage = "http://swf.daimler.com",
    maintainer = "Minerva Platform",
    package = "minerva_mpu_adaptive",
    version = "0.0.0",
)

container_image(
    name = "minerva_mpu_adaptive_docker",
    base = "@ubuntu_18.04//image",
    entrypoint = "/sbin/amsr_vector_fs_em_executionmanager " +
                 "-a /opt -m /etc/machine_exec_config.json",
    # The legacy_run_behavior is not disabled on container_image by default
    legacy_run_behavior = False,
    stamp = True,
    tars = [
        ":minerva_mpu_adaptive_filesystem",
    ],
)

# Buildifier
buildifier(
    name = "buildifier",
)
