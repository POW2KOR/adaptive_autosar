set -e

# If this flag is set to true it will boot directly into the adaptive stack, if
# set to false, it will boot into a login prompt.
BOOT_INTO_ADAPTIVE_STACK=true

if [ ! -d "runtime" ]; then
    mkdir runtime
fi

cd runtime

if [ ! -f "kernel-build/arch/arm64/boot/Image" ]; then
    printf "Fetch and build kernel...\n"

    wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.12.tar.xz

    tar xf linux-5.12.tar.xz

    cd linux-5.12

    export ARCH=arm64
    export CROSS_COMPILE=/drive/toolchains/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
    export LOCALVERSION="-tegra"

    mkdir kernel-build
    make -C linux-5.12 O=${PWD}/kernel-build defconfig

    # Using up all the cores might lock up your machine
    CORES_FOR_LINUX_BUILD=$(expr `nproc` - 1)

    make -j$CORES_FOR_LINUX_BUILD -C linux-5.12 O=${PWD}/kernel-build
fi

printf "Preparing filesystem...\n"

virt-make-fs --format=qcow2 --type=ext4 --size=+500M /drive/drive-t186ref-linux/targetfs/ driveos.ext4.qcow2

# Setup networking
guestfish -a driveos.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd-wait-online.service /etc/systemd/system/network-online.target.wants/systemd-networkd-wait-online.service
guestfish -a driveos.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd.socket /etc/systemd/system/sockets.target.wants/systemd-networkd.socket
guestfish -a driveos.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd.service /etc/systemd/system/multi-user.target.wants/systemd-networkd.service
guestfish -a driveos.ext4.qcow2 -i ln-sf /lib/systemd/system/systemd-networkd.service /etc/systemd/system/dbus-org.freedesktop.network1.service

virt-copy-in -a driveos.ext4.qcow2 ../configs/enp0s1.network /etc/systemd/network
virt-copy-in -a driveos.ext4.qcow2 ../configs/enp0s2.network /etc/systemd/network
virt-copy-in -a driveos.ext4.qcow2 ../configs/enp0s3.network /etc/systemd/network
virt-copy-in -a driveos.ext4.qcow2 ../configs/enp0s4.network /etc/systemd/network

# Activate sshd
guestfish -a driveos.ext4.qcow2 -i rm /etc/ssh/sshd_not_to_be_run

# Disable OEM setup for NVIDIA. We automate it.
guestfish -a driveos.ext4.qcow2 -i ln-sf /lib/systemd/system/multi-user.target /lib/systemd/system/default.target

# Currently the modules are built for a different kernel than we use.
guestfish -a driveos.ext4.qcow2 -i rm-rf /lib/modules
guestfish -a driveos.ext4.qcow2 -i rm /etc/modules-load.d/modules.conf

# Clean-up and streamline initialization
guestfish -a driveos.ext4.qcow2 -i rm /etc/systemd/system/multi-user.target.wants/drive-setup.service
guestfish -a driveos.ext4.qcow2 -i rm /etc/systemd/system/multi-user.target.wants/nv_duv3.service
guestfish -a driveos.ext4.qcow2 -i rm /etc/systemd/system/multi-user.target.wants/nv_network_configure.service
guestfish -a driveos.ext4.qcow2 -i rm /etc/systemd/system/network-online.target.wants/nv_networkd_wait_online.service
guestfish -a driveos.ext4.qcow2 -i rm /etc/systemd/system/ssh.service.wants/nv_ssh_host_keys.service
guestfish -a driveos.ext4.qcow2 -i rm-rf /etc/systemd/system/tegra.target.wants

qemu-img create -b driveos.ext4.qcow2 -f qcow2 adaptive_overlay.ext4.qcow2

if [ "$BOOT_INTO_ADAPTIVE_STACK" = true ] ; then
# Install systemd service for adaptive-stack
virt-copy-in -a adaptive_overlay.ext4.qcow2 ../configs/adaptive-stack.service /lib/systemd/system/
guestfish -a adaptive_overlay.ext4.qcow2 -i ln-sf /lib/systemd/system/adaptive-stack.service /etc/systemd/system/multi-user.target.wants/adaptive-stack.service
fi

# Add the adaptive stack to the filesystem
virt-tar-in -a adaptive_overlay.ext4.qcow2 ../../../bazel-bin/minerva_mpu_adaptive_filesystem.tar /

printf "Booting...\n"

qemu-system-aarch64 \
-nographic \
-machine virt \
-cpu cortex-a53 \
-smp 4 \
-m 1024M \
-bios /usr/share/qemu-efi-aarch64/QEMU_EFI.fd \
-kernel kernel-build/arch/arm64/boot/Image \
-append "console=ttyAMA0 root=/dev/vda rw quiet" \
-drive file=adaptive_overlay.ext4.qcow2,format=qcow2,if=none,id=drive0 \
-device virtio-blk-device,drive=drive0 \
-device virtio-net-pci,netdev=net1 \
-netdev user,id=net1,net=10.1.17.0/24 \
-device virtio-net-pci,netdev=net20 \
-netdev user,id=net20,net=10.20.17.0/24 \
-device virtio-net-pci,netdev=net21 \
-netdev user,id=net21,net=10.21.17.0/24 \
-device virtio-net-pci,netdev=net127 \
-netdev user,id=net127,net=10.127.17.0/24
