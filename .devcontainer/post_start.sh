#!/bin/bash

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

# We do a mknod for /dev/kvm/ to start sudo-less KVM acceleration with qemu
sudo mknod /dev/kvm c 10 $(grep '\<kvm\>' /proc/misc | cut -f 1 -d' ')
sudo chown dev:dev /dev/kvm

printf "\nAll done 👌\n\n"
printf "👉 Build with something like:\n\n"

printf "bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --config=x86_64_linux\n\n"
