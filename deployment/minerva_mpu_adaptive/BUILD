load("//:bazel/defs.bzl", "append_and_select", "minerva_aa_update_package_rule")
load(":package.bzl", "SW_PARTNUMBER", "VERSION")
load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")

package(default_visibility = ["//visibility:public"])

pkg_tar(
    name = "filesystem_tar",
    files = {
        "//machine/idc6_m_p1_xavier:machine_exec_config": "/etc/machine_exec_config.json",
    },
    deps =
        append_and_select(
            {
                "//:mt_present": [
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
                "//application/x6aa_rov_transmission_manager:package",
                "//application/x6aa_dummy_2_app:package",
                "//application/diagnostic_manager_deamon_executable:package",
                "//application/sda:package",
                "//application/amsr_vector_fs_swupdateclient:package",
            ],
        ),
)

pkg_deb(
    name = "filesystem_deb",
    # We are using architecture = "all" since it seems `select` doesn't work
    # well with this parameter and we weren't able to find a quick fix.
    architecture = "all",
    data = ":filesystem_tar",
    description = "Distribution of the Minerva Adaptive AUTOSAR stack",
    homepage = "http://swf.daimler.com",
    maintainer = "Minerva Platform",
    package = "minerva_mpu_adaptive",
    version = VERSION,
)

minerva_aa_update_package_rule(
    name = "filesystem_update_package",
    filesystem_src = ":filesystem_tar",
    sw_part_number = SW_PARTNUMBER,
    version = VERSION,
)
