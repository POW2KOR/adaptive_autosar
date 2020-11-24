# Bazel CMake wrapper

The current bazel build is bazed on the rules for building external cmake:
https://github.com/bazelbuild/rules_foreign_cc
Default build type in bazel is "Release" 

## Usage
### Build different targets for x86_64 host  

The x86 GCC compiler needs to be installed on your system:
```
sudo apt-get install g++
```

On Daimler Ubuntu laptops, it might be installed by default.

```
:~/proto$ bazel build @vector_sip_aa//:amsr-vector-fs-sec-cryptostack --config=x86_64
```

### Build different targets for aarch64 target 

The aarch64 GCC cross-compiler needs to be installed on your system:
```
sudo apt-get install g++-aarch64-linux-gnu
```

If you are doing this on a Daimler Ubuntu system, and not inside a container, bear in mind that your toolchain may get
automatically uninstalled after 30 minutes and might need to be reinstalled. 

```
:~/proto$ bazel build @vector_sip_aa//:amsr-vector-fs-sec-cryptostack --config=aarch64
```

### Linking issues with libARA.a

Currently, there is a circular linking dependency between amsr-vector-fs-communication-midleware and code-gen. If you
do see linking issues related to libARA.a when you try to build, you might have to build the communication middleware
target first:
```
bazel build @vector_sip_aa//:amsr-vector-fs-communicationmiddleware --config=<your target architecture>
```

### Useful information
For buidling debug vesion use `--compilation_mode=dbg`. Other useful parameters for debugging purposes
`--verbose_failures` and `--sandbox_debug`.

Build results are under `bazel-bin` and copy the build artifacts
completely from the install directory that is output from the cmake build.
