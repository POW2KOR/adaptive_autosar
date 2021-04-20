#!/bin/bash

printf "\nSetting up .gitconfig and copying over GSEP keys\n"

cp /host/.gitconfig $HOME/.gitconfig
sed -i "s|$1|$HOME|g" $HOME/.gitconfig

mkdir -p $HOME/.ssh
cp -r /host/.ssh/gsep $HOME/.ssh

printf "Setting up bash history and bazel cache persistency permissions\n"

# We do a chown because VS Code will change the UID and GID to match the current user
sudo chown -R $UID:$UID /command_history
sudo chown -R $UID:$UID /bazel_cache

printf "\nAll done 👌\n\n"
printf "👉 Build with something like:\n\n"

printf "bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=x86_64_linux && "
printf "bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=x86_64_linux && "
printf "bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=x86_64_linux && "
printf "bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux\n\n"
