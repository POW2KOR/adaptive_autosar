[image=0x800000]
[virtual=x86_64,bios +compress] .boot = {
    startup-x86 -vvvv -D8250..115200
    [module=aps] PATH=/proc/boot:/bin:/usr/bin:/sbin:/usr/sbin LD_LIBRARY_PATH=/proc/boot:/lib:/usr/lib:/lib/dll:/lib/dll/pci procnto-smp-instr
}

[+script] .startup-script = {

    procmgr_symlink ../../proc/boot/libc.so /usr/lib/ldqnx-64.so.2

    # slogger2 server
    display_msg "Starting slogger2 server ..."
    slogger2 -s2048k &
    waitfor /dev/slog2

    # Necessary utilities
    display_msg "Starting some common services..."
    pipe
    dumper
    random -t
    waitfor /dev/random
    mqueue
 
    #----------------------------------------------------------------------------------------------
    # Settings env for PCI server and starting PCI server
    #----------------------------------------------------------------------------------------------
    PCI_HW_MODULE=/lib/dll/pci/pci_hw-Intel_x86_APL.so
    PCI_BKWD_COMPAT_MODULE=/lib/dll/pci/pci_bkwd_compat.so
    PCI_SLOG_MODULE=/lib/dll/pci/pci_slog2.so
    PCI_DEBUG_MODULE=/lib/dll/pci/pci_debug2.so
    PCI_BASE_VERBOSITY=10

    display_msg "Starting PCI server..."
    pci-server --aspace-enable
    waitfor /dev/pci 5

    # Disk drivers
    display_msg "Starting block driver..."
    devb-eide blk cache=16M,auto=partition &
    waitfor /dev/hd1 5
    mount -t qnx6 /dev/hd1t177 /
  
    # Console and serial lines
    display_msg "Starting console driver..."
    devc-con -e -n2 &
    waitfor /dev/con1
    waitfor /dev/con2

    display_msg "Starting serial driver..."
    devc-ser8250 -e -b 115200 &
    waitfor /dev/ser1

    display_msg "Starting network..."
    sh /proc/boot/network-start.sh

    # Inetd daemon for internet services
    display_msg "Starting inetd daemon..."
    inetd

    # Remote debugging service support
    display_msg "Starting debugging services..."
    qconn

    display_msg "Starting ssh daemon..."
    ksh -c /usr/sbin/sshd

    devc-pty

    # Adaptive AUTOSAR
    display_msg "Starting Adaptive AUTOSAR services..."
    start_adaptive.sh &

    display_msg "Starting shells..."
    SYSNAME=nto
    TERM=qansi

    reopen /dev/con1
    [+session] sh &

    reopen /dev/ser1
    [+session] sh &
}

# make mkifs to fail if any of the required files is missing
# http://www.qnx.com/developers/docs/7.0.0/index.html#com.qnx.doc.neutrino.utilities/topic/m/mkifs.html#mkifs__optional
[-optional]

# Network startup script
configs/network-start.sh

# Adaptive AUTOSAR startup script
configs/start_adaptive.sh

# Shell link
[type=link] /bin/sh=/proc/boot/ksh

# Redirect console messages
[type=link] /dev/console=/dev/con1

# Logger libraries
libslog2.so
libslog2parse.so

# Shared libraries
libc.so
libm.so
libz.so
libsocket.so
libsocket.so.3
libasound.so.2

# Programs require the runtime linker (ldqnx.so) to be at a fixed location
[type=link] /usr/lib/ldqnx-64.so.2=/proc/boot/libc.so

# Added for HD support
[type=link] /usr/lib/libcam.so.2=/proc/boot/libcam.so

# PCI support
libpci.so
libpci.so.2.0
[-followlink search=${QNX_TARGET}/${PROCESSOR}] /lib/dll/pci/=lib/dll/pci

# Curses library for terminal control tasks
libncursesw.so.1

# Include the hard disk shared objects so we can access the disk
libcam.so
cam-disk.so
io-blk.so
fs-qnx6.so
fs-dos.so

# For the UDF filesystem and PCI
cam-cdrom.so
fs-udf.so

# Copy code and data for all executables after this line
[data=copy]

#--------------------------------------------------------------------------------------------------
# PCI support
#--------------------------------------------------------------------------------------------------
pci-server
pci-tool
[search=${QNX_TARGET}/etc/system/config/pci] /etc/system/config/pci/pcidatabase.com-tab_delimited.txt=pcidatabase.com-tab_delimited.txt

# General commands, console driver, shell etc.
cat
chmod
cp
devb-ahci
devb-eide
devc-con
devc-ser8250
dumper
find
grep
head
if_up
ifconfig
io-pkt-v6-hc
ksh
less
ls
mkdosfs
mount
mqueue
nicinfo
pidin
pipe
ps
random
route
slog2info
slogger2
sort
tail
sync
