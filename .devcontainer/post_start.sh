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

printf "Setup the tap5 interface for QEMU user-space networking\n"
sudo chgrp dev /dev/net/tun
sudo chmod 770 /dev/net/tun
sudo tunctl -t tap5 -u dev > /dev/null

# Add tap interface on QNX Qemu's untagged interface
sudo ifconfig tap5 172.16.10.107 netmask 255.255.0.0

printf "Clean-up vlans on tap5 interface\n"
sudo ip link show \
    | grep "tap5." \
    | awk -F ':' 'NR>1{print $2}' \
    | cut -d "@" -f1 \
    | while read -r b; \
    do \
    sudo ip link delete "$b";\
    done

printf "Creating vlans over tap5 interface\n"
# Add vlans on Host side over tap5 interface

sudo ip link add link tap5 name tap5.21 type vlan id 21
sudo ip link set up tap5.21
sudo ip addr add 10.21.17.90/16 dev tap5.21

sudo ip link add link tap5 name tap5.10 type vlan id 10
sudo ip link set up tap5.10
sudo ip addr add 10.10.1.91/16 dev tap5.10

sudo ip link add link tap5 name tap5.127  type vlan id 127
sudo ip link set up tap5.127
sudo ip addr add 10.127.1.91/16 dev tap5.127

sudo ip link add link tap5 name tap5.210 type vlan id 210
sudo ip link set up tap5.210
sudo ip addr add 10.210.220.4/16 dev tap5.210

printf "The following vlans are created:\n"
ip link show \
    | grep "tap5." \
    | awk -F ':' 'NR>1{print $2}' \
    | cut -d "@" -f1

# Activate QNX license inside the container. This license server is for developers only.
printf "Setting up the QNX license manager path\n"
echo "export LM_LICENSE_FILE=27057@sedcagse1190.emea.bg.corpintra.net" >> $HOME/.bashrc

printf "\nAll done 👌\n\n"
printf "👉 Build with something like:\n\n"

printf "bazel build //deployment/apricot_adaptive:filesystem_tar --config=x86_64_linux\n\n"
