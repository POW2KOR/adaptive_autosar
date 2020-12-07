load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@rules_pkg//:pkg.bzl", "pkg_tar", "pkg_deb")
load("@io_bazel_rules_docker//container:container.bzl", "container_image")

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

# This filegroup is necessary so that we isolate the output group corresponding
# to the binary of the cmake_external. Otherwise, it adds a lot of noise and
# annoying stuff. Maybe we can find a better way in the future.
# To list the output groups, I used this method:
# https://stackoverflow.com/a/61282031
# More information here:
# - https://docs.bazel.build/versions/master/skylark/rules.html#requesting-output-files
# - https://github.com/bazelbuild/rules_foreign_cc/blob/d54c78ab86b40770ee19f0949db9d74a831ab9f0/tools/build_defs/framework.bzl#L400
filegroup(
    name="adaptive_autosar_executionmanager_binary",
    srcs=["@vector_sip_aa//:amsr-vector-fs-em-executionmanager"],
    output_group="amsr_vector_fs_em_executionmanager"
)

pkg_tar(
    name = "minerva_mpu_adaptive_binaries",
    package_dir = "/",
    # If you change strip_prefix, be aware of the following:
    # - https://github.com/bazelbuild/rules_pkg/issues/82
    strip_prefix = 
        "./external/vector_sip_aa/amsr-vector-fs-em-executionmanager/",
    srcs = [":adaptive_autosar_executionmanager_binary"],
    mode = "0755",
)

pkg_tar(
    name = "minerva_mpu_adaptive_configs",
    package_dir = "/etc",
    srcs = ["//bsw:src_gen/example-machine/machine_exec_config.json"],
    mode = "0755",
)

pkg_tar(
    name = "minerva_mpu_adaptive_filesystem",
    deps = [
        ":minerva_mpu_adaptive_binaries",
        ":minerva_mpu_adaptive_configs",
    ],
)

pkg_deb(
    name = "minerva_mpu_adaptive_deb",
    architecture = "amd64",
    data = ":minerva_filesystem",
    description = "Distribution of the Minerva Adaptive AUTOSAR stack",
    homepage = "http://swf.daimler.com",
    maintainer = "Minerva Platform",
    package = "minerva_mpu_adaptive",
    version = "0.0.0",
)

container_image(
    name = "minerva_mpu_adaptive_docker",
    base = "@ubuntu_18.04//image",
    stamp = True,
    tars = [
        ":minerva_mpu_adaptive_filesystem",
    ],
    # The legacy_run_behavior is not disabled on container_image by default
    legacy_run_behavior = False,
    entrypoint = "/sbin/amsr_vector_fs_em_executionmanager "+
        "-a /opt -m /etc/machine_exec_config.json"
)
