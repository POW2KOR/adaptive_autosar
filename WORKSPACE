workspace(name = "minerva_mpu_adaptive")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("//build_env/toolchain/aarch64_linux_ubuntu_compiler:aarch64_linux_ubuntu_configure.bzl", "aarch64_linux_ubuntu_configure")
load("//build_env/toolchain/aarch64_linux_linaro_compiler:aarch64_linux_linaro_configure.bzl", "aarch64_linux_linaro_configure")

# Rule repository
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies(register_default_tools = True)

http_archive(
    name = "rules_pkg",
    sha256 = "352c090cc3d3f9a6b4e676cf42a6047c16824959b438895a76c2989c6d7c246a",
    url = "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.5/rules_pkg-0.2.5.tar.gz",
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

http_archive(
    name = "rules_python",
    sha256 = "b6d46438523a3ec0f3cead544190ee13223a52f6a6765a29eae7b7cc24cc83a0",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.1.0/rules_python-0.1.0.tar.gz",
)

aarch64_linux_ubuntu_configure(
    name = "aarch64_linux_ubuntu_compiler",
    build_file = "@//build_env/toolchain/aarch64_linux_ubuntu_compiler:aarch64_linux_ubuntu_compiler.BUILD",
)

aarch64_linux_linaro_configure(
    name = "aarch64_linux_linaro_compiler",
    build_file = "@//build_env/toolchain/aarch64_linux_linaro_compiler:aarch64_linux_linaro_compiler.BUILD",
)

http_archive(
    name = "io_bazel_rules_docker",
    sha256 = "1698624e878b0607052ae6131aa216d45ebb63871ec497f26c67455b34119c80",
    strip_prefix = "rules_docker-0.15.0",
    urls = ["https://github.com/bazelbuild/rules_docker/releases/download/v0.15.0/rules_docker-v0.15.0.tar.gz"],
)

load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)

container_repositories()

load("@io_bazel_rules_docker//repositories:deps.bzl", container_deps = "deps")

container_deps()

load("@io_bazel_rules_docker//container:container.bzl", "container_pull")

container_pull(
    name = "ubuntu_18.04",
    digest = "sha256:a7fa45fb43d471f4e66c5b53b1b9b0e02f7f1d37a889a41bbe1601fac70cb54e",
    registry = "index.docker.io",
    repository = "library/ubuntu",
    tag = "18.04",
)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

new_git_repository(
    name = "vector_sip_aa",  # bazel will create under its own cache folder in the external folder package with the specified name(e.g. external/vector_sip_aa)
    # alternative for cloning using HTTPS
    # remote = "https://git.swf.daimler.com/adas/vector_sip_aa.git",
    build_file = "@//bsw:vector_sip.BUILD",
    commit = "2dd1b86ee87e7ba28e2cf7f3b69938e9bd3c8f61",  # the commit ID that bazel will use to fetch the external repository
    init_submodules = True,
    patch_args = ["-p1"],
    patches = ["@//bsw:remove-controlpanel-symlink-in-vector-sip.patch"],
    remote = "ssh://git@git.swf.daimler.com:7999/adas/vector_sip_aa.git",
    shallow_since = "1605535330 +0100",
)

# Enable the below rule if you want to avoid cloning of repo at every run
# You need to provide the path of vector_sip_aa repo locally
'''new_local_repository(
    name = "vector_sip_aa",
    path = "/lhome/sathire/repos/temp_sip/vector_sip_aa",
    build_file = "@//bsw:vector_sip.BUILD",
)'''

http_archive(
    name = "google",
    sha256 = "aa20e0bfa275190c5dbfc64c4776c3a1cd0d1e5f8b7e48bf7f7f9a4297f5204e",
    strip_prefix = "googletest",
    url = "https://artifact.swf.daimler.com/adas/tools/gtest-framework/googletest.zip",
)

# Buildifier

# buildifier is written in Go and hence needs rules_go to be built.
# See https://github.com/bazelbuild/rules_go for the up to date setup instructions.
http_archive(
    name = "io_bazel_rules_go",
    sha256 = "d1ffd055969c8f8d431e2d439813e42326961d0942bdf734d2c95dc30c369566",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_go/releases/download/v0.24.5/rules_go-v0.24.5.tar.gz",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.24.5/rules_go-v0.24.5.tar.gz",
    ],
)

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")

go_rules_dependencies()

go_register_toolchains()

http_archive(
    name = "bazel_gazelle",
    sha256 = "b85f48fa105c4403326e9525ad2b2cc437babaa6e15a3fc0b1dbab0ab064bc7c",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.22.2/bazel-gazelle-v0.22.2.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.22.2/bazel-gazelle-v0.22.2.tar.gz",
    ],
)

load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")

gazelle_dependencies()

http_archive(
    name = "com_google_protobuf",
    strip_prefix = "protobuf-master",
    urls = ["https://github.com/protocolbuffers/protobuf/archive/master.zip"],
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

http_archive(
    name = "com_github_bazelbuild_buildtools",
    strip_prefix = "buildtools-master",
    url = "https://github.com/bazelbuild/buildtools/archive/master.zip",
)
