#!/bin/bash

set -eux

# Change to the script directory
cd "$(dirname "$0")"

# Deployment (minerva_mpu_adaptive or apricot_adaptive
if [ $# -eq 0 ]; then
    DEPLOYMENT="minerva_mpu_adaptive"
else 
    DEPLOYMENT=$1
fi

# Output folder
OUTPUT_DIR=runtime

# Relative path to adaptive tar package
ADAPTIVE_TAR=../../../bazel-bin/deployment/$DEPLOYMENT/filesystem_tar.tar

if [ ! -f $ADAPTIVE_TAR ]; then
    echo "File $ADAPTIVE_TAR does not exist. Exiting."
    exit 0
fi

# Folder to untar the adaptive package
ADAPTIVE_ROOT=adaptive

function setup() {
    # Create output folder
    rm -rf $OUTPUT_DIR
    mkdir $OUTPUT_DIR

    # Untar the adaptive package
    rm -rf $ADAPTIVE_ROOT
    mkdir $ADAPTIVE_ROOT
    tar -xvf $ADAPTIVE_TAR -C $ADAPTIVE_ROOT
}

function create_bootfs() {
    mkifs boot.buildfile $OUTPUT_DIR/boot.ifs
    echo "[num_sectors=512K sector_size=512] /.boot/ifs=${PWD}/${OUTPUT_DIR}/boot.ifs" | mkqnx6fsimg - $OUTPUT_DIR/boot_disk.fs
    diskimage -c boot.cfg -o $OUTPUT_DIR/boot_raw.raw -b ${QNX_TARGET}/x86/boot/sys/ipl-diskpc1-nomsg
    qemu-img convert -f raw -O qcow2 $OUTPUT_DIR/boot_raw.raw $OUTPUT_DIR/boot.qcow2
}

function create_rootfs() {
    ADAPTIVE_ROOT=$ADAPTIVE_ROOT mkqnx6fsimg -D -vv root.buildfile $OUTPUT_DIR/root_disk.fs
    diskimage -c root.cfg -o $OUTPUT_DIR/root.raw
    qemu-img convert -f raw -O qcow2 $OUTPUT_DIR/root.raw $OUTPUT_DIR/root.qcow2
}

function package() {
    tar cvzf $OUTPUT_DIR/qemu_x86_64_qnx.tar $OUTPUT_DIR/root.qcow2 $OUTPUT_DIR/boot.qcow2
}

function cleanup() {
    rm -f $OUTPUT_DIR/*.fs
    rm -f $OUTPUT_DIR/*.ifs
    rm -f $OUTPUT_DIR/*.raw
}

setup
create_bootfs
create_rootfs
package
cleanup
