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

if [ ! -f "cloud.img" ]; then
    printf "Downloading image...\n"

    img_url="https://cloud-images.ubuntu.com/releases/bionic/release/"
    img_url="${img_url}/ubuntu-18.04-server-cloudimg-amd64.img"

    wget $img_url -O cloud.img
fi

cat >user-data <<EOF
#cloud-config
password: asdfqwer
chpasswd: { expire: False }
ssh_pwauth: True
EOF

if [ ! -f "cloud.img" ]; then
    # create the disk with NoCloud data on it.
    cloud-localds user.img user-data
fi

if [ ! -f "ubuntu.img" ]; then
    # Convert the compressed qcow file downloaded to a uncompressed qcow2
    qemu-img convert -O qcow2 cloud.img cloud.img.orig

    # Create a delta disk to keep our .orig file pristine backed by 'cloud.img.orig'. All writes in the kvm instance will go to the ubuntu.img file.
    qemu-img create -f qcow2 -b cloud.img.orig ubuntu.img 20G


    printf "Preparing filesystem...\n"

    # Enable networking with systemd-networkd
    guestfish -a ubuntu.img -i ln-sf /lib/systemd/system/systemd-networkd-wait-online.service /etc/systemd/system/network-online.target.wants/systemd-networkd-wait-online.service
    guestfish -a ubuntu.img -i ln-sf /lib/systemd/system/systemd-networkd.socket /etc/systemd/system/sockets.target.wants/systemd-networkd.socket
    guestfish -a ubuntu.img -i ln-sf /lib/systemd/system/systemd-networkd.service /etc/systemd/system/multi-user.target.wants/systemd-networkd.service
    guestfish -a ubuntu.img -i ln-sf /lib/systemd/system/systemd-networkd.service /etc/systemd/system/dbus-org.freedesktop.network1.service

    # Disable OEM setup for NVIDIA. We automate it.
    guestfish -a ubuntu.img -i ln-sf /lib/systemd/system/multi-user.target /lib/systemd/system/default.target

    # Install systemd service for adaptive-stack
    SERVICE_PATHS_TO_COPY="../configs/services/adaptive-stack.service ../configs/services/enable-ipv6-loopback.service"

    if [ "$BOOT_ADAPTIVE_STACK_TO_FOREGROUND" = true ] ; then
        # If we boot to foreground, we also copy the drop-in configuration
        SERVICE_PATHS_TO_COPY="${SERVICE_PATHS_TO_COPY} ../configs/services/adaptive-stack.service.d"
    fi

    virt-copy-in -a ubuntu.img $SERVICE_PATHS_TO_COPY /lib/systemd/system/

    guestfish -a ubuntu.img -i ln-sf /lib/systemd/system/adaptive-stack.service /etc/systemd/system/multi-user.target.wants/adaptive-stack.service
    guestfish -a ubuntu.img -i ln-sf /lib/systemd/system/enable-ipv6-loopback.service /etc/systemd/system/network-online.target.wants/enable-ipv6-loopback.service

    # Configure the network interfaces
    virt-copy-in -a ubuntu.img ../configs/enp0s1.network /etc/systemd/network
    virt-copy-in -a ubuntu.img ../configs/enp0s2.network /etc/systemd/network
    virt-copy-in -a ubuntu.img ../configs/enp0s3.network /etc/systemd/network
    virt-copy-in -a ubuntu.img ../configs/enp0s4.network /etc/systemd/network
    virt-copy-in -a ubuntu.img ../configs/enp0s5.network /etc/systemd/network

    # Add the adaptive stack to the filesystem
    virt-tar-in -a ubuntu.img $PATH_TO_ADAPTIVE_TAR /
fi

printf "Booting...\n"

# The following command set up several virtual network interfaces for QEMU, but
# it also has the following port-forwarding to guest:
# - host port 10022 to guest port 22 on IP 10.21.17.98 for SSH
# - host port 13490 to guest port 49361 on IP 10.21.17.98 for remote DLT
# - host port 10023 to guest port 23 on IP 10.21.17.98 for telnet

sudo qemu-system-x86_64 -nographic -cpu host -machine accel=kvm,type=q35 -smp 4 -m 2G -drive if=virtio,format=qcow2,file=ubuntu.img -drive if=virtio,format=raw,file=user.img -device virtio-net-pci,netdev=net1 -netdev user,id=net1,net=10.1.17.0/16 -device virtio-net-pci,netdev=net20 -netdev user,id=net20,net=10.20.17.0/16 -device virtio-net-pci,netdev=net21 -netdev user,id=net21,net=10.21.17.0/24,hostfwd=tcp::13490-10.21.17.98:49361,hostfwd=tcp::10022-10.21.17.98:22,hostfwd=tcp::10023-10.21.17.98:23 -device virtio-net-pci,netdev=net127 -netdev user,id=net127,net=10.127.17.0/16 -device virtio-net-pci,netdev=net254 -netdev user,id=net254,net=169.254.18.0/16
