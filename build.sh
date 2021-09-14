#!/bin/bash

set -eux

if [ ! $# -eq 0 ]
then
    ARG="${1}"
else
    ARG=""
fi

function create_qemu_x86_64_qnx(){
    ./os/qnx/qemu_x86_64/build_qemu.sh
    cp os/qnx/qemu_x86_64/runtime/qemu_x86_64_qnx.tar out/tar
}

function build(){
    TARGET=$1
    echo "Building for $TARGET.."
    bazel build //deployment/apricot_adaptive:filesystem_tar --config=$TARGET

    # Create a folder to store tar packages for CI
    if [ ! -f "out/tar" ]; then
        mkdir -p out/tar
    fi
    cp -f bazel-bin/deployment/apricot_adaptive/filesystem_tar.tar out/tar/apricot_adaptive_filesystem_$TARGET.tar

    # Untar the adaptive package for qnx-build-script if BUILD_TARGET is set
    # This var is set when building CIVIC's QNX image:
    # https://git.swf.daimler.com/apricotqal/qnx-build-script/-/blob/master/build.sh#L65
    if [ -n "${BUILD_TARGET:-}" ]; then
        rm -rf out/civic/$BUILD_TARGET
        mkdir -p out/civic/$BUILD_TARGET
        tar -xvf bazel-bin/deployment/apricot_adaptive/filesystem_tar.tar -C out/civic/$BUILD_TARGET
    fi
}

case ${ARG} in
    aarch64_qnx | sa8195 | sa8295)
        build aarch64_qnx
        ;;
    x86_64_qnx | qemu)
        build x86_64_qnx
        ;;
    x86_64_linux)
        build x86_64_linux
        ;;
    all)
        build x86_64_linux
        build aarch64_qnx
        build x86_64_qnx
        create_qemu_x86_64_qnx
        ;;
    *)
        echo "ERROR: unknown target \"${ARG}\""
        echo "Use a vaild target. Example:  ./build.sh  aarch64_qnx"
        exit 1
        ;;
esac
