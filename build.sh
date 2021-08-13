#!/bin/bash

set -eux

# Create a folder to store artifacts
mkdir artifacts

function create_qemu_x86_64_qnx(){
   ./os/qnx/qemu_x86_64/build_qemu.sh
   cp os/qnx/qemu_x86_64/runtime/qemu_x86_64_qnx.tar artifacts/
}

function build(){
   TARGET=$1
   echo "Building for $TARGET.."
   bazel build //deployment/apricot_adaptive:filesystem_tar --config=$TARGET

   if [ ${TARGET} = "x86_64_qnx" ]; then
      create_qemu_x86_64_qnx
   fi

   cp bazel-bin/deployment/apricot_adaptive/filesystem_tar.tar artifacts/apricot_adaptive_filesystem_$TARGET.tar
}

build x86_64_linux
build x86_64_qnx
build aarch64_qnx
