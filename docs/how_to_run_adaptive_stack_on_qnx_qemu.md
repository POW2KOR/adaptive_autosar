# How to run adaptive stack on QNX QEMU

There are two ways to run the adaptive stack locally on QNX Qemu:

* [Setup to run adaptive stack locally with QNX license](#setup-to-run-adaptive-stack-locally-with-QNX-license)
* [Setup to run adaptive stack locally without QNX license](#setup-to-run-adaptive-stack-locally-with-QNX-license)

## Setup to run adaptive stack locally with QNX license

QNX license is required when builing and creating QNX image locally for running on QEMU execution environment.

### Compiler Setup

The steps below will install QNX compiler toolchain in devcontainer to build for QNX target:

1. Download QNX Software Center-Linux Hosts from myQNX account and install it in the host machine.

2. Download [QNX_SDP](https://artifact.swf.daimler.com/webapp/#/artifacts/browse/tree/General/apricotbscqal/tools/sdp/7.0.0/SDP700_EXP_Gen3_Patchset_HQX0_2_ES_5_1_20210211_Updated.tar.gz)
   from artifactory and extract it under `/home` directory

3. Open Apricot Adaptive Autosar repository and add the below lines in `.devcontainer/devcontainer.json` file under section `mounts`:

```json
    "type=bind,source=${localEnv:HOME}/.qnx,target=/home/dev/.qnx",
    "type=bind,source=${localEnv:HOME}/SDP700_EXP_Gen3_Patchset_HQX0_2_ES_5_1_20210211_Updated,target=/home/dev/qnx700"
```

The final `devcontainer.json` file will look like below :-

```json
  "mounts": [
    "type=bind,source=/dev/bus/usb,target=/dev/bus/usb",
    "type=bind,source=${localEnv:HOME}/.gitconfig,target=/host/.gitconfig",
    "type=bind,source=${localEnv:HOME}/.ssh/gsep,target=/host/.ssh/gsep",
    "type=bind,source=${localWorkspaceFolder}/.devcontainer/.bazelrc,target=/etc/bazel.bazelrc",
    "type=volume,source=mbos_adaptive_build_env_command_history,target=/command_history",
    "type=volume,source=mbos_adaptive_build_env_bazel_cache,target=/bazel_cache",
    # Below two lines are to be added :-
    "type=bind,source=${localEnv:HOME}/.qnx,target=/home/dev/.qnx",
    "type=bind,source=${localEnv:HOME}/SDP700_EXP_Gen3_Patchset_HQX0_2_ES_5_1_20210211_Updated,target=/home/dev/qnx700"
  ],
```

4. Rebuild the docker container after making changes in `devcontainer.json`

5. Execute the below command to setup `QNX_HOST` and `QNX_TARGET` correctly in devcontainer environment

```bash
source ~/qnx700/qnxsdp-env.sh
```

6. Execute `qcc` in terminal. If you get the below output it means everything is properly set-up

```bash
cc: no files to process
```

#### Troubleshoot

If you get below error after executing `qcc` in terminal, its probably because of license file not properly configured

```bash
checkout failed: Cannot find license file.
 The license files (or license server system network addresses) attempted are 
listed below.  Use LM_LICENSE_FILE to use a different license file,
 or contact your software provider for a license file.
Feature:       P10F2048
Filename:      /usr/local/flexlm/licenses/license.dat
License path:  /usr/local/flexlm/licenses/license.dat:
FlexNet Licensing error:-1,359.  System Error: 2 "No such file or directory"
For further information, refer to the FlexNet Licensing documentation,
available at "www.flexerasoftware.com".
license check failed
```

Execute below command to solve this problem:

```bash
 export LM_LICENSE_FILE=27057@sedcagse1190.emea.bg.corpintra.net`
```

### Bazel Build

Start the bazel build for QNX target :-

```bazel
 bazel build //deployment/apricot_adaptive:filesystem_tar --config=x86_64_qnx
```

### Deploy Build

The steps below will install Adaptive Autosar stack into QNX image and deploy it on Qemu Execution Environment:-

1. Execute the below command to create QNX image with adaptive autosar stack

```bash
 ./os/qnx/qemu_x86_64/build_qemu.sh
```

2. Start the Qemu by executing below command:

```bash
cd os/qnx/qemu_x86_64/ # Important!
./run_x86_64_qemu.sh
```

## Setup to run adaptive stack locally without QNX license

Without QNX license its impossible to build and create QNX image locally, but you can run in Qemu if you have the already built QNX image with AA stack.

To get a QNX image trigger a Jenkins build with required changes by creating a Merge Request as QNX license is available in CI/CD pipeline during Jenkins build.

This will create QNX image `qemu_x86_64_qnx.tar` required to start Qemu

The steps below will deploy QNX image locally on to Qemu Execution Environment:-

1. Download `qemu_x86_64_qnx.tar` file from artifactory after Jenkins build is completed successfully

2. Untar `qemu_x86_64_qnx.tar` and copy `root.qcow2` and `boot.qcow2` files to newly created `runtime` folder under `/os/qnx/qemu_x86_64/` directory

3. Start the Qemu by executing below command:

```bash
cd os/qnx/qemu_x86_64/ # Important!
./run_x86_64_qemu.sh
```

### Note : Its always suggested to get a QNX license to build & deploy QNX image locally. Only follow this method without QNX license if its utmost necessary
