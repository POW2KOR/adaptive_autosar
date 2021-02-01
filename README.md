# Minerva MPU repository
This is the MPU Adaptive AUTOSAR repository for the Minerva project.


# Setting up
There are 2 ways to build the project: build from inside the docker container or on your host. The first option is 
considered to be our main one. Both of them are covered in this manual.

Please note that even if you build on host, you still need docker to run applications.


## The use of docker in this repository

Currently we use docker both to build and to run our applications. Both cases are optional, but they make certain
things easier and they enable a few extra use-cases. For example, for building, it allows us to deliver all the
dependencies and tools under one package (NVIDIA Drive SDK, toolchains, Bazel dependencies) and have little
interference from Daimler IT. Believe it or not, Daimler IT uninstalls your `g++-aarch64-linux-gnu` deb package after
30 minutes. For running, this allows us to make use of docker virtual networks with custom subnets and IP address
configurations without actually affecting the developer machine configuration.

We call the docker container where we build things the `build_env` and the docker container where we run things the
`run_env`.

Yoy can find a guide on setting up docker on Daimler Ubuntu laptops
[here](https://wiki.swf.daimler.com/display/ADASDAI/Setup+docker)


## Setup to build from inside the docker container
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
docker pull artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:<YYYYMMDDHHMMSS>
```
where `<YYYYMMDDHHMMSS>` is the image version. We are currently targeting version `20210104191029`.


## Setup to build without docker
In order to build on your host machine, you will need the following tools:
- compiler toolchains for the target platform of choice
- Bazel

Information on how to set these up is below.


### Compiler
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


### Bazel
Bazel is our currently used build system. Please refer to the
[Bazel installation guide](https://docs.bazel.build/versions/master/install.html)

At the moment we use version 3.7.0.

**NOTE** For now, if Bazel version 4.0.0 is used, there is an issue with custom rules formatting. To avoid this, please
add `--incompatible_restrict_string_escapes=false --incompatible_require_linker_input_cc_api=false` to 
each used Bazel command.


# Build
During the build stage it is important to use the proper configuration, even if you build on your host machine. 
Please find detailed descriptions in corresponding sections.

## Build from inside the docker container
* Set up the docker network (this is a temporary workaround and probably won't be needed in future):
   ```
   docker network create --subnet 10.21.17.0/24 mnv0
   ```

* Run the docker container:
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
   artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:<YYYYMMDDHHMMSS> 
   ```
   where: `<REPOSITORY>` is your local path to the cloned repo, e.g. 
   `/lhome/$USER/workspace/minerva/minerva_mpu_adaptive/`, and `<YYYYMMDDHHMMSS>` is container's version (it is 
   supposed to be the same version you've pulled during setup).

*  Build proxy and skeleton apps using the following commands from inside the docker container:
   ```
   bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy --config=<your target config>
   bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_skeleton --config=<your target config>
   bazel build //:minerva_mpu_adaptive_filesystem --config=<CONFIGURATION>
   ```
   where `<CONFIGURATION>` is your configuration type, e.g. `x86_64_linux`. 

   **NOTE** The first two commands are needed to handle the circular dependency issue. For more information 
   please refer to [this](#circular-dependency-workaround) section.


## Build without docker
The current Bazel build is based on [rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc) for building
external CMake projects. In particular, they are used to build the Vector BSW libraries and. Default build type for the 
BSW modules is "Release".

To avoid downloading dependencies from external sources all the time, all packages are integrated into the docker image.
These dependencies are kept at `/usr/tools/bazel` inside the docker container. If you don't want to use the docker
container, to install these Bazel dependencies outside the docker container, you can use
[this](https://git.swf.daimler.com/adasdai/minerva_mpu_docker/-/blob/master/collect_deps.py) script. Since the script will
download everything to `/usr/tools/bazel/`, it needs be called with sudo privileges:
```
sudo python3 collect_deps.py
```

For collecting also packages from Artifactory, the script shall be called with `auth_mode` parameter (it will ask for
Artifactory credentials):
```
sudo python3 collect_deps.py -d --auth_mode=prompt
```

By default, everything will be installed under `/usr/tools/bazel`. It is possible to set another location,
but in such a case the WORKSPACE file needs to be changed appropriately:
```
sudo python3 collect_deps.py -d --auth_mode=prompt --path=<your_path>
```

To proceed with your build on host, change to your project repo directory and execute the following commands:
```
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy --config=<your target config>
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_skeleton --config=<your target config>
bazel build //:minerva_mpu_adaptive_filesystem --config=<CONFIGURATION>
```
where `<CONFIGURATION>` is your configuration type, e.g. `x86_64_linux`.
These commands invoke Bazel to build proxy and skeleton applications with their dependencies.

**NOTE** The first two commands are needed to handle the circular dependency issue. For more information 
please refer to [this](#circular-dependency-workaround) section.
# Running

## Running on host with the run_env docker

The following command will allow you to run the Minerva MPU Adaptive stack inside a docker container on your
development machine. The run command uses the Bazel build graph and will detect if it is necessary to build/rebuild
anything before running the stack. So you don't need to have a call a build step separately.
```
bazel run //:minerva_mpu_adaptive_docker --config=<CONFIGURATION>
```
where `<CONFIGURATION>` is your configuration type, e.g. `x86_64_linux`. This should be the same configuration
you've used during the build stage.
This command invokes the rest of dependencies and launches demo application in a container.

**NOTE** There might be an issue with firewall settings which blocks pulling the Ubuntu image from Dockerhub. 
For now, this might be solved by temporary disabling your firewall.

## Running on the AGX without docker


Install aarch64 GCC cross-compiler using below command:
```
sudo apt-get install g++-aarch64-linux-gnu
```

Build the filesystem like so:
```
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_ubuntu
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_ubuntu
bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu
```

Make sure the below content is present in `~/.ssh/config`
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

# Miscellaneous

## Circular dependency workaround
Currently, there is a circular linking dependency between `amsr_vector_fs_socal` and the generated source code for
`ara::com`. Bazel does not support circular linking dependencies. Currently, the only way to get rid of this circular
dependency is through some custom temporary targets called `amsr_vector_fs_socal_for_proxy` and
`amsr_vector_fs_socal_for_skeleton`. Whenever the generated sources for `ara::com` change (or on the first build),
these targets have to be rebuilt manually. The manual rebuild is necessary these are not explicit build dependencies in
the Bazel build system, but hard-coded path includes. 

These steps are necessary due to the circular dependency workaround. They will not be needed once Vector ships a fix in 
the SIP:
```
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy --config=<your target config>
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_skeleton --config=<your target config>
```
After that, you can initiate your actual building, because the circular dependency is worked around with the 
`@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_headers` target
and both `\\:socal_lib_for_proxy` and `\\:socal_lib_for_socal` file groups.

## Useful information
For building the debug version use `--compilation_mode=dbg`. Other useful parameters for debugging purposes are
`--verbose_failures` and `--sandbox_debug`.

Build results are under `bazel-bin`.


## Formatting bazel files with buildifier
### Installing
```
curl -fL "https://github.com/bazelbuild/buildtools/releases/download/3.5.0/buildifier" -o buildifier
chmod +x buildifier
sudo mv buildifier /bin/buildifier
```

### Running
In the root of the `minerva_mpu_adaptive` repo, run:
```
buildifier -r .
```
and check for changed files with
```
git status
```
If there are no files formatted, the output of above command will be empty. Else, it will show the list of files formatted.
