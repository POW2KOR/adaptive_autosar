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
:~/minerva_mpu_adaptive$ bazel build @starter_kit_adaptive_xavier//:amsr-vector-fs-sec-cryptostack --config=x86_64_linux
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
:~/minerva_mpu_adaptive$ bazel build @starter_kit_adaptive_xavier//:amsr-vector-fs-sec-cryptostack --config=aarch64_linux_ubuntu
```

You can use the linaro toolchain provided by Nvidia with the `minerva_mpu_docker` image:

```
:~/minerva_mpu_adaptive$ bazel build @starter_kit_adaptive_xavier//:amsr-vector-fs-sec-cryptostack --config=aarch64_linux_linaro
```

### Linking issues with libARA.a
Currently, there is a circular linking dependency between amsr-vector-fs-communication-middleware and code-gen. If you
do see linking issues related to libARA.a when you try to build, you might have to build the communication middleware
target first:
```
bazel build @starter_kit_adaptive_xavier//:amsr-vector-fs-communicationmiddleware --config=<your target config>
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
