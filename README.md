# Minerva MPU repository
This is the MPU Adaptive AUTOSAR repository for the Minerva project.

# Setting up
tbd

# Build Instructions
The current Bazel build is based on [rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc) for building
external CMake projects. The default build type is "Release".

To avoid downloading dependencies from external sources all the time, all packages are integrated into the docker
image. These dependencies are kept at `/usr/tools/bazel` inside the docker container. Read
[here](https://git.swf.daimler.com/adas/minerva_mpu_docker/-/blob/master/Readme.md) for more info on building inside
the docker container. To install these bazel dependencies outside the docker container, you can use
[this](https://git.swf.daimler.com/adas/minerva_mpu_docker/-/blob/master/collect_deps.py) script. Since the script will
download everything to `/usr/tools/bazel/`, it needs be called with sudo privileges:
```
sudo python3 collect_deps.py
```

For collecting also packages from artifactory the script shall be called with (it will ask for artifactory credentials):
```
sudo python3 collect_deps.py -d --auth_mode=prompt
```

By default everything will be installed under /usr/tools/bazel. There is a parameter do define different location,
but then also the WORKSPACE file needs to be changed.
```
sudo python3 collect_deps.py -d --auth_mode=prompt --path=<your_path>
```


## Usage
### Build different targets for x86_64 host
The x86 GCC compiler needs to be installed on your system:
```
sudo apt-get install g++
```

On Daimler Ubuntu laptops, it might be installed by default.

```
:~/minerva_mpu_adaptive$ bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_sec_cryptostack --config=x86_64_linux
```

### Build different targets for aarch64 target 
The aarch64 GCC cross-compiler needs to be installed on your system:
```
sudo apt-get install g++-aarch64-linux-gnu
```

If you are doing this on a Daimler Ubuntu system, and not inside a container, bear in mind that your toolchain may get
automatically uninstalled after 30 minutes and might need to be reinstalled. (This problem seems not be present on
Daimler laptops).

```
:~/minerva_mpu_adaptive$ bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_sec_cryptostack --config=aarch64_linux_ubuntu
```

You can use the linaro toolchain provided by Nvidia with the `minerva_mpu_docker` image:

```
:~/minerva_mpu_adaptive$ bazel build @starter_kit_adaptive_xavier//:amsr-vector-fs-sec-cryptostack --config=aarch64_linux_linaro
```

### Deploying Execution manager on AGX

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
    User username

    Host xavier-b
    HostName x41.rd.corpintra.net
    Port 4005
    User username
    ```

You will find the build product of the `minerva_mpu_adaptive_filesystem` target at:
`bazel-out/aarch64-fastbuild/bin/minerva_mpu_adaptive_filesystem.tar`. We need to copy this to the AGX (we are copying
to `xavier-a`), like so:
```
scp bazel-out/aarch64-fastbuild/bin/minerva_mpu_adaptive_filesystem.tar $USER@xavier-a:
```

Once the Copy is successful untar the .tar file in xavier-a using below command:
    ```
    tar -xvf minerva_mpu_adaptive_filesystem.tar
    ```

Then copy the contents of etc, opt and sbin folders(extracted from the .tar) to /etc/, /opt/, and /sbin/.

Change the IP address in the opt/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/etc/someip_config.json & opt/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/etc/someip_config.json to match with the IP Address of the AGX.

IP address of AGX can be found using command ip addr(right now : 10.20.1.97)

After this run the below command to run execution manager
    ```
    sudo sbin/amsr_vector_fs_em_executionmanager -a opt -m etc/machine_exec_config.json
    ```

### Linking issues with libARA.a
Currently, there is a circular linking dependency between amsr_vector_fs_communication_miunderscoresddleware and code_gen. If you
do see linking issues related to libARA.a when you try to build, you might have to build the communication middleware
target first:
```
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_communicationmiddleware --config=<your target config>
```

### Useful information
For building the debug version use `--compilation_mode=dbg`. Other useful parameters for debugging purposes are
`--verbose_failures` and `--sandbox_debug`.

Build results are under `bazel-bin`.


### Creating docker network before bazel run
The proxy and skelton applications require network to communicate. So, we need to create a docker network before doing bazel run.
Docker network can be created using below command:
```
docker network create --subnet 10.21.17.0/24 mnv0
```

### Formatting bazel files with buildifier
#### Installing
```
curl -fL "https://github.com/bazelbuild/buildtools/releases/download/3.5.0/buildifier" -o buildifier
chmod +x buildifier
sudo mv buildifier /bin/buildifier
```

#### Running
In the root of the `minerva_mpu_adaptive` repo, run:
```
buildifier -r .
```
and check for changed files with
```
git status
```
If there are no files formatted, the output of above command will be empty. Else, it will show the list of files formatted.
