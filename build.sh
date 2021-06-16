#!/bin/bash

set -eux

# Create a folder to store artifacts
mkdir artifacts

function build(){
   TARGET=$1
   echo "Building for $TARGET.."
   bazel build //:minerva_mpu_adaptive_filesystem --config=$TARGET
   cp bazel-bin/minerva_mpu_adaptive_filesystem.tar artifacts/minerva_mpu_adaptive_filesystem_$TARGET.tar
}

build x86_64_linux
build x86_64_qnx
build aarch64_qnx
