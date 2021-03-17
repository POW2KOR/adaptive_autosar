workspace(name = "minerva_mpu_adaptive")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("//bazel/toolchains/aarch64_linux_ubuntu_compiler:aarch64_linux_ubuntu_configure.bzl", "aarch64_linux_ubuntu_configure")
load("//bazel/toolchains/aarch64_linux_linaro_compiler:aarch64_linux_linaro_configure.bzl", "aarch64_linux_linaro_configure")
load("//bazel/toolchains/x86_64_qnx_compiler:x86_64_qnx_configure.bzl", "x86_64_qnx_configure")

# To avoid downloading dependencies from external sources all the time, they
# were made part of the docker image and are loaded directly from there.

# The packages that follow are standard bazel packages needed for buidling
# the C/C++ applications and the unit tests.
http_archive(
    name = "rules_cc",
    sha256 = "1d4dbbd1e1e9b57d40bb0ade51c9e882da7658d5bfbf22bbd15b68e7879d761f",
    strip_prefix = "rules_cc-8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0",
    url = "file:///usr/tools/bazel/rules_cc.zip",
)

http_archive(
    name = "rules_java",
    sha256 = "bc81f1ba47ef5cc68ad32225c3d0e70b8c6f6077663835438da8d5733f917598",
    strip_prefix = "rules_java-7cf3cefd652008d0a64a419c34c13bdca6c8f178",
    url = "file:///usr/tools/bazel/rules_java.zip",
)

http_archive(
    name = "rules_pkg",
    sha256 = "352c090cc3d3f9a6b4e676cf42a6047c16824959b438895a76c2989c6d7c246a",
    url = "file:///usr/tools/bazel/rules_pkg-0.2.5.tar.gz",
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

http_archive(
    name = "remote_coverage_tools",
    sha256 = "cd14f1cb4559e4723e63b7e7b06d09fcc3bd7ba58d03f354cdff1439bd936a7d",
    #strip_prefix = "remote_coverage_tools",
    url = "file:///usr/tools/bazel/remote_coverage_tools.zip",
)

http_archive(
    name = "rules_foreign_cc",
    sha256 = "21177439c27c994fd9b6e04d4ed6cec79d7dbcf174649f8d70e396dd582d1c82",
    strip_prefix = "rules_foreign_cc-ed95b95affecaa3ea3bf7bab3e0ab6aa847dfb06",
    url = "file:///usr/tools/bazel/rules_foreign_cc.zip",
)

http_archive(
    name = "rules_python",
    sha256 = "b6d46438523a3ec0f3cead544190ee13223a52f6a6765a29eae7b7cc24cc83a0",
    #strip_prefix = "rules_foreign_cc-ed95b95affecaa3ea3bf7bab3e0ab6aa847dfb06",
    url = "file:///usr/tools/bazel/rules_python-0.1.0.tar.gz",
)

aarch64_linux_ubuntu_configure(
    name = "aarch64_linux_ubuntu_compiler",
    build_file = "@//bazel/toolchains/aarch64_linux_ubuntu_compiler:aarch64_linux_ubuntu_compiler.BUILD",
)

aarch64_linux_linaro_configure(
    name = "aarch64_linux_linaro_compiler",
    build_file = "@//bazel/toolchains/aarch64_linux_linaro_compiler:aarch64_linux_linaro_compiler.BUILD",
)

x86_64_qnx_configure(
    name = "x86_64_qnx_compiler",
    build_file = "@//bazel/toolchains/x86_64_qnx_compiler:x86_64_qnx_compiler.BUILD",
)

http_archive(
    name = "bazel_skylib",
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
    #strip_prefix = "rules_foreign_cc-ed95b95affecaa3ea3bf7bab3e0ab6aa847dfb06",
    url = "file:///usr/tools/bazel/bazel-skylib-1.0.3.tar.gz",
)

http_archive(
    name = "google",
    sha256 = "aa20e0bfa275190c5dbfc64c4776c3a1cd0d1e5f8b7e48bf7f7f9a4297f5204e",
    strip_prefix = "googletest",
    url = "file:///usr/tools/bazel/googletest.zip",
)

http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    url = "file:///usr/tools/bazel/rules_proto.tar.gz",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies(register_default_tools = True)

http_archive(
    name = "io_bazel_rules_docker",
    patch_args = ["-p1"],
    patches = [
        "@//:bazel/patch_to_enable_selects_in_rules_docker_entrypoints.patch",
    ],
    sha256 = "1698624e878b0607052ae6131aa216d45ebb63871ec497f26c67455b34119c80",
    strip_prefix = "rules_docker-0.15.0",
    url = "file:///usr/tools/bazel/rules_docker-v0.15.0.tar.gz",
)

#The following packages are needed by io_bazel_rules_docker to create a docker image
#These dependencies can be found whit docker started without network connection

http_archive(
    name = "io_bazel_rules_go",
    sha256 = "08c3cd71857d58af3cda759112437d9e63339ac9c6e0042add43f4d94caf632d",
    url = "file:///usr/tools/bazel/rules_go-v0.24.2.tar.gz",
)

#io_bazel_rules_go needs go_sdk during creation of a docker image. In order to
#setup the go sdk like a bazel package go_local_sdk rule will be used.
#https://github.com/bazelbuild/rules_go/blob/master/go/toolchains.rst#go-local-sdk
#The needed sdk can be found in the sdk_list in @io_bazel_rules_go/go/private/sdk_list.bzl
#The sdk is setup and the BUILD file is provided with:
#@io_bazel_rules_go/go/private/sdk.bzl

load(
    "@io_bazel_rules_go//go:deps.bzl",
    "go_local_sdk",
)

go_local_sdk(
    name = "go_sdk",
    path = "/usr/tools/bazel/go_sdk/go/",
)

#Package needed by go for code generation
http_archive(
    name = "bazel_gazelle",
    sha256 = "cdb02a887a7187ea4d5a27452311a75ed8637379a1287d8eeb952138ea485f7d",
    url = "file:///usr/tools/bazel/bazel-gazelle-v0.21.1.tar.gz",
)
# Additional go packages needed for the docker creation
# The go repositories can be found at:
#@io_bazel_rules_docker/repositories/go_repositories.bzl

load("@bazel_gazelle//:deps.bzl", "go_repository")

go_repository(
    name = "com_github_google_go_containerregistry",
    importpath = "github.com/google/go-containerregistry",
    sha256 = "3a5f9ff61b48b928ce37e9d227a581571957b3b3ad5d45d148bce5433f9c9a6c",
    strip_prefix = "google-go-containerregistry-e5f4efd",
    type = "tar.gz",
    urls = ["file:///usr/tools/bazel/google-go-containerregistry-v0.1.1-5-ge5f4efd.tar.gz"],  # v0.1.2
)

go_repository(
    name = "com_github_pkg_errors",
    importpath = "github.com/pkg/errors",
    sha256 = "208d21a7da574026f68a8c9818fa7c6ede1b514ef9e72dc733b496ddcb7792a6",
    strip_prefix = "pkg-errors-614d223",
    type = "tar.gz",
    urls = ["file:///usr/tools/bazel/pkg-errors-v0.9.1-0-g614d223.tar.gz"],  # v0.9.1
)

#The following package is also needed during the docker
#Can be found from: @io_bazel_rules_go/go/private/repositories.bzl
http_archive(
    name = "org_golang_x_tools",
    patch_args = ["-p1"],
    patches = [
        # deletegopls removes the gopls subdirectorye. It contains a nested
        # module with additional dependencies. It's not needed by rules_go.
        "@io_bazel_rules_go//third_party:org_golang_x_tools-deletegopls.patch",
        # gazelle args: -repo_root . -go_prefix golang.org/x/tools -go_naming_convention import_alias
        "@io_bazel_rules_go//third_party:org_golang_x_tools-gazelle.patch",
    ],
    sha256 = "5b330e3bd29a52c235648457e1aa899d948cb1eb90a8b5caa0ac882be75572db",
    strip_prefix = "tools-c024452afbcdebb4a0fbe1bb0eaea0d2dbff835b",
    # master, as of 2020-08-24
    urls = [
        "file:///usr/tools/bazel/c024452afbcdebb4a0fbe1bb0eaea0d2dbff835b.zip",
    ],
)

#Bazel also wants to download a puller for darwin.
#It is not clear why since this is android package
#The both pullers are defined at:@io_bazel_rules_docker/repositories/repositories.bzl

http_file(
    name = "go_puller_darwin",
    executable = True,
    sha256 = "62b405511624528ba5b2716b1b93b5591c41edeca57195efc62da14001441c44",
    urls = ["file:///usr/tools/bazel/puller-darwin-amd64"],
)

http_file(
    name = "go_puller_linux",
    executable = True,
    sha256 = "1bcbbf86972cde8448dfab770a686801c46a1739f68f1d7a5373a4f0c3954846",
    urls = ["file:///usr/tools/bazel/puller-linux-amd64"],
)

http_archive(
    name = "platforms",
    sha256 = "ae95e4bfcd9f66e9dc73a92cee0107fede74163f788e3deefe00f3aaae75c431",
    strip_prefix = "platforms-681f1ee032566aa2d443cf0335d012925d9c58d4",
    url = "file:///usr/tools/bazel/681f1ee032566aa2d443cf0335d012925d9c58d4.zip",
)

load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)

