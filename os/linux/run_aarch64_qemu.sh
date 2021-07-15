#!/bin/bash

set -e

# If this flag is set to true the adaptive stack will bind directly to the main
# tty. If set to false, it will boot in the background.
BOOT_ADAPTIVE_STACK_TO_FOREGROUND=true

# Path to tar to include at the root of the filesystem, usually to the adaptive
# stack tar.
PATH_TO_ADAPTIVE_TAR="../../../bazel-bin/deployment/minerva_mpu_adaptive/filesystem_tar.tar"

# Extra space to add on the disk. Should be big enough to fit the unpacked tar
# from above.
EXTRA_SPACE_ON_DISK="4G"

# How much memory should the emulator have.
EMULATOR_MEMORY_SIZE="1024M"

# How many cores is the guest permitted to use.
EMULATOR_SMP=4

if [ ! -d "runtime" ]; then
    mkdir runtime
fi

cd runtime

if [ ! -f "kernel-build/arch/arm64/boot/Image" ]; then
    printf "Fetch and build kernel...\n"

    wget -c -N https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.12.tar.xz

    tar xf linux-5.12.tar.xz

    cp ../configs/minerva_qemu_defconfig linux-5.12/arch/arm64/configs

    export ARCH=arm64
    export CROSS_COMPILE=/drive/toolchains/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
    export LOCALVERSION="-tegra"

    mkdir kernel-build
    make -C linux-5.12 O=${PWD}/kernel-build minerva_qemu_defconfig

    # Using up all the cores might lock up your machine
    CORES_FOR_LINUX_BUILD=$(expr `nproc` - 1)

    make -j$CORES_FOR_LINUX_BUILD -C linux-5.12 O=${PWD}/kernel-build
fi

printf "Preparing filesystem...\n"

if [ ! -f "driveos.ext4.qcow2" ]; then
    virt-make-fs --format=qcow2 --type=ext4 --size=+$EXTRA_SPACE_ON_DISK /drive/drive-t186ref-linux/targetfs/ driveos-tmp.ext4.qcow2

    # Enable networking with systemd-networkd
    guestfish -a driveos-tmp.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd-wait-online.service /etc/systemd/system/network-online.target.wants/systemd-networkd-wait-online.service
    guestfish -a driveos-tmp.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd.socket /etc/systemd/system/sockets.target.wants/systemd-networkd.socket
    guestfish -a driveos-tmp.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd.service /etc/systemd/system/multi-user.target.wants/systemd-networkd.service
    guestfish -a driveos-tmp.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd.service /etc/systemd/system/dbus-org.freedesktop.network1.service

    # Activate sshd
    guestfish -a driveos-tmp.ext4.qcow2 -i rm /etc/ssh/sshd_not_to_be_run

    # Disable OEM setup for NVIDIA. We automate it.
    guestfish -a driveos-tmp.ext4.qcow2 -i ln-sf /lib/systemd/system/multi-user.target /lib/systemd/system/default.target

    # Currently the modules are built for a different kernel than we use.
    guestfish -a driveos-tmp.ext4.qcow2 -i rm-rf /lib/modules
    guestfish -a driveos-tmp.ext4.qcow2 -i rm /etc/modules-load.d/modules.conf

    # Clean-up and streamline initialization
    guestfish -a driveos-tmp.ext4.qcow2 -i rm /etc/systemd/system/multi-user.target.wants/drive-setup.service
    guestfish -a driveos-tmp.ext4.qcow2 -i rm /etc/systemd/system/multi-user.target.wants/nv_duv3.service
    guestfish -a driveos-tmp.ext4.qcow2 -i rm /etc/systemd/system/multi-user.target.wants/nv_network_configure.service
    guestfish -a driveos-tmp.ext4.qcow2 -i rm /etc/systemd/system/network-online.target.wants/nv_networkd_wait_online.service
    guestfish -a driveos-tmp.ext4.qcow2 -i rm /etc/systemd/system/ssh.service.wants/nv_ssh_host_keys.service
    guestfish -a driveos-tmp.ext4.qcow2 -i rm-rf /etc/systemd/system/tegra.target.wants

    mv driveos-tmp.ext4.qcow2 driveos.ext4.qcow2
