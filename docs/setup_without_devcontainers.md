# Setups to build without devcontainers

There are two ways to build without devcontainers:

* [setup to build with plain docker](#setup-to-build-with-plain-docker) instead of devcontainers
* [setup to build without any docker](#setup-to-build-without-docker) at all

## Setup to build with plain docker

Make sure you have setup your login credentials for the SWF Artifactory Docker registry, as described in the
[README](../README.md#setup-credentials-for-swf-artifactory-docker-registry)

Then, simply run `./devops/scripts/enter_build_env_docker.sh`.

The first start is expected to take a long time. This is because it will fetch the base image from Artifactory, which
is currently around 25 GB. It might require your computer turned on overnight in order to finish the download.
Subsequent starts will be much quicker.

Currently the main drawback is that the UID of the user inside the container will not match the UID on the host
machine. This part is handled transparently through VS Code. For most tasks, this is not needed.

Bash command history and the bazel build cache will be persisted for you. However, you will have to do any clean-up
manually.

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

We currently use Bazel version 4.0.0 as our build system. The docker `build_env` container already has these
dependencies embedded into it. If you are using the container, then you don't need to do any other further steps. The
instructions below will show how to install Bazel and all of its dependencies.

**NOTE** `rules_foreign_cc` requires minimum Bazel version 3.7.0. If you are seeing errors related to platform, update
now. More info [here](https://github.com/bazelbuild/rules_foreign_cc/commit/f48ec05fed3170b8b32bbc4b6d8fd4175f8b8cff).

To avoid downloading Bazel dependencies from external sources all the time, we do a one-time download and installation
to a known path. The build system is currently configured to look for the dependencies under `/usr/tools/bazel`.

This download can be done using [the collect_deps.py](../devops/docker/scripts/collect_deps.py) script.

The script will download:

1. from the internet the packages based on the content of the
[tools_web.json](../devops/docker/configuration/tools_web.json) file
2. from Artifactory the packages based on the content of the [tools.json](../devops/docker/configuration/tools.json)
file.

Please follow the following steps:

```bash
cd devops/docker/

# download all the dependencies using the python script
# NOTE: when prompted enter your Artifactory credentials
python3 scripts/collect_deps.py

# copy the downloaded files to /usr/tools/bazel/
sudo mkdir -p /usr/tools/bazel/
sudo cp tools/bazel/* /usr/tools/bazel/

# optionally, you can install Bazel and its build tools
sudo dpkg -i /usr/tools/bazel/bazel_4.0.0-linux-x86_64.deb
sudo rm /usr/tools/bazel/bazel_4.0.0-linux-x86_64.deb
sudo mv /usr/tools/bazel/buildifier /usr/local/bin/
sudo mv /usr/tools/bazel/buildozer /usr/local/bin/
sudo chmod +x /usr/local/bin/buildifier /usr/local/bin/buildozer
```
