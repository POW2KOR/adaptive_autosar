# This implementation will create a rule that will be used for configuring
# the aarch64_linux ubuntu_toolchain path. The extra rule is needed in order
# to have the possibility to set the compiler path over environment variable
# The same path is used for the toolchain configuration in the
# aarch64_linux_ubuntu_toolchain_config.bzl.tpl

def _tpl(repository_ctx, tpl, substitutions = {}, out = None):
    if not out:
        out = tpl
    repository_ctx.template(
        out,
        Label("//build_env/toolchain/aarch64_linux_ubuntu_compiler:%s.tpl" % tpl),
        substitutions,
    )

def _aarch64_linux_ubuntu_toolchain_configure_impl(repository_ctx):
    if "USER_PATH" in repository_ctx.os.environ:
        aarch64_linux_ubuntu_toolchain_path = repository_ctx.os.environ["USER_PATH"]
    else:
        aarch64_linux_ubuntu_toolchain_path = "/usr"

    _tpl(repository_ctx, "aarch64_linux_ubuntu_toolchain_config.bzl", {
        "%{USER_PATH}%": aarch64_linux_ubuntu_toolchain_path,
    })

    repository_ctx.symlink(repository_ctx.attr.build_file, "BUILD")

    repository_ctx.symlink(aarch64_linux_ubuntu_toolchain_path + "/bin", "bin")
    repository_ctx.symlink(aarch64_linux_ubuntu_toolchain_path + "/lib/gcc-cross", "gcc-cross")
    repository_ctx.symlink(aarch64_linux_ubuntu_toolchain_path + "/aarch64-linux-gnu", "aarch64-linux-gnu")
    repository_ctx.symlink(aarch64_linux_ubuntu_toolchain_path + "/include", "include")

aarch64_linux_ubuntu_configure = repository_rule(
    implementation = _aarch64_linux_ubuntu_toolchain_configure_impl,
    environ = ["USER_PATH"],
    attrs = {
        "build_file": attr.label(),
    },
)