container_repositories()

load("@io_bazel_rules_docker//repositories:deps.bzl", container_deps = "deps")

container_deps()

load("@io_bazel_rules_docker//container:container.bzl", "container_pull")

#In the moment for pulling of the base docker image internet connection is needed
#Ongoing analysis to setup local docker registry

container_pull(
    name = "ubuntu_18.04",
    digest = "sha256:a7fa45fb43d471f4e66c5b53b1b9b0e02f7f1d37a889a41bbe1601fac70cb54e",
    registry = "index.docker.io",
    repository = "library/ubuntu",
    tag = "18.04",
)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

new_git_repository(
    name = "starter_kit_adaptive_xavier",  # bazel will create under its own cache folder in the external folder package with the specified name(e.g. external/starter_kit_adaptive_xavier)
    # alternative for cloning using HTTPS
    # remote = "https://git.swf.daimler.com/adasdai/starter_kit_adaptive_xavier.git",
    build_file = "@//bsw:starter_kit_adaptive_xavier.BUILD",
    commit = "379d1f0ece2724e78ea23fa9f863d8120c0457b5",  # the commit ID that bazel will use to fetch the external repository
    init_submodules = True,
    patch_args = [
        "-p1",
    ],
    patches = [
        "@//bsw:patches/add-pthread-header-to-fix-qnx.patch",
        "@//bsw:patches/add-c-headers-to-fix-qnx.patch",
        "@//bsw:patches/fix-cmake-package-exports.patch",
        "@//bsw:patches/remove-controlpanel-symlink-in-vector-sip.patch",
    ],
    remote = "ssh://git@git.swf.daimler.com:7999/adasdai/starter_kit_adaptive_xavier.git",
    shallow_since = "1607616957 +0100",
)

# Enable the below rule if you want to avoid cloning of repo at every run
# You need to provide the path of vector_sip_aa repo locally
'''new_local_repository(
    name = "starter_kit_adaptive_xavier",
    path = "<local_path_to_reposittory>",
    build_file = "@//bsw:starter_kit_adaptive_xavier.BUILD",
)'''
