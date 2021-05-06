#!/bin/bash

# Please keep this file in sync with .devcontainer/devcontainer.json

current_path=`dirname $(cd -P -- "$(dirname -- "$0")" && printf '%s\n' "$(pwd -P)/$(basename -- "$0")")`
repo_root=$current_path/../..

echo "Repo root is $repo_root"

cd $repo_root/.devcontainer

set -x

docker build -t minerva_mpu_build_env_image .

docker run -it \
   --privileged \
   --network=host \
   -e HTTP_PROXY=$http_proxy \
   -e http_proxy=$http_proxy \
   -e HTTPS_PROXY=$https_proxy \
   -e https_proxy=$https_proxy \
   -e NO_PROXY=$no_proxy \
   -e no_proxy=$no_proxy \
   --mount type=bind,source=$HOME/.gitconfig,target=/host/.gitconfig \
   --mount type=bind,source=$HOME/.ssh/gsep,target=/host/.ssh/gsep \
   --mount type=bind,source=$repo_root/.devcontainer/.bazelrc,target=/etc/bazel.bazelrc \
   --mount type=volume,source=minerva_mpu_build_env_command_history,target=/command_history \
   --mount type=volume,source=minerva_mpu_build_env_bazel_cache,target=/bazel_cache \
   -v $repo_root:/workspaces/minerva_mpu_adaptive \
   -v /dev/kvm:/dev/kvm \
   -v /var/run/docker.sock:/var/run/docker.sock \
   --workdir /workspaces/minerva_mpu_adaptive \
   -t minerva_mpu_build_env_image:latest \
   /bin/bash -c "/workspaces/minerva_mpu_adaptive/.devcontainer/post_start.sh $HOME; bash"
