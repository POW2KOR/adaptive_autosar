# Minerva MPU repository

This is the MPU Adaptive AUTOSAR repository for the Minerva project.

## Setting up

This guide describes three ways how to build and run. The first method is preferred, but all are supported.

* build with devcontainers, described [below](#build-with-build_env-devcontainer)
* [setup to build with plain docker](docs/setup_without_devcontainers.md#setup-to-build-with-plain-docker) instead of
devcontainers
* [setup to build without any docker](docs/setup_without_devcontainers.md#setup-to-build-without-docker) at all

### The use of docker in this repository

Currently we use docker both to build and to run our applications. Both cases are optional, but they make certain
things easier and they enable a few extra use-cases. For example, for building, it allows us to deliver all the
dependencies and tools under one package (NVIDIA Drive SDK, toolchains, Bazel dependencies) and have little
interference from Daimler IT. For running, this allows us to make use of docker virtual networks with custom subnets
and IP address configurations without actually affecting the developer machine configuration.

You can find a guide on setting up docker on Daimler Ubuntu laptops
[here](https://wiki.swf.daimler.com/display/swf/How+to+setup+docker).

We call the docker container where we build things the `build_env` and the docker container where we run things the
`run_env`.

The `build_env` is currently configured in
[this repository](https://git.swf.daimler.com/adasdai/minerva_mpu_docker/). The CI/CD pipeline for this repository
pushes new version of the repository to
[SWF Artifactory](https://artifact.swf.daimler.com/list/adasdai-docker/minerva_mpu_docker/minerva_mpu/) on merge. The
image includes all the dependencies needed, including Bazel, Bazel plugins and toolchains (for both x86 and aarch64).

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
between sessions. VS Code also has a feature where it makes sure that the user ID of the user inside the devcontainer
matches the one outside the container. The devcontainer is configured to support this feature.

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
bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=<CONFIGURATION>
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

### Running on host with the run_env docker

The following command will allow you to run the Minerva MPU Adaptive stack inside a docker container on your
development machine. There are few dependencies that should be resolved before going ahead with the build.

#### Running Docker

Before running, you will need to create a docker network configured for the subnet in the NCD. This should be a one-time
setup. Run the command below:

```
docker network create --subnet 10.21.17.0/24 mnv0
```

Then, run the application with below command:

```
bazel run //:minerva_mpu_adaptive_docker --config=<CONFIGURATION>
```

where `<CONFIGURATION>` is your configuration type, e.g. `x86_64_linux`. This should be the same configuration
you've used during the build stage.
This command invokes the rest of dependencies and launches demo application in a container.

**NOTE** There might be an issue with firewall settings which blocks pulling the Ubuntu image from Dockerhub.
For now, this might be solved by temporary disabling your firewall.

There are two modes to run, the first mode is `--//:docker_entrypoint="shell"`, which drops to a shell inside the
container, where you can run any command. The other mode is `--//:docker_entrypoint="execution_manager"`, which is also
the implicit default, configures the IP stack for the Vector BSW and then starts the execution manager.

Currently, if you enter into shell mode, you will have to setup the network stack yourself before running the
application. This is something that will be addressed in the future, but has to be done manually at the moment. For
more information, look into `minerva_mpu_adaptive/BUILD` in the `entrypoint` parameter of the target with
`name = "minerva_mpu_adaptive_docker"`. This mode is useful if you want to do quick changes/iteration without losing
your current state.

No matter what mode you are running, you can open extra terminals into the container by using the following method:

- Get the id of the container using the command below. If nothing is printed, it means your container is not running.

```
docker ps -qf "ancestor=bazel:minerva_mpu_adaptive_docker"
```

- Enter the container with `docker exec` like below. Replace `<container id>` with the id returned by the previous
step. You can also run other commands than `/bin/bash`, provided that this command has been already added to the
container.

```
docker exec -it <container id> /bin/bash
```

### Connecting to remote DLT

All of the applications apart from the `log-daemon` are configured to output remote DLT over TCP at IP address
`10.21.17.98` and port `49361`.

Sometimes, you may not be able to connect to this address. This can happen because you have multiple interfaces on your
system which have the same 10.21.17.0/24 subnet associated to them and your DLT viewer might be confused about which one
of these to use. To check this, run `ip add | grep 10.21.17.` and see if you get more than one match. If this is true,
you can use the `./tools/remove_bridge_networks.sh` script to clean up your bridge interfaces.

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
bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=aarch64_linux_ubuntu
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
bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=<CONFIGURATION>
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
