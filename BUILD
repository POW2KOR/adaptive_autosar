load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")
load("@io_bazel_rules_docker//container:container.bzl", "container_image")
load("@io_bazel_rules_docker//docker/util:run.bzl", "container_run_and_commit")

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
    name = "adaptive_autosar_log_daemon_binary",
    srcs = ["//bsw:amsr_vector_fs_log_daemon"],
    output_group = "amsr_vector_fs_log_daemon",
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
        ":adaptive_autosar_log_daemon_binary": "opt/amsr_vector_fs_log_daemon/bin/amsr_vector_fs_log_daemon",
        ":adaptive_autosar_executionmanager_binary": "sbin/amsr_vector_fs_em_executionmanager",
        "//bsw:executionmanager_state_client_binary": "opt/executionmanager_state_client_app/bin/executionmanager_state_client_app",
        "//bsw:skeleton_demo_idc6": "opt/BaseApplicationExecutable/bin/BaseApplicationExecutable",
        "//bsw:proxy_demo_idc6": "opt/TestBaseApplicationExecutable/bin/TestBaseApplicationExecutable",
        "//bsw:restart_app_demo_idc6": "opt/restart_app_demo_idc6/bin/restart_app_demo_idc6",
        "//bsw:shutdown_app_demo_idc6": "opt/shutdown_app_demo_idc6/bin/shutdown_app_demo_idc6",
        "//bsw:update_app_demo_idc6": "opt/update_app_demo_idc6/bin/update_app_demo_idc6",
        # For now we are commenting out the references for sw_update_client application
        # as we are not able to build the application with latest delivery
        #"//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app": "opt/sw_update_client_minerva_adapter_app/bin/sw_update_client_minerva_adapter_app",
    },
    mode = "0755",
    package_dir = "/",
)

pkg_tar(
    name = "minerva_mpu_adaptive_etc",
    srcs = [
        "//bsw:machine_exec_config",
    ],
    files = {
        "//bsw:em_logging_config": "logging_config.json",
    },
    mode = "0755",
    package_dir = "/etc",
)

pkg_tar(
    name = "adaptive_autosar_log_daemon_configs",
    files = {
        "//bsw:amsr_vector_fs_log_daemon_logging_config": "logging_config.json",
        "//bsw:amsr_vector_fs_log_daemon_logd_config": "logd_config.json",
        "//bsw:amsr_vector_fs_log_daemon_exec_config": "exec_config.json",
    },
    mode = "0755",
    package_dir = "/opt/amsr_vector_fs_log_daemon/etc/",
)

pkg_tar(
    name = "adaptive_autosar_someipdaemon_configs",
    srcs = {
        "//bsw:someipd_posix_logging_config": "logging_config.json",
        "//bsw:someipd_posix_exec_config": "exec_config.json",
        "//bsw:someipd_posix_someip_config": "someipd-posix.json",
    },
    mode = "0755",
    package_dir = "/opt/someipd_posix/etc/",
)

pkg_tar(
    name = "adaptive_autosar_proxy_configs",
    srcs = {
        "//bsw:proxy_com_application_config": "com_application.json",
        "//bsw:starter_kit_test_base_application_proxy_exec_config": "exec_config.json",
        "//bsw:starter_kit_test_base_application_proxy_updatemanager_swcluster_meta": "swcl_package_metadata.json",
        "//bsw:starter_kit_test_base_application_proxy_updatemanager_daemon": "updatemanager.json",
        "//bsw:starter_kit_test_base_application_proxy_updatemanager_swcl_db_daemon": "swcl_db.json",
        "//bsw:proxy_logging_config": "logging_config.json",
        "//bsw:starter_kit_test_base_application_proxy_someip_config": "someip_config.json",
    },
    mode = "0755",
    package_dir = "/opt/TestBaseApplicationExecutable/etc/",
)

