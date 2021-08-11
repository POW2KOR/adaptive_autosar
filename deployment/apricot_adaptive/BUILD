load("//:bazel/defs.bzl", "append_and_select", "minerva_aa_update_package_rule")
load(":package.bzl", "SW_PARTNUMBER", "VERSION")
load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")

package(default_visibility = ["//visibility:public"])

pkg_tar(
    name = "filesystem_tar",
    files = {
        "//machine/idc6_m_p1_xavier:machine_exec_config": "/etc/machine_exec_config.json",
        "//deployment/apricot_adaptive:post_install.sh": "/usr/share/apricot/post_install.sh",
        "//deployment/apricot_adaptive:pre_removal.sh": "/usr/share/apricot/pre_removal.sh",
        "//deployment/apricot_adaptive:network_setup.sh": "/usr/share/apricot/network_setup.sh",
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
                "//application/someipd_posix:package",
                "//application/amsr_vector_fs_log_daemon:package",
                "//os/linux:package",
            ],
        ),
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
