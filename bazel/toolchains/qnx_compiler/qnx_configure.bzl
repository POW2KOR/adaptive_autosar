DEFAULT_QNX_TOOLCHAIN_TARGET_PATH = "/opt/qnx/qnx700/target/qnx7"
DEFAULT_QNX_TOOLCHAIN_HOST_PATH = "/opt/qnx/qnx700/host/linux/x86_64"

# This file describes the repository rule which creates our self-contained QNX
# compiler Bazel repositories. This makes use of some generic template files
# which are then expanded into the final bazel files necessary for the
# toolchain files.

def _qnx_toolchain_configure_impl(repository_ctx):
    if "QNX_HOST" in repository_ctx.os.environ:
        qnx_toolchain_host_path = repository_ctx.os.environ["QNX_HOST"]
    else:
        qnx_toolchain_host_path = DEFAULT_QNX_TOOLCHAIN_HOST_PATH

    if "QNX_TARGET" in repository_ctx.os.environ:
        qnx_toolchain_target_path = repository_ctx.os.environ["QNX_TARGET"]
    else:
        qnx_toolchain_target_path = DEFAULT_QNX_TOOLCHAIN_TARGET_PATH

    repository_ctx.symlink(qnx_toolchain_host_path, "qnx_host")
    repository_ctx.symlink(qnx_toolchain_target_path, "qnx_target")

    spec_file_path = "//bazel/toolchains/qnx_compiler:specs/{}.specs".format(repository_ctx.attr.arch)
    repository_ctx.symlink(Label(spec_file_path), "file.specs")

    # The target path for aarch64 is called aarch64le so we have to add this special case
    if repository_ctx.attr.arch == "aarch64":
        arch_for_target_path = "aarch64le"
    else:
        arch_for_target_path = repository_ctx.attr.arch

    # Bazel conventionally uses k8 as an architecture name for x86_64, so we convert
    if repository_ctx.attr.arch == "x86_64":
        target_cpu = "k8"
    else:
        target_cpu = repository_ctx.attr.arch

    repository_ctx.template(
        "qnx_toolchain_config.bzl",
        Label("//bazel/toolchains/qnx_compiler:qnx_toolchain_config.bzl.tpl"),
        {
            "%{HOST_PATH}%": str(repository_ctx.path("qnx_host")),
            "%{TARGET_PATH}%": str(repository_ctx.path("qnx_target")),
            "%{SPECS_PATH}%": str(repository_ctx.path("file.specs")),
            "%{TOOLCHAIN_PREFIX}%": repository_ctx.attr.toolchain_prefix,
            "%{ARCH}%": repository_ctx.attr.arch,
            "%{ARCH_FOR_TARGET_PATH}%": arch_for_target_path,
            "%{TARGET_CPU}%": target_cpu,
        },
    )

    repository_ctx.template(
        "BUILD",
        Label("//bazel/toolchains/qnx_compiler:qnx_compiler.BUILD.tpl"),
        {
            "%{TOOLCHAIN_PREFIX}%": repository_ctx.attr.toolchain_prefix,
            "%{ARCH}%": repository_ctx.attr.arch,
        },
    )

qnx_toolchain_configure = repository_rule(
    implementation = _qnx_toolchain_configure_impl,
    environ = ["QNX_HOST", "QNX_TARGET"],
    attrs = {
        "arch": attr.string(),
        "toolchain_prefix": attr.string(),
    },
)
