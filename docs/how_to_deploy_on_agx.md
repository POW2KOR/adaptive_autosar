# How to deploy on AGX

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
