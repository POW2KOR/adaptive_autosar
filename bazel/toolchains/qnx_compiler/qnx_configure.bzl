# This implementation will create a rule that will be used for configuring
# the qnx toolchain path. The extra rule is needed in order to have the
#possibility to set the compiler path over environment variable

def _x86_64_qnx_toolchain_configure_impl(repository_ctx):
    if "QNX_HOST" in repository_ctx.os.environ:
        x86_64_qnx_toolchain_host_path = repository_ctx.os.environ["QNX_HOST"]
    else:
        x86_64_qnx_toolchain_host_path = "/opt/qnx/qnx700/host/linux/x86_64"

    if "QNX_TARGET" in repository_ctx.os.environ:
        x86_64_qnx_toolchain_target_path = repository_ctx.os.environ["QNX_TARGET"]
    else:
        x86_64_qnx_toolchain_target_path = "/opt/qnx/qnx700/target/qnx7"

    repository_ctx.symlink(x86_64_qnx_toolchain_host_path, "qnx_host")
    repository_ctx.symlink(x86_64_qnx_toolchain_target_path, "qnx_target")

    repository_ctx.template(
        "qnx_toolchain_config.bzl",
        Label("//bazel/toolchains/qnx_compiler:qnx_toolchain_config.bzl.tpl"),
        {
            "%{HOST_PATH}%": str(repository_ctx.path("qnx_host")),
            "%{TARGET_PATH}%": str(repository_ctx.path("qnx_target")),
        },
    )

    repository_ctx.template(
        "BUILD",
        Label("//bazel/toolchains/qnx_compiler:qnx_compiler.BUILD.tpl"),
        {},
    )

x86_64_qnx_configure = repository_rule(
    implementation = _x86_64_qnx_toolchain_configure_impl,
    environ = ["QNX_HOST", "QNX_TARGET"],
    attrs = {
        "build_file": attr.label(),
    },
)
