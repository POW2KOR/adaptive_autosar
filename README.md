# Minerva MPU repository

This is the MPU Adaptive AUTOSAR repository for the Minerva project.

Apart from this document, you will find more documentation under `docs/`.

## Setting up

Regardless of which of the following setup methods you use, please make sure you set up your SWF gitlab according to
[this guide](https://wiki.swf.daimler.com/display/swf/How+to+use+HTTPS+to+checkout+from+GitLab). If you don't have the
client certificate files anymore, you can re-request them
[here](https://gsep.app.corpintra.net/helpdesk/faces/portlets/index.xhtml). Our scripts will assume that you have
stored your x509 client certificates in `~/.ssh/gsep`. Our development environment scripts and automation are currently
not configured to work with SSH key authentication or `ssh-agent`. If you want to contribute this improvement, it is
welcome. Once you have done this setup, you will still use the SSH clone URLs from the Gitlab web interface, but git
will internally convert these into HTTPS requests using the OAuth token and x509 client certificates.

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

The build will typically require more than 40-50 GB of memory because it has a high degree of parallelism. If you don't
have that much phyiscal RAM on your machine, follow
[this guide](docs/bazel_tips_and_tricks.md#increasing-the-size-of-the-swap) to increase the size of the swap.

## The actual build steps

The current Bazel build is based on [rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc) for building
external CMake projects. In particular, they are used to build the Vector BSW libraries. The default build type for
the BSW modules is "Release".

To proceed with your build on host, change to your repository root directory and execute the following commands:

```
bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --config=<CONFIGURATION>
```

where `<CONFIGURATION>` is the target toolchain configuration, e.g. (`x86_64_linux`, `aarch64_linux_ubuntu` or
`aarch64_linux_linaro`, `x86_64_qnx`, `aarch64_qnx`). For now, you cannot skip `--config=x86_64_linux` even if you are
building on an `x86_64` host for an `x86_64` target. Skipping would lead to linking issue. This will be fixed in the
future by adding custom toolchain files for `x86_64_linux`.

For the `x86_64_qnx` and `aarch64_qnx` toolchains to work, you need to have the `QNX_HOST` and `QNX_TARGET` set
correctly in your environment. This is usually done by running something like: `source ~/qnx/qnx700/qnxsdp-env.sh`. If
these variables are not set, then Bazel will assume the following values:

- `QNX_HOST=/opt/qnx/qnx700/host/linux/x86_64`
- `QNX_TARGET=/opt/qnx/qnx700/target/qnx7`

If you want to add the measurement techonology tools to the stack, call bazel with `--//:mt`.

If you want to generate a package for software update build the
`//deployment/minerva_mpu_adaptive:filesystem_update_package` target. For now, generating a software update package
requires `--config=stripped`. This limitation will be removed in the future.

## Running

### Running aarch64 virtual ECU with DRIVE OS with QEMU

This method is currently known to only work with the `build_env`. This is because it needs the NVIDIA DRIVE OS Linux
files which come as part of the `build_env` container. If you would want to make this work without the
`build_env`, you would have to make sure you have the correct DRIVE OS SDK dependencies placed at `/drive`.

Our QEMU execution environment currently supports aarch64 executables which uses Drive OS Linux  as a base, which
NVIDIA provides only for aarch64.

Alternatively, x86_64 QEMU enviroment can be brought up for tasks that are not dependable
on Nvidia Drive OS and benifit for native virtualization and KVM accleration.

The execution is currently done through a script, although this will be moved back to be done through bazel in the
future.

First, make sure you built the stack using the steps above. Use the `aarch64_linux_linaro` config. This uses the DRIVE
SDK toolchain.

Then run like so:

For aarch64 build -
```
cd os/linux # Important!
./run_aarch64_qemu.sh

```
On first run, the script will download and build the Linux kernel and it will also put together the DRIVE OS
Linux filesystem. Depending on your machine, this might be enough time for you to have lunch, a cake and a couple of
coffees. Luckily, subsequent runs will re-use the results from the first run, so you will only have to do this once.

If you open up the `os/linux/run_aarch64_qemu.sh` script, you will see a bunch of configurable parameters. The most
important is `BOOT_ADAPTIVE_STACK_TO_FOREGROUND`. When it is set to true, this will cause the QEMU instance to bind the
the Adaptive AUTOSAR stack to the main tty as soon as systemd has finished booting the system. When it is set to false,
this will cause the QEMU instance when finished bootin to drop to a login prompt and boot the Adaptive stack in the
background. The username is `nvidia` and password `nvidia`.

### Running x86_64 virtual ECU with KVM acceleration and QEMU

Alternatively, x86_64 QEMU enviroment can be brought up for tasks that are not dependable on Nvidia Drive OS and benifit
from native virtualization and KVM accleration.

For x64_64 build -
```
cd os/linux # Important!
./run_x86_64_qemu.sh

```
On first run, the script will download Ubuntu cloud image and then bazel x86_64 build for Adaptive stack is extracted into it.

Once Image boots up, you can login to the image by below credentials -
```
ubuntu login: ubuntu
Password: ubuntu

```

Alternatively, you can also ssh into the image from host with same password by below command -

```
ssh -p 10022 ubuntu@localhost

```

Adaptive stack is started in the background, check with below command -
```
sudo systemctl status adaptive-stack.service
```

### Connecting to remote DLT

All of the applications apart from the `log-daemon` are configured to output remote DLT. The connection is available
over TCP at IP address `10.21.17.98` and port `49361`.

When running a virtual ECU inside QEMU, the QEMU configuration will forward the remote DLT port to port `13490` on the
host machine. Configure the [dlt-viewer](https://github.com/GENIVI/dlt-viewer) running on your host to connect to
`127.0.0.1` port `13490` over TCP.

## Miscellaneous

You can use ssh to connect to the virtual ECU.
To connect to Qemu VM instance over ssh from host, we forward host port 10022 to guest port 22.
More information on how to set this up is [here](https://git.swf.daimler.com/adasdai/minerva_mpu_adaptive/-/blob/master/docs/setup_ssh.md)

### Build collectd and its plugins through bazel

collectd can be built and install binaries using:
```
bazel build //tools:build_collectd
```
The binaries are generated in `bazel-bin/tools` directory.

## Contributing

We support a usual merge request-based contribution flow. For now, you don't have to push the your proposal as a branch
in a personal gitlab fork. You can just push it in the main repo. However, this might change. The branch naming
conventions are covered [here](https://wiki.swf.daimler.com/display/GREEN/Naming+Conventions+for+the+branches). Please
try as much as possible to link your MRs to Jira tickets.

Before you open a merge request (MR), please check the contributor checklist below.

Unless otherwise agreed, the MR threads need to be marked as resolved by the person who opened the discussion, not by
the MR author.

If the MR is not meant to be reviewed yet, or you wish to prevent it from being merged, use the "WIP:" prefix in the
title.

The preferred case for file paths, names, targets, etc. is `underscore_case`. This is mainly due to Python and bazel.

Consider the following content for your `.vscode/settings.json`:

```json
{
    "[git-commit]": {
        "editor.rulers": [
            50,
            72
        ]
    },
    "[markdown]": {
        "editor.rulers": [120]
    },
    "files.trimTrailingWhitespace": true,
    "files.insertFinalNewline": true,
}
```

### Pre-commit checks

We use a took called `pre-commit` for various static checks before creating a commit. To enable `pre-commit`,
after cloning the repository:

```
cd minerva_mpu_adaptive
pre-commit install
```

Once enabled, pre-commit will run before every local commit in order to suggest fixes for the checks defined in
[.pre-commit-config.yaml](./pre-commit-config.yaml). These checks are performed automatically in the CI pipeline.

## Contributor checklist

The following checklist is derived from a list of common mistakes.

I, the author of a merge request, have:

* checked for typos
* updated any relevant documentation files and UML diagrams
* made sure markdown paragraphs wrap at 120 characters (not automated yet)
* made sure the automated pre-commit checks pass

If I want to preserve git history, I have:

* made sure [50](https://chris.beams.io/posts/git-commit/#limit-50)/
[72](https://chris.beams.io/posts/git-commit/#wrap-72) rule for git messages is respected (not automated yet)
* made sure git messages are [descriptive and well formed](https://chris.beams.io/posts/git-commit/)
* made sure the automated pre-commit checks pass
* made sure that if I use the apply suggestion feature in gitlab, I cleaned-up the commit log and squashed/fixed up the
modifications

Otherwise, if I want to squash the git history through gitlab, I have:

* made sure [50](https://chris.beams.io/posts/git-commit/#limit-50)/
[72](https://chris.beams.io/posts/git-commit/#wrap-72) rule for the gitlab MR title and description is respected (not
automated yet)
* made sure the MR title and description is [descriptive and well formed](https://chris.beams.io/posts/git-commit/)
