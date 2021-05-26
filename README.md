# Minerva MPU repository

This is the MPU Adaptive AUTOSAR repository for the Minerva project.

## Setting up

Regardless of which of the following setup methods you use, please make sure you set up your SWF gitlab according to
[this guide](https://wiki.swf.daimler.com/display/swf/How+to+use+HTTPS+to+checkout+from+GitLab). Our scripts will assume
that you have stored your x509 client certificates in `~/.ssh/gsep`. Our development environment scripts and automation
are currently not configured to work with SSH key authentication or `ssh-agent`. If you want to contribute this
improvement, it is welcome. Once you have done this setup, you will still use the SSH clone URLs from the Gitlab web
interface, but git will internally convert these into HTTPS requests using the OAuth token and x509 client certificates.

This document describes three ways how to build and run. The first method is preferred, but all are supported. These
methods are:

* build with devcontainers, described [below](#build-with-build_env-devcontainer)
* [setup to build with plain docker](docs/setup_without_devcontainers.md#setup-to-build-with-plain-docker) instead of
devcontainers
* [setup to build without any docker](docs/setup_without_devcontainers.md#setup-to-build-without-docker) at all

### The use of docker in this repository

Currently we use docker to build applications. It is optional, but it makes certain things easier and they enable a few
extra use-cases. For example, for building, it allows us to deliver all the dependencies and tools under one package
(NVIDIA Drive SDK, toolchains, Bazel dependencies) and have little interference from Daimler IT. In the past we also
used to use docker to run as well, but began to hit issues with network and firewall configurations, as well as not
being able to run our stack in the CI pipelines.

You can find a guide on setting up docker on Daimler Ubuntu laptops
[here](https://wiki.swf.daimler.com/display/swf/How+to+setup+docker).

We call the docker container where we build things `build_env` and sometimes `devcontainer`.

The CI environment can be found [here](devops/docker/Dockerfile.build_env). The CI/CD pipeline for this repository
pushes new version of the repository to
[SWF Artifactory](https://artifact.swf.daimler.com/list/adasdai-docker/minerva_mpu_docker/minerva_mpu/) on merge. The
image includes all the dependencies needed, including Bazel, Bazel plugins and toolchains (for both x86 and aarch64).
The `devcontainer` adds [a few changes](.devcontainer/Dockerfile) on top of that but these are expected to be merged
into a single file with the CI environment soon.

### Setup credentials for SWF Artifactory Docker registry

Our main docker container registry resides in SWF artifactory. To be able to download an image, first you should log
in to SWF Artifactory with your credentials:

```
docker login artifact.swf.daimler.com
```

### Build with `build_env` devcontainer

There are multiple tools which support devcontainers:
[VS Code with the Remote Development plugin](https://code.visualstudio.com/docs/remote/containers#_getting-started)
 (preferred) or the [devc CLI tool](https://github.com/nikaro/devc).

We will only be discussing the VS Code method for now. Make sure you have the
[Remote Development plugin](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)
installed. Once this is done, open the repository with VS Code by running this command:

```
cd minerva_mpu_adaptive
code .
```

Once VS Code has started, press `Ctrl-Shift-P` and type "Focus on Containers View". Then in the top bar you will see a
`+` sign. Click on it and then select "Open Current Folder in Container View".

The first start is expected to take a long time. This is because it will fetch the base image from Artifactory, which
is currently around 25 GB. It might require your computer turned on overnight in order to finish the download.
Subsequent starts will be much quicker.

The devcontainer will set up your `git` and `ssh` inside the container to work with SWF git. This assumes you have the
environment outside the docker container already working with SWF git and that you have your x509 SWF certificates
stored in `~/.ssh/gsep`. The devcontainer is configured to run in host network mode and the proxy is configured for
you. `ssh-agent` and `gpg-agent` forwarding is handled through VS Code. Bash history and Bazel build cache is persisted
between sessions. Your user ID inside the devcontainer will be made to match the one outside the container.

## Build

The actual build instructions are the same, regardless if you use the `build_env` to build or not.

## The actual build steps

The current Bazel build is based on [rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc) for building
external CMake projects. In particular, they are used to build the Vector BSW libraries. The default build type for
the BSW modules is "Release".

To proceed with your build on host, change to your repository root directory and execute the following commands:

```
bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=<CONFIGURATION>
bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=<CONFIGURATION>

# For now we are commenting out the references for socal_for_software_update as we are not able to build the target
with latest delivery, but we're bringing it back in a future step.
# bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=<CONFIGURATION>

bazel build //:minerva_mpu_adaptive_filesystem --config=<CONFIGURATION>
```

where `<CONFIGURATION>` is the target toolchain configuration, e.g. (`x86_64_linux`, `aarch64_linux_ubuntu` or
`aarch64_linux_linaro`, `x86_64_qnx`, `aarch64_qnx`). For now, you cannot skip `--config=x86_64_linux` even if you are
building on an `x86_64` host for an `x86_64` target. Skipping would lead to linking issue. This will be fixed in the
future by adding custom toolchain files for `x86_64_linux`.

**NOTE** The first three commands are needed to handle the circular dependency issue. For more information
please refer to [this](docs/circular_dependency_workaround.md) section.

For the `x86_64_qnx` and `aarch64_qnx` toolchains to work, you need to have the `QNX_HOST` and `QNX_TARGET` set
correctly in your environment. This is usually done by running something like: `source ~/qnx/qnx700/qnxsdp-env.sh`. If
these variables are not set, then Bazel will assume the following values:

- `QNX_HOST=/opt/qnx/qnx700/host/linux/x86_64`
- `QNX_TARGET=/opt/qnx/qnx700/target/qnx7`

## Running

### Running a virtual ECU with QEMU

This method is currently known to only work with the `build_env`. This is because it needs the NVIDIA DRIVE OS Linux
files which come as part of the `build_env` container. If you would want to make this work without the
`build_env`, you would have to make sure you have the correct DRIVE OS SDK dependencies placed at `/drive`.

Our QEMU execution environment currently only support aarch64 executables. This is because it uses DRIVE OS Linux as a
base, which NVIDIA provides only for aarch64.

The execution is currently done through a script, although this will be moved back to be done through bazel in the
future.

First, make sure you built the stack using the steps above. Use the `aarch64_linux_linaro` config. This uses the DRIVE
SDK toolchain.

Then run like so:

```
cd os/linux # Important!
./run_aarch64_qemu.sh
```

On first run, the script will download and build the Linux kernel and it will also put together the DRIVE OS
Linux filesystem. Depending on your machine, this might be enough time for you to have lunch, a cake and a couple of
coffees. Luckily, subsequent runs will re-use the results from the first run, so you will only have to do this once.

If you open up the `os/linux/run_aarch64_qemu.sh` script, you will see a bunch of configurable parameters. The most
important is `BOOT_INTO_ADAPTIVE_STACK`. When it is set to true, this will cause the QEMU instance to start the Adaptive
AUTOSAR stack as soon as systemd has finished booting the system. When it is set to false, this will cause the QEMU
instance to drop to a login prompt once systemd has finished booting the system. The username is `nvidia` and password
`nvidia`. To know which command to use to start the Adaptive stack, read the `ExecStart` field from the
`os/linux/configs/adaptive-stack.service` file in this repository.

### Connecting to remote DLT

All of the applications apart from the `log-daemon` are configured to output remote DLT over TCP at IP address
`10.21.17.98` and port `49361`.

## Miscellaneous

### Pre-commit checks

We use a took called `pre-commit` for various static checks before creating a commit. To enable `pre-commit`,
after cloning the repository:

```
cd minerva_mpu_adaptive
pre-commit install
```

Once enabled, pre-commit will run before every local commit in order to suggest fixes for the checks defined in
[.pre-commit-config.yaml](./pre-commit-config.yaml). These checks are performed automatically in the CI pipeline.

### Formatting bazel files with buildifier

#### Installing buildifier

```
curl -fL "https://github.com/bazelbuild/buildtools/releases/download/3.5.0/buildifier" -o buildifier
chmod +x buildifier
sudo mv buildifier /bin/buildifier
```

#### Running buildifier

In the root of the `minerva_mpu_adaptive` repo, run:

```
buildifier -r .
```

and check for changed files with

```
git status
```

If there are no files formatted, the output of above command will be empty. Else, it will show the list of files
formatted.

### Build collectd and its plugins through bazel

collectd can be built and install binaries using:
```
bazel build //tools:build_collectd
```
The binaries are generated in `bazel-bin/tools` directory.