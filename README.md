# Minerva MPU repository

This is the MPU Adaptive AUTOSAR repository for the Minerva project.

## Setting up

This guide describes how to build and run both from within the docker container and outside of it. The first method is
preferred, but both are supported. See next section for more info.

### The use of docker in this repository

Currently we use docker both to build and to run our applications. Both cases are optional, but they make certain
things easier and they enable a few extra use-cases. For example, for building, it allows us to deliver all the
dependencies and tools under one package (NVIDIA Drive SDK, toolchains, Bazel dependencies) and have little
interference from Daimler IT. Believe it or not, Daimler IT uninstalls your `g++-aarch64-linux-gnu` deb package after
30 minutes. For running, this allows us to make use of docker virtual networks with custom subnets and IP address
configurations without actually affecting the developer machine configuration.

We call the docker container where we build things the `build_env` and the docker container where we run things the
`run_env`.

You can find a guide on setting up docker on Daimler Ubuntu laptops
[here](https://wiki.swf.daimler.com/display/swf/How+to+setup+docker)

### Setup to build from inside the docker container

To build inside the docker container, you should get the docker image from Artifactory and check your local settings.
The image includes all the dependencies needed, including Bazel, Bazel plugins and toolchains (for both x86 and
aarch64).

Docker images are pushed to Artifactory from a CI/CD pipeline. Please check
[SWF Artifactory](https://artifact.swf.daimler.com/list/adasdai-docker/minerva_mpu_docker/minerva_mpu/) to find a
full list.

To obtain an image, first you should log in to SWF Artifactory with your credentials:

```
docker login artifact.swf.daimler.com
```

Then pull your image:

```
docker pull artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:<commitID>
```
where `<commitID>` is the image version. We are currently targeting version `e9eaa2018a759bea4927e25dca5224cbcd0bfdec`.

### Setup to build without docker

In order to build on your host machine, you will need the following tools:

- compiler toolchains for the target platform of choice
- Bazel

Information on how to set these up is below.

#### Compiler

GCC compiler needs to be installed on your system.

**IMPORTANT NOTE:** It might happen that your local installation of compiler is removed by automated Daimler IT policy
every 30 minutes, so you need to reinstall it, or contact your system administrator and ask for policy change.

For x86_64 host:

```
sudo apt install g++
```

For aarch64 cross-compilation:

```
sudo apt install g++-aarch64-linux-gnu
```

#### Bazel

Bazel is our currently used build system. Please refer to the
[Bazel installation guide](https://docs.bazel.build/versions/master/install.html)

At the moment we use version 3.7.0.

**NOTE** Now `rules_foreign_cc` requires version 3.7.0 to be installed. Using lower versions results in error related to
platform(Windows). The reference for this issue and solution can be found
[here](https://github.com/bazelbuild/rules_foreign_cc/commit/f48ec05fed3170b8b32bbc4b6d8fd4175f8b8cff).

Bazel version 3.7.0 can be downlaoded and installed from [link](https://github.com/bazelbuild/bazel/releases/tag/3.7.0).
```
sudo dpkg -i <path to bazel_3.7.0-linux-x86_64.deb>
```

**NOTE** For now, if Bazel version 4.0.0 is used, there is an issue with custom rules formatting. To avoid this, please
add `--incompatible_restrict_string_escapes=false --incompatible_require_linker_input_cc_api=false` to
each used Bazel command.

To avoid downloading Bazel dependencies from external sources all the time, we do a one-time download and installation
to a known path. These dependencies are kept at `/usr/tools/bazel`. Bazel is configured to look for them at that path.
The docker container `build_env` already has these dependencies embedded into it. To install these Bazel dependencies,
use [this](devops/docker/scripts/collect_deps.py) script. Since the script will download everything to `/usr/tools/bazel/`,
it needs to be called with sudo privileges. The following download options are available:

```
# Download all the dependencies (Artifactory authentification needed)
sudo python3 devops/docker/scripts/collect_deps.py

# Skip the dependencies from the internet (Artifactory authentification needed)
python3 devops/docker/scripts/collect_deps.py -i

# Skip the dependencies from the Artifactory
python3 devops/docker/scripts/collect_deps.py -a
```

#### Git hooks

##### Pre-commit

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

Once enabaled, pre-commit will run before every local commit in order to suggest fixes for the checks defined in
[.pre-commit-config.yaml](./pre-commit-config.yaml)

## Build

The actual build instructions are the same, regardless if you use the `build_env` to build or not. However, if you use
the `build_env` you have to go through the extra step of entering it.

### Entering the docker `build_env`

Currently, the command to enter the `build_env` is a bit messy, but in the future this will be covered by tools and
the it will be much more simpler to use.

To enter the `build_env` docker container, run the following command:

```
docker run -it \
   --name=minerva_mpu_dev \
   --rm \
   --privileged \
   --network=host \
   -e HTTP_PROXY=$http_proxy \
   -e HTTPS_PROXY=$https_proxy \
   -e no_proxy=hksmirror.rd.corpintra.net,ubunturepo.rd.corpintra.net \
   -e SSH_AUTH_SOCK=/ssh-agent \
   -v /lib/modules/$(uname -r):/lib/modules/$(uname -r) \
   -v /dev/bus/usb:/dev/bus/usb \
   -v <REPOSITORY>:/root/workspace/minerva_mpu_adaptive \
   -v /var/run/docker.sock:/var/run/docker.sock \
   -v $SSH_AUTH_SOCK:/ssh-agent \
   --workdir /root/workspace \
   artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:<commitID>
```

where: `<REPOSITORY>` is your local path to the cloned repo, e.g.
`/lhome/$USER/workspace/minerva/minerva_mpu_adaptive/`, and `<commitID>` is container's version (it is supposed
to be the same version you've pulled during the setup from earlier).

## The actual build steps

The current Bazel build is based on [rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc) for building
external CMake projects. In particular, they are used to build the Vector BSW libraries and. Default build type for the
BSW modules is "Release".

To proceed with your build on host, change to your repository root directory and execute the following commands:

```
bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=<CONFIGURATION>
bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=<CONFIGURATION>
bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=<CONFIGURATION>
bazel build //:minerva_mpu_adaptive_filesystem --config=<CONFIGURATION>
```

where `<CONFIGURATION>` is the target toolchain configuration, e.g. (`x86_64_linux`, `aarch64_linux_ubuntu` or
`aarch64_linux_linaro`, `x86_64_qnx`). For now, you cannot skip `--config=x86_64_linux` even if you are building on
an `x86_64` host for an `x86_64` target. Skipping would lead to linking issue. This will be fixed in the future by
adding custom toolchain files for `x86_64_linux`.

**NOTE** The first three commands are needed to handle the circular dependency issue. For more information
please refer to [this](#circular-dependency-workaround) section.

For the `x86_64_qnx` toolchain to work, you need to have the `QNX_HOST` and `QNX_TARGET` set correctly in your
environment. This is usually done by running something like: `source ~/qnx/qnx700/qnxsdp-env.sh`. If these variables
are not set, then Bazel will assume the following values:

- `QNX_HOST=/opt/qnx/qnx700/host/linux/x86_64`
- `QNX_TARGET=/opt/qnx/qnx700/target/qnx7`

## Running

### Running on host with the run_env docker

The following command will allow you to run the Minerva MPU Adaptive stack inside a docker container on your
development machine. There are few dependencies that should be resolved before going ahead with the build.

#### Running Docker

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

- Enter the contaienr with `docker exec` like below. Replace `<container id>` with the id returned by the previous
step. You can also run other commands than `/bin/bash`, provided that this command has been already added to the
container.

```
docker exec -it <container id> /bin/bash
```

## Miscellaneous

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

### Circular dependency workaround

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

### Useful information

For building the debug version use `--compilation_mode=dbg`. Other useful parameters for debugging purposes are
`--verbose_failures` and `--sandbox_debug`.

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

If there are no files formatted, the output of above command will be empty. Else, it will show the list of files formatted.

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

### ssh-keys handling in Docker
During the bazel build, components need to be cloned that will require to have valid ssh keys to access swf git.
If you are using docker build environment, the docker command uses the ssh-agent to utilize your keys from the host.
The docker build environment mounts the ssh-agent socket in the build environment using the following command-line
arguments:
```
-v $SSH_AUTH_SOCK:/ssh-agent \
```

Use the following commands to add your keys to the ssh-agent and execute it:

```
eval `ssh-agent -s`
ssh-add
```

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
