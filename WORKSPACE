workspace(name = "main_bazel_cmake")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("//build_env/toolchain/aarch64_compiler:aarch64_configure.bzl", "aarch64_configure")

# Rule repository
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies(register_default_tools = True)



http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.1.0/rules_python-0.1.0.tar.gz",
    sha256 = "b6d46438523a3ec0f3cead544190ee13223a52f6a6765a29eae7b7cc24cc83a0",
)

load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

load("@rules_python//python:pip.bzl", "pip_install")

pip_install(
    requirements = "@vector_sip_aa//:config/tools/ariel/requirements.txt",
)

aarch64_configure(
    name = "aarch64_compiler",
    build_file = "@//build_env/toolchain/aarch64_compiler:aarch64_compiler.BUILD",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies(register_default_tools = True)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

new_git_repository(
    name = "vector_sip_aa", # bazel will create under its own cache folder in the external folder package with the specified name(e.g. external/vector_sip_aa)  
    commit = "c627319b2dd8fad43c7363f352d9820ae8e4a67f", # the commit ID that bazel will use to fetch the external repository
    remote = "ssh://git@git.swf.daimler.com:7999/adas/vector_sip_aa.git",
    # alternative for cloning using HTTPS
    # remote = "https://git.swf.daimler.com/adas/vector_sip_aa.git",
    build_file = "@//bsw:vector_sip.BUILD",
    init_submodules = True
)

http_archive(
    name = "google",
    url = "https://artifact.swf.daimler.com/adas/tools/gtest-framework/googletest.zip",
    sha256 = "aa20e0bfa275190c5dbfc64c4776c3a1cd0d1e5f8b7e48bf7f7f9a4297f5204e",
    strip_prefix="googletest",
)