pkg_tar(
    name = "adaptive_autosar_skeleton_configs",
    srcs = {
        "//bsw:skeleton_com_application_config": "com_application.json",
        "//bsw:starter_kit_base_application_skeleton_exec_config": "exec_config.json",
        "//bsw:starter_kit_base_application_skeleton_updatemanager_swcluster_meta": "swcl_package_metadata.json",
        "//bsw:starter_kit_base_application_skeleton_updatemanager_daemon": "updatemanager.json",
        "//bsw:starter_kit_base_application_skeleton_updatemanager_swcl_db_daemon": "swcl_db.json",
        "//bsw:skeleton_logging_config": "logging_config.json",
        "//bsw:starter_kit_base_application_skeleton_someip_config": "someip_config.json",
    },
    mode = "0755",
    package_dir = "/opt/BaseApplicationExecutable/etc/",
)

pkg_tar(
    name = "restart_app_demo_configs",
    srcs = {
        "//bsw:starter_kit_restart_app_idc6_exec_config": "exec_config.json",
        "//bsw:starter_kit_restart_app_idc6_updatemanager_swcluster_meta": "swcl_package_metadata.json",
        "//bsw:starter_kit_restart_app_idc6_updatemanager_daemon": "updatemanager.json",
        "//bsw:starter_kit_restart_app_idc6_updatemanager_swcl_db_daemon": "swcl_db.json",
        "//bsw:restart_app_logging_config": "logging_config.json",
    },
    mode = "0755",
    package_dir = "/opt/restart_app_demo_idc6/etc/",
)

pkg_tar(
    name = "shutdown_app_demo_configs",
    srcs = {
        "//bsw:starter_kit_shutdown_app_idc6_exec_config": "exec_config.json",
        "//bsw:starter_kit_shutdown_app_idc6_updatemanager_swcluster_meta": "swcl_package_metadata.json",
        "//bsw:starter_kit_shutdown_app_idc6_updatemanager_daemon": "updatemanager.json",
        "//bsw:starter_kit_shutdown_app_idc6_updatemanager_swcl_db_daemon": "swcl_db.json",
        "//bsw:shutdown_app_logging_config": "logging_config.json",
    },
    mode = "0755",
    package_dir = "/opt/shutdown_app_demo_idc6/etc/",
)

pkg_tar(
    name = "update_app_v1_demo_configs",
    srcs = {
        "//bsw:starter_kit_update_app_idc6_exec_config": "exec_config.json",
        "//bsw:starter_kit_update_app_idc6_updatemanager_swcluster_meta": "swcl_package_metadata.json",
        "//bsw:starter_kit_update_app_idc6_updatemanager_daemon": "updatemanager.json",
        "//bsw:starter_kit_update_app_idc6_updatemanager_swcl_db_daemon": "swcl_db.json",
        "//bsw:update_app_v1_logging_config": "logging_config.json",
    },
    mode = "0755",
    package_dir = "/opt/update_app_demo_idc6/etc/",
)

pkg_tar(
    name = "adaptive_autosar_executionmanager_state_client_configs",
    files = {
        "//bsw:executionmanager_state_client_updatemanager_daemon_db": "opt/executionmanager_state_client_app/etc/swcl_db.json",
        "//bsw:executionmanager_state_client_updatemanager_swcluser_meta": "opt/executionmanager_state_client_app/etc/swcl_package_metadata.json",
        "//bsw:executionmanager_state_client_app_logging_config": "opt/executionmanager_state_client_app/etc/logging_config.json",
        "//bsw:executionmanager_state_client_app_exec_config": "opt/executionmanager_state_client_app/etc/exec_config.json",
    },
    mode = "0755",
)

pkg_tar(
    name = "adaptive_sw_update_client_minerva_adapter_configs",
    files = {
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_updatemanager_daemon_db": "opt/sw_update_client_minerva_adapter_app/etc/swcl_db.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_updatemanager_config": "opt/sw_update_client_minerva_adapter_app/etc/updatemanager.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_updatemanager_swcluser_meta": "opt/sw_update_client_minerva_adapter_app/etc/swcl_package_metadata.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_someip_config": "opt/sw_update_client_minerva_adapter_app/etc/someip_config.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_exec_config": "opt/sw_update_client_minerva_adapter_app/etc/exec_config.json",
        "//application/sw_update_client_minerva_adapter:logging_config_json": "opt/sw_update_client_minerva_adapter_app/etc/logging_config.json",
        "//application/sw_update_client_minerva_adapter:com_application_json": "opt/sw_update_client_minerva_adapter_app/etc/com_application.json",
    },
    mode = "0755",
)

