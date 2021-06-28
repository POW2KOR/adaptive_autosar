load("@rules_pkg//:pkg.bzl", "pkg_tar")

package(default_visibility = ["//visibility:public"])

# This filegroup is necessary so that we isolate the output group corresponding
# to the binary of the cmake_external. Otherwise, it adds a lot of noise and
# annoying stuff. Maybe we can find a better way in the future.
# To list the output groups, I used this method:
# https://stackoverflow.com/a/61282031
# More information here:
# - https://docs.bazel.build/versions/master/skylark/rules.html#requesting-output-files
# - https://github.com/bazelbuild/rules_foreign_cc/blob/d54c78ab86b40770ee19f0949db9d74a831ab9f0/tools/build_defs/framework.bzl#L400
filegroup(
    name = "app",
    srcs = ["//bsw:amsr_vector_fs_sec_cryptostack"],
    output_group = "amsr_vector_fs_sec_cryptostack_daemon",
)

filegroup(
    name = "logging_config",
    srcs = ["configs/logging_config.json"],
)

filegroup(
    name = "exec_config",
    srcs = ["configs/exec_config.json"],
)

filegroup(
    name = "daemon_config",
    srcs = ["configs/daemon_config.json"],
)

filegroup(
    name = "ksp_config",
    srcs = ["configs/ksp.json"],
)

filegroup(
    name = "predefined_slots",
    srcs = ["configs/predefined_slots"],
)

filegroup(
    name = "trusted_cert",
    srcs = ["configs/var/crypto/certs/trusted/2555437E9448E971.cer"],
)

filegroup(
    name = "untrusted_cert",
    srcs = ["configs/var/crypto/certs/untrusted/.empty"],
)

filegroup(
    name = "new_csrs",
    srcs = ["configs/var/crypto/csrs/new/.empty"],
)

filegroup(
    name = "pending_csrs",
    srcs = ["configs/var/crypto/csrs/pending/.empty"],
)

filegroup(
    name = "example_slots",
    srcs = ["configs/var/crypto/example_slots"],
)

filegroup(
    name = "per_slots",
    srcs = ["configs/etc"],
)

pkg_tar(
    name = "package",
    files = {
        ":app": "bin/amsr_vector_fs_sec_cryptostack_daemon",
        ":logging_config": "etc/logging_config.json",
        ":exec_config": "etc/exec_config.json",
        ":daemon_config": "etc/daemon_config.json",
        ":ksp_config": "etc/ksp.json",
        ":predefined_slots": "etc/predefined_slots",
        ":trusted_cert": "var/crypto/certs/trusted/2555437E9448E971.cer",
        ":untrusted_cert": "var/crypto/certs/untrusted/.empty",
        ":new_csrs": "var/crypto/csrs/new/.empty",
        ":pending_csrs": "var/crypto/csrs/pending/.empty",
        ":example_slots": "var/crypto/example_slots",
        # In the latest delivery the persistency related folders are created
        # outside the etc directory. It is created at the same level of sbin
        # directory. For achiving that the use of "../../" is needed.
        ":per_slots": "../../per/amsr_vector_fs_sec_cryptostack_daemon/etc",
    },
    mode = "0755",
    package_dir = "opt/amsr_vector_fs_sec_cryptostack_daemon",
)
