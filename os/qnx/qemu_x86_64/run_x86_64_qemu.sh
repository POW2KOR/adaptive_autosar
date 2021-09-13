#!/bin/bash

set -eux

# Path to boot disk image.
PATH_TO_BOOT_IMAGE="runtime/boot.qcow2"

# Path to root disk image.
PATH_TO_ROOT_IMAGE="runtime/root.qcow2"

# How much memory should the emulator have.
EMULATOR_MEMORY_SIZE="4G"

# How many cores is the guest permitted to use.
EMULATOR_SMP=4

function precheck() {
    echo "Checking QEMU images exist..."

    if [ ! -f ${PATH_TO_BOOT_IMAGE} ]; then
        echo "Error: QNX boot image not found (boot.qcow2)"
        exit 1
    fi

    if [ ! -f ${PATH_TO_ROOT_IMAGE} ]; then
        echo "Error: QNX root image not found (root.qcow2)"
        exit 1
    fi
}

function start_qemu() {
    echo "Starting QEMU..."

    KVM="-accel kvm -cpu host,pmu=off -enable-kvm"

    # If u have problems running qemu as non-root because of kvm,
    # Run "sudo usermod -aG kvm $(whoami)" and reboot your machine
    qemu-system-x86_64 \
    -m ${EMULATOR_MEMORY_SIZE} \
    -smp ${EMULATOR_SMP} \
    ${KVM} \
    -drive format=qcow2,file=${PATH_TO_BOOT_IMAGE} \
    -drive format=qcow2,file=${PATH_TO_ROOT_IMAGE} \
    -device virtio-net-pci,netdev=net21 \
    -netdev user,id=net21,net=10.21.17.0/24,hostfwd=tcp::13490-10.21.17.98:49361,hostfwd=tcp::10022-10.21.17.98:22,hostfwd=tcp::10023-10.21.17.98:23 \
    -nographic 
}

precheck
start_qemu