pkg_tar(
    name = "minerva_mpu_adaptive_configs",
    mode = "0755",
    package_dir = "",
    deps = [
        ":adaptive_autosar_executionmanager_state_client_configs",
        ":adaptive_autosar_log_daemon_configs",
        ":adaptive_autosar_proxy_configs",
        ":adaptive_autosar_skeleton_configs",
        ":adaptive_autosar_someipdaemon_configs",
        # For now we are commenting out the references for sw_update_client application
        # as we are not able to build the application with latest delivery
        #":adaptive_sw_update_client_minerva_adapter_configs",
        ":restart_app_demo_configs",
        ":shutdown_app_demo_configs",
        ":update_app_v1_demo_configs",
    ],
)

pkg_tar(
    name = "minerva_mpu_adaptive_filesystem",
    deps = [
        ":minerva_mpu_adaptive_binaries",
        ":minerva_mpu_adaptive_configs",
        ":minerva_mpu_adaptive_etc",
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

container_run_and_commit(
    name = "minerva_mpu_adaptive_docker_image",
    commands = [
        "apt update",
        "apt-get install -y iproute2 strace",
    ],
    docker_run_flags = [
        "--env http_proxy=http://172.17.0.1:3128",
        "--env https_proxy=http://172.17.0.1:3128",
    ],
    image = "@ubuntu_18.04//image",
)

container_image(
    name = "minerva_mpu_adaptive_docker",
    base = ":minerva_mpu_adaptive_docker_image",
    docker_run_flags = " ".join([
        "-it",
        "--cap-add SYS_NICE",
        "--cap-add NET_ADMIN",
        "--ip 10.21.17.98",
        "--sysctl net.ipv6.conf.all.disable_ipv6=0",
        "--net mnv0",
    ]),
    entrypoint = select({
        ":docker_entrypoint_execution_manager": [
            "/bin/sh",
            "-c",
            "ip link set lo multicast on && ip route add ff01::0/16 dev lo && /sbin/amsr_vector_fs_em_executionmanager -a /opt -m /etc/machine_exec_config.json",
        ],
        ":docker_entrypoint_shell": [
            "/bin/sh",
        ],
    }),
    # The legacy_run_behavior is not disabled on container_image by default
    legacy_run_behavior = False,
    stamp = True,
    tars = [
        ":minerva_mpu_adaptive_filesystem",
    ],
)

# We need it as a temporary workaround to resolve cyclic dependency between code generator and
# socal library. The issue reported and confirmed by Vector.
# Desision to put it here is due to the bazel nature of the relative pates. So we left it in
# the root. The file is used in bsw/BUILD file later.

target_build_dir_for_socal_proxy = select({
    ":k8": [
        "bazel-out/k8-fastbuild/bin/bsw/amsr_vector_fs_socal_for_proxy/lib/libSocal.a",
    ],
    ":aarch64": [
        "bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_proxy/lib/libSocal.a",
    ],
})

target_build_dir_for_socal_skeleton = select({
    ":k8": [
        "bazel-out/k8-fastbuild/bin/bsw/amsr_vector_fs_socal_for_skeleton/lib/libSocal.a",
    ],
    ":aarch64": [
        "bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_skeleton/lib/libSocal.a",
    ],
})

target_build_dir_for_socal_sw_update = select({
    ":k8": [
        "bazel-out/k8-fastbuild/bin/bsw/amsr_vector_fs_socal_for_software_update/lib/libSocal.a",
    ],
    ":aarch64": [
        "bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_software_update/lib/libSocal.a",
    ],
})

filegroup(
    name = "socal_lib_for_proxy",
    srcs = target_build_dir_for_socal_proxy,
    visibility = ["//visibility:public"],
)

filegroup(
    name = "socal_lib_for_skeleton",
    srcs = target_build_dir_for_socal_skeleton,
    visibility = ["//visibility:public"],
)

filegroup(
    name = "socal_lib_for_sw_update",
    srcs = target_build_dir_for_socal_sw_update,
    visibility = ["//visibility:public"],
)
