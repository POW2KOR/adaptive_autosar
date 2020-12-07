# Minerva MPU repository
This is the MPU Adaptive AUTOSAR repository for the Minerva project.

# Setting up
tbd

# Build Instructions
The current Bazel build is based on [rules_foreign_cc](https://github.com/bazelbuild/rules_foreign_cc) for building external CMake projects. The default build type is "Release".

## Usage
### Build different targets for x86_64 host  
The x86 GCC compiler needs to be installed on your system:
```
sudo apt-get install g++
```

On Daimler Ubuntu laptops, it might be installed by default.

```
:~/minerva_mpu_adaptive$ bazel build @vector_sip_aa//:amsr-vector-fs-sec-cryptostack --config=x86_64_linux
```

### Build different targets for aarch64 target 
The aarch64 GCC cross-compiler needs to be installed on your system:
```
sudo apt-get install g++-aarch64-linux-gnu
```

If you are doing this on a Daimler Ubuntu system, and not inside a container, bear in mind that your toolchain may get
automatically uninstalled after 30 minutes and might need to be reinstalled. (This problem seems not be present on Daimler laptops).

```
:~/minerva_mpu_adaptive$ bazel build @vector_sip_aa//:amsr-vector-fs-sec-cryptostack --config=aarch64_linux_ubuntu
```

You can use the linaro toolchain provided by Nvidia with the `minerva_mpu_docker` image:

```
:~/minerva_mpu_adaptive$ bazel build @vector_sip_aa//:amsr-vector-fs-sec-cryptostack --config=aarch64_linux_linaro
```

### Linking issues with libARA.a
Currently, there is a circular linking dependency between amsr-vector-fs-communication-middleware and code-gen. If you
do see linking issues related to libARA.a when you try to build, you might have to build the communication middleware
target first:
```
bazel build @vector_sip_aa//:amsr-vector-fs-communicationmiddleware --config=<your target config>
```

### Useful information
For building the debug version use `--compilation_mode=dbg`. Other useful parameters for debugging purposes are
`--verbose_failures` and `--sandbox_debug`.

Build results are under `bazel-bin`.
