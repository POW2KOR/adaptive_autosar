workspace(name = "apricot_adaptive")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("//bazel/toolchains/aarch64_linux_ubuntu_compiler:aarch64_linux_ubuntu_configure.bzl", "aarch64_linux_ubuntu_configure")
load("//bazel/toolchains/aarch64_linux_linaro_compiler:aarch64_linux_linaro_configure.bzl", "aarch64_linux_linaro_configure")
load("//bazel/toolchains/qnx_compiler:qnx_configure.bzl", "qnx_toolchain_configure")

# To avoid downloading dependencies from external sources all the time, they
# were made part of the docker image and are loaded directly from there.

# The packages that follow are standard bazel packages needed for buidling
# the C/C++ applications and the unit tests.
http_archive(
    name = "rules_cc",
    sha256 = "1d4dbbd1e1e9b57d40bb0ade51c9e882da7658d5bfbf22bbd15b68e7879d761f",
    strip_prefix = "rules_cc-8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/rules_cc.zip",
)

http_archive(
    name = "rules_java",
    sha256 = "bc81f1ba47ef5cc68ad32225c3d0e70b8c6f6077663835438da8d5733f917598",
    strip_prefix = "rules_java-7cf3cefd652008d0a64a419c34c13bdca6c8f178",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/rules_java.zip",
)

http_archive(
    name = "rules_pkg",
    sha256 = "352c090cc3d3f9a6b4e676cf42a6047c16824959b438895a76c2989c6d7c246a",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/rules_pkg-0.2.5.tar.gz",
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

http_archive(
    name = "remote_coverage_tools",
    sha256 = "cd14f1cb4559e4723e63b7e7b06d09fcc3bd7ba58d03f354cdff1439bd936a7d",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/coverage_output_generator-v2.5.zip",
)

http_archive(
    name = "rules_foreign_cc",
    patch_args = ["-p1"],
    patches = [
        "@//:bazel/patches/rules_foreign_cc_support_multiple_include_out_dirs.patch",
        "@//:bazel/patches/rules_foreign_cc_output_groups_for_libraries.patch",
    ],
    sha256 = "44bfeb6566f74e4e6e36acc33ee166b428d31a6f01a4f1c14056dc7d0f68c9b6",
    strip_prefix = "rules_foreign_cc-eae19778d5fe8605f0f37332a712f05d4a17dc3b",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/rules_foreign_cc.zip",
)

http_archive(
    name = "rules_python",
    sha256 = "b6d46438523a3ec0f3cead544190ee13223a52f6a6765a29eae7b7cc24cc83a0",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/rules_python-0.1.0.tar.gz",
)

aarch64_linux_ubuntu_configure(
    name = "aarch64_linux_ubuntu_compiler",
    build_file = "@//bazel/toolchains/aarch64_linux_ubuntu_compiler:aarch64_linux_ubuntu_compiler.BUILD",
)

aarch64_linux_linaro_configure(
    name = "aarch64_linux_linaro_compiler",
    build_file = "@//bazel/toolchains/aarch64_linux_linaro_compiler:aarch64_linux_linaro_compiler.BUILD",
)

qnx_toolchain_configure(
    name = "x86_64_qnx_compiler",
    arch = "x86_64",
    toolchain_prefix = "x86_64-pc",
)

qnx_toolchain_configure(
    name = "aarch64_qnx_compiler",
    arch = "aarch64",
    toolchain_prefix = "aarch64-unknown",
)

http_archive(
    name = "bazel_skylib",
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/bazel-skylib-1.0.3.tar.gz",
)

http_archive(
    name = "google",
    sha256 = "aa20e0bfa275190c5dbfc64c4776c3a1cd0d1e5f8b7e48bf7f7f9a4297f5204e",
    strip_prefix = "googletest",
    url = "https://artifact.swf.daimler.com/apricot-bin-delivery/xpf/build-tools/googletest.zip",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies(register_default_tools = True)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

# If you want to make frequent changes to the starter_kit or amsr_xavier read more in docs/bazel_tips_and_tricks.md,
# under "Try out modifications to the amsr_xavier or sda_xavier".
new_git_repository(
    name = "amsr_xavier",  # bazel will create under its own cache folder in the external folder package with the specified name(e.g. external/amsr_xavier)
    build_file = "@//bsw:amsr_xavier.BUILD",
    commit = "f950c89d4edf138add8bdee80c58085cfc9900e4", #patched_for_integration_vMB-BLuP-1.1.5.1
    remote = "ssh://git@git.swf.daimler.com:7999/autosarbas/mbos_aa/mirrors/amsr_xavier.git",
    shallow_since = "1626781203 +0200",
)

'''new_local_repository(
    name = "amsr_xavier",
    build_file = "@//bsw:amsr_xavier.BUILD",
    path = "<local_path_to_reposittory>",
)'''

new_git_repository(
    name = "sda_xavier",  # bazel will create under its own cache folder in the external folder package with the specified name(e.g. external/sda_xavier)
    build_file = "@//application/sda:sda_xavier.BUILD",
    commit = "0ef3edea01c312b634bff177851d216ae15c18bf",    #mbos/patched_for_integration_vMB-BLuP-1.1.5.0
    remote = "ssh://git@git.swf.daimler.com:7999/autosarbas/mbos_aa/mirrors/sda_xavier.git",
    shallow_since = "1625125727 +0200",
)

'''new_local_repository(
    name = "sda_xavier",
    build_file = "@//application/sda:sda_xavier.BUILD",
    path = "<local_path_to_reposittory>",
)'''

# IF Required this can be used for starter_kit. If not
# this can be removed entirely
'''new_git_repository(
    name = "starter_kit_adaptive_xavier",  # bazel will create under its own cache folder in the external folder package with the specified name(e.g. external/starter_kit_adaptive_xavier)
    build_file = "@//:application/starter_kit_adaptive_xavier.BUILD",
    commit = "cc3a30df5b6505c10904fa8ab602593115c79960",
    remote = "ssh://git@git.swf.daimler.com:7999/adasdai/starter_kit_adaptive_xavier.git",
    shallow_since = "1621327161 +0200",
)'''

'''new_local_repository(
    name = "starter_kit_adaptive_xavier",
    build_file = "@//bsw:starter_kit_adaptive_xavier.BUILD",
    path = "<local_path_to_reposittory>",
)'''

new_git_repository(
    name = "collectd_mbient",  # bazel will create under its own cache folder in the external folder package with the specified name(e.g. external/collectd_mbient)
    build_file = "@//application/x6aa_resource_monitor:collectd_mbient.BUILD",
    commit = "98b0f4b6283398815ee3165d68aa731717fd77b6",  # the commit ID that bazel will use to fetch the external repository
    init_submodules = True,
    patch_args = [
        "-p1",
    ],
    patches = [
        "@//application/x6aa_resource_monitor:remove-srcdir-prefix.patch",
    ],
    remote = "ssh://git@git.swf.daimler.com:7999/mbient/collectd.git",
    shallow_since = "1625836431 +0200",
)

'''new_local_repository(
    name = "collectd_mbient",
    build_file = "@//application/x6aa_resource_monitor:collectd_mbient.BUILD",
    path = "/workspaces/minerva_mpu_adaptive/collectd/",
)'''
