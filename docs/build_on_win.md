# Building on Windows with WSL
## Introduction

It's possible to build minerva_mpu_adaptive on a Windows machine with WSL2 installed. WSL2 stands for Windows Subsystem Linux 2. It's a fully-fledged Linux Kernel running on top of Windows, therefore it's possible to natively execute linux binaries on top of Windows.

## Installing Docker for Windows

The build will also require a Docker windows installation. After installing `Docker Desktop` using the official steps for windows, most importantly, the configuration setting `Use the WSL2 based engine` should be checked to enable executing docker commands from your favourite WSL2 distro. (note: this setting might not be available until WSL2 is installed first)

## Installing WSL2

To be able to install WSL2: the minimum supported Windows version is 1903 according to windows [docs](https://devblogs.microsoft.com/commandline/wsl-2-support-is-coming-to-windows-10-versions-1903-and-1909/) .
You can request the 1909 update manually from the IT shop by searching for "WINDOWS 10 RELEASE UPDATE 1909 (QEV111AIEGW7)"
To install WSL2 (not from the Microsoft Store), the official Microsoft [tutorial]( https://docs.microsoft.com/en-us/windows/wsl/install-win10 ) can be followed udner the `manual installation` section.
After WSL2 installaion,  you need to manually downlad your preferred distro and install it by double-clicking on the file. These steps were only tested with Ubuntu 20.04 distro.
Now, you can start a terminal to your distro by typing bash in windows search or cmd line

## Setting-up networking in your WSL2 distro

After the installation of the distro, please try `ping www.google.com` or `sudo apt update`, they will probably not work but `ping 8.8.8.8` should work.
To setup the network access for your WSL2 distro, you need to follow the following steps:

1. Create a file: /etc/wsl.conf.
2. Put the following lines in the file in order to ensure the your DNS changes do not get blown away

```
[network]
generateResolvConf = false
```

3. In a cmd window, run wsl --shutdown
4. Restart WSL2
5. Create a file: /etc/resolv.conf. If it exists, replace existing one with this new file.
6. Put the following line in the file

```
nameserver 8.8.8.8 # Or use the company DNS server
```
7. Repeat step 3 and 4. Now `sudo apt update` should work fine

## Setting up git certificates

Please follow the [tutorial](https://wiki.swf.daimler.com/display/swf/How+to+use+HTTPS+to+checkout+from+GitLab).

## Running the build

You should be able to follow the exact same steps documented in the repository main [Readme](https://git.swf.daimler.com/adasdai/minerva_mpu_adaptive/-/blob/master/README.md).

## Using the dev container

You should be also able to use the dev container method with VS code on Windows after installing the `Remote - WSL` extensions. From VS code you can select connect to WSL and open the `minerva_mpu_adpative` folder in there, it will automatically detect the container and prompt you to reopen the workspace in the dev container.



## Misc

### Resolving docker build' error: "failed to solve with frontend dockerfile.v0

It might happen that you face this issue on WSL2 only when trying to run the build script. The solution is to disable the docker build kit by typing in
```
export DOCKER_BUILDKIT=0
export COMPOSE_DOCKER_CLI_BUILD=0
```
before running the build command.

### Exporting your filesystem to an image

Since Daimler IT has the habit of deleting your WSL2 installation after updating your mahine from within the office network. You might want to [save your workspace](https://docs.microsoft.com/en-us/windows/wsl/enterprise) before taking your laptop to office using
```
wsl --export <Distro> <FileName>
```
And importing it later again with
```
wsl --import <Distro> <InstallLocation> <FileName>
```
