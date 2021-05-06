#!/bin/bash

printf "\nSetting up read permissions for Drive OS targetfs for sudo-less image building\n"
sudo chmod -R +r /drive/drive-t186ref-linux/targetfs/
sudo find /drive/drive-t186ref-linux/targetfs/ -type d -exec chmod +x {} \;

printf "Setting up .gitconfig and copying over GSEP keys\n"

sudo cp /host/.gitconfig $HOME/.gitconfig
sed -i "s|$1|$HOME|g" $HOME/.gitconfig

mkdir -p $HOME/.ssh
sudo cp -r /host/.ssh/gsep $HOME/.ssh

printf "Setting up x509 certificates, bash history and bazel cache persistency permissions\n"

sudo chown -R $UID:$UID $HOME/.ssh

# We do a chown because VS Code will change the UID and GID to match the current user
sudo chown -R $UID:$UID /command_history
sudo chown -R $UID:$UID /bazel_cache

printf "\nAll done 👌\n\n"
printf "👉 Build with something like:\n\n"

printf "bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=x86_64_linux && "
printf "bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=x86_64_linux && "
printf "bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=x86_64_linux && "
printf "bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux\n\n"