fi

rm -f adaptive_overlay.ext4.qcow2
qemu-img create -b driveos.ext4.qcow2 -f qcow2 adaptive_overlay.ext4.qcow2

# Install systemd service for adaptive-stack
SERVICE_PATHS_TO_COPY="../configs/services/adaptive-stack.service ../configs/services/enable-ipv6-loopback.service"

if [ "$BOOT_ADAPTIVE_STACK_TO_FOREGROUND" = true ] ; then
    # If we boot to foreground, we also copy the drop-in configuration
    SERVICE_PATHS_TO_COPY="${SERVICE_PATHS_TO_COPY} ../configs/services/adaptive-stack.service.d"
fi

virt-copy-in -a adaptive_overlay.ext4.qcow2 $SERVICE_PATHS_TO_COPY /lib/systemd/system/

guestfish -a adaptive_overlay.ext4.qcow2 -i ln-sf /lib/systemd/system/adaptive-stack.service /etc/systemd/system/multi-user.target.wants/adaptive-stack.service
guestfish -a adaptive_overlay.ext4.qcow2 -i ln-sf /lib/systemd/system/enable-ipv6-loopback.service /etc/systemd/system/network-online.target.wants/enable-ipv6-loopback.service

# Configure the network interfaces
virt-copy-in -a adaptive_overlay.ext4.qcow2 ../configs/enp0s1.network /etc/systemd/network
virt-copy-in -a adaptive_overlay.ext4.qcow2 ../configs/enp0s2.network /etc/systemd/network
virt-copy-in -a adaptive_overlay.ext4.qcow2 ../configs/enp0s3.network /etc/systemd/network
virt-copy-in -a adaptive_overlay.ext4.qcow2 ../configs/enp0s4.network /etc/systemd/network
virt-copy-in -a adaptive_overlay.ext4.qcow2 ../configs/enp0s5.network /etc/systemd/network

# Add the adaptive stack to the filesystem
virt-tar-in -a adaptive_overlay.ext4.qcow2 $PATH_TO_ADAPTIVE_TAR /

# Add ssh keys
virt-copy-in -a adaptive_overlay.ext4.qcow2 ../configs/ssh/* /etc/ssh

printf "Booting...\n"

# The following command set up several virtual network interfaces for QEMU, but
# it also has the following port-forwarding to guest:
# - host port 10022 to guest port 22 on IP 10.21.17.98 for SSH
# - host port 13490 to guest port 49361 on IP 10.21.17.98 for remote DLT
# - host port 10023 to guest port 23 on IP 10.21.17.98 for telnet
# - host port 13400 to guest port 13400 on IP 169.254.17.7 for Socket Connection

qemu-system-aarch64 \
-nographic \
-machine virt \
-cpu cortex-a53 \
-smp $EMULATOR_SMP \
-m $EMULATOR_MEMORY_SIZE \
-bios /usr/share/qemu-efi-aarch64/QEMU_EFI.fd \
-kernel kernel-build/arch/arm64/boot/Image \
-append "console=ttyAMA0 root=/dev/vda rw quiet" \
-drive file=adaptive_overlay.ext4.qcow2,format=qcow2,if=none,id=drive0 \
-device virtio-blk-device,drive=drive0 \
-device virtio-net-pci,netdev=net1 \
-netdev user,id=net1,net=10.1.17.0/16 \
-device virtio-net-pci,netdev=net20 \
-netdev user,id=net20,net=10.20.17.0/16 \
-device virtio-net-pci,netdev=net21 \
-netdev user,id=net21,net=10.21.17.0/24,hostfwd=tcp::13490-10.21.17.98:49361,hostfwd=tcp::10022-10.21.17.98:22,hostfwd=tcp::10023-10.21.17.98:23 \
-device virtio-net-pci,netdev=net127 \
-netdev user,id=net127,net=10.127.17.0/16 \
-device virtio-net-pci,netdev=net254 \
-netdev user,id=net254,net=169.254.18.0/16,hostfwd=tcp::13400-169.254.17.7:13400
