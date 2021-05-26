# Minerva MPU repository

This is the MPU Adaptive AUTOSAR repository for the Minerva project.

## Setting up

Regardless of which of the following setup methods you use, please make sure you set up your SWF gitlab according to
[this guide](https://wiki.swf.daimler.com/display/swf/How+to+use+HTTPS+to+checkout+from+GitLab). Our scripts will assume
that you have stored your x509 client certificates in `~/.ssh/gsep`. Our development environment scripts and automation
are currently not configured to work with SSH key authentication or `ssh-agent`. If you want to contribute this
improvement, it is welcome. Once you have done this setup, you will still use the SSH clone URLs from the Gitlab web
interface, but git will internally convert these into HTTPS requests using the OAuth token and x509 client certificates.

This document describes three ways how to build and run. The first method is preferred, but all are supported.

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
please refer to [this](#circular-dependency-workaround) section.

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

### Git hooks

#### Pre-commit

This repository runs git hooks using [pre-commit](https://pre-commit.com/). The following command can be used to install
pre-commit.

```
pip3 install pre-commit==2.10.1
```

To enable pre-commit after cloning the repository, the following command can be used.

```
cd minerva_mpu_adaptive
pre-commit install
```

Once enabled, pre-commit will run before every local commit in order to suggest fixes for the checks defined in
[.pre-commit-config.yaml](./pre-commit-config.yaml)


### Proxy handling in Docker

In order to allow Internet access from inside our docker containers, we need to pass to them proper
environment variables. For now, we should take care on the following settings:

- proxy settings in `~/.docker/config.json`: needed to set up access from ubuntu_18.04 image
  when it is started on host
- proxy settings which are passed with `docker run` command: needed to set up access from
  minerva_mpu_docker
- proxy settings in `BUILD` file: needed to set up access from ubuntu_18.04 image when it is started
  from inside minerva_mpu_docker container

In case of proxy settings change, please change corresponding parameters according to your build and
launch strategy.

### Build different targets for aarch64 target

The aarch64 GCC cross-compiler needs to be installed on your system:

```
sudo apt-get install g++-aarch64-linux-gnu
```

If you are doing this on a Daimler Ubuntu system, and not inside a container, bear in mind that your toolchain may get
automatically uninstalled after 30 minutes and might need to be reinstalled. (This problem seems not be present on
Daimler laptops).

```
:~/minerva_mpu_adaptive$ bazel build //bsw:amsr_vector_fs_sec_cryptostack \
--config=aarch64_linux_ubuntu
```

You can use the Linaro toolchain provided by Nvidia with the `minerva_mpu_docker` image:

```
:~/minerva_mpu_adaptive$ bazel build //bsw:amsr-vector-fs-sec-cryptostack \
--config=aarch64_linux_linaro
```

Install aarch64 GCC cross-compiler using below command:

```
sudo apt-get install g++-aarch64-linux-gnu
```

Build the filesystem like so:

```
bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_ubuntu
bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_ubuntu

# For now we are commenting out the references for socal_for_software_update as we are not able to build the target
with latest delivery, but we're bringing it back in a future step.
# bazel build //bsw:amsr_vector_fs_socal_for_software_update ---config=aarch64_linux_ubuntu

bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu
```

Make sure the below content is present in `~/.ssh/config`:

```
Host xavier-a
HostName x41.rd.corpintra.net
Port 4004

Host xavier-b
HostName x41.rd.corpintra.net
Port 4005
```

You will find the build product of the `minerva_mpu_adaptive_filesystem` target at:
`bazel-out/aarch64-fastbuild/bin/minerva_mpu_adaptive_filesystem.tar`. We need to copy this to the AGX (we are copying
to `xavier-a`), like so:

```
scp bazel-out/aarch64-fastbuild/bin/minerva_mpu_adaptive_filesystem.tar $USER@xavier-a:
```

Once the copy is successful untar the .tar file in xavier-a using below command:

```
tar -xvf minerva_mpu_adaptive_filesystem.tar
```

Then, in `./opt/someipd_posix/etc/someipd-posix.json` change the paths to be relative.

Change the IP addresses in the following files:

- `opt/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/etc/someip_config.json`
- `opt/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/etc/someip_config.json`

The IP Address of the AGX (`10.20.1.97`, can be found via `ip addr`). This is because currently the AGX is using the IP
address in the old NCD.

After this run the below command to run execution manager:

```
sudo ./sbin/amsr_vector_fs_em_executionmanager -a ./opt -m ./etc/machine_exec_config.json
```

### Known issues and fixes

#### Circular dependency workaround

Currently, there is a circular linking dependency between `amsr_vector_fs_socal` and the generated source code for
`ara::com`. Bazel does not support circular linking dependencies. Currently, the only way to get rid of this circular
dependency is through some custom temporary targets called `amsr_vector_fs_socal_for_proxy` and
`amsr_vector_fs_socal_for_skeleton`. Whenever the generated sources for `ara::com` change (or on the first build),
these targets have to be rebuilt manually. The manual rebuild is necessary these are not explicit build dependencies in
the Bazel build system, but hard-coded path includes.

These steps are necessary due to the circular dependency workaround. They will not be needed once Vector ships a fix in
the SIP:

```
bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=<CONFIGURATION>
bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=<CONFIGURATION>

# For now we are commenting out the references for socal_for_software_update as we are not able to build the target
with latest delivery, but we're bringing it back in a future step.
# bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=<CONFIGURATION>
```

After that, you can initiate your actual building, because the circular dependency is worked around with the
`//bsw:amsr_vector_fs_socal_headers` target and both `\\:socal_lib_for_proxy` and `\\:socal_lib_for_socal` file groups.

#### Workaround for the "no such package" issue

If a build without docker has beed initiated, and Bazel-generated directories present in the working directory, then
the following error might happen when Docker build container is used:

```
ERROR: Skipping '//:os': no such package 'bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_skeleton/lib':
Unable to determine the local repository for directory
/workspaces/minerva_mpu_adaptive/bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_skeleton/lib
WARNING: Target pattern parsing failed.
```

In such a case, it is needed to remove Bazel-generated directories (`bazel-bin`, `bazel-minerva_mpu_adaptive`,
`bazel-out`, `bazel-testlogs`) from host.

### Useful information

For building the debug version use `--compilation_mode=dbg`. For building binaries stripped of debug information, use
`--compilation_mode=opt`.  Other useful parameters for debugging purposes are `--verbose_failures` and `--sandbox_debug`.

Build results are under `bazel-bin`.

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

### Connection timeout issue while submodule init of gnulibs in collectd repo with VPN on

If you face connection timeout issues while submodule init of `gnulibs` in collectd repo
through `collectd_mbient` rule of WORKSPACE file, then open `~/.gitconfig` file
and add below 2 lines:
```
[url "https://git.savannah.gnu.org/git/"]
      insteadOf = git://git.savannah.gnu.org/
```

### Build collectd and its plugins through bazel

collectd can be built and install binaries using:
```
bazel build //tools:build_collectd
```
The binaries are generated in `bazel-bin/tools` directory.

### Try out modifications to the BSW or starter kit

If you want to build the stack with a modified version of the starter kit or the BSW, first clone the starter kit:

```
git clone --recurse-submodules ssh://git@git.swf.daimler.com:7999/adasdai/starter_kit_adaptive_xavier.git
```

Then do your modifications to the source. At the end you have to copy the `BUILD` file and add a `WORKSPACE` file:

```
cp minerva_mpu_adaptive/bsw/starter_kit_adaptive_xavier.BUILD <path to starter kit clone>/BUILD
echo "workspace(name = \"starter_kit_adaptive_xavier\")" > <path to starter kit clone>/WORKSPACE
```

Finally, open `.bazelrc`, and add the following line:
```
build --override_repository=starter_kit_adaptive_xavier=<path to starter kit clone>
```

Where you replace `<path to starter kit clone>` with the path to your modified starter kit
repository.
