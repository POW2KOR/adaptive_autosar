load("//:bazel/defs.bzl", "minerva_aa_update_package_rule")
load(":package.bzl", "SW_PARTNUMBER", "VERSION")
load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")

package(default_visibility = ["//visibility:public"])

pkg_tar(
    name = "filesystem_tar",
    files = {
        "//machine/civic_m_p:i3_machine_exec_config": "/etc/machine_exec_config.json",
        "//deployment/apricot_adaptive:post_install.sh": "/usr/share/apricot/post_install.sh",
        "//deployment/apricot_adaptive:pre_removal.sh": "/usr/share/apricot/pre_removal.sh",
        "//deployment/apricot_adaptive:network_setup.sh": "/usr/share/apricot/network_setup.sh",
    },
    deps =
            [
                "//application/amsr_vector_fs_em_executionmanager:package",
                "//application/someipd_posix:package",
                "//application/amsr_vector_fs_log_daemon:package",
                "//application/InternalRouting_CIVIC_M_P_ST35_Executable:package",
                "//application/x6aa_em_state_client_app:package",
                "//os/linux:package",
            ],
)

pkg_deb(
    name = "filesystem_deb",
    # We are using architecture = "all" since it seems `select` doesn't work
    # well with this parameter and we weren't able to find a quick fix.
    architecture = "all",
    data = ":filesystem_tar",
    description = "Distribution of the Apricot Adaptive AUTOSAR stack",
    homepage = "http://swf.daimler.com",
    maintainer = "Apricot Platform",
    package = "apricot_adaptive",
    postinst = "post_install.sh",
    prerm = "pre_removal.sh",
    version = VERSION,
)

minerva_aa_update_package_rule(
    name = "filesystem_update_package",
    filesystem_src = ":filesystem_tar",
    sw_part_number = SW_PARTNUMBER,
    version = VERSION,
)
