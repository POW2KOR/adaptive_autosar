[num_sectors=4194304]
[uid=0 gid=0 search=${QNX_TARGET}/x86_64]

# Basic folder structure
[uid=0 gid=0 type=dir dperms=0755] /bin

[uid=0 gid=0 type=dir dperms=0755] /etc
[uid=0 gid=0 type=dir dperms=0755] /etc/pam.d
[uid=0 gid=0 type=dir dperms=0755] /etc/ssh
[uid=0 gid=0 type=dir dperms=0755] /home
[uid=0 gid=0 type=dir dperms=0755] /lib
[uid=0 gid=0 type=dir dperms=0755] /lib/dll
[uid=0 gid=0 type=dir dperms=0755] /root
[uid=0 gid=0 type=dir dperms=0755] /sbin
[uid=0 gid=0 type=dir dperms=0755] /usr
[uid=0 gid=0 type=dir dperms=0755] /usr/bin
[uid=0 gid=0 type=dir dperms=0755] /usr/lib
[uid=0 gid=0 type=dir dperms=0755] /usr/lib/terminfo
[uid=0 gid=0 type=dir dperms=0755] /usr/lib/terminfo/a
[uid=0 gid=0 type=dir dperms=0755] /usr/lib/terminfo/q
[uid=0 gid=0 type=dir dperms=0755] /usr/lib/terminfo/v
[uid=0 gid=0 type=dir dperms=0755] /usr/lib/terminfo/x
[uid=0 gid=0 type=dir dperms=0755] /usr/libexec
[uid=0 gid=0 type=dir dperms=0755] /usr/sbin
[uid=0 gid=0 type=dir dperms=0755] /usr/share
[uid=0 gid=0 type=dir dperms=0755] /usr/share/misc
[uid=0 gid=0 type=dir dperms=1777] /tmp
[uid=0 gid=0 type=dir dperms=0755] /opt
[uid=0 gid=0 type=dir dperms=0755] /var
[uid=0 gid=0 type=dir dperms=1777] /var/run
[uid=0 gid=0 type=dir dperms=1777] /var/db
[uid=0 gid=0 type=dir dperms=0755] /var/chroot
[uid=0 gid=0 type=dir dperms=0755] /var/chroot/sshd
[uid=0 gid=0 type=dir dperms=0755] /var/log

[uid=1000 gid=1000 type=dir dperms=0755] /home/qnxuser

[prefix=bin]
bin/cat
bin/chgrp
bin/chmod
bin/chown
bin/cp
bin/dd
bin/df
bin/echo
bin/ed
bin/elvis
bin/false
bin/hostname
bin/ln
[perms=4755] bin/login
bin/ls
bin/mkdir
bin/mount
bin/mv
bin/on
bin/pwd
bin/rm
bin/secpolmonitor
bin/sed
[type=link] /bin/sh=/proc/boot/ksh
bin/slay
bin/slog2info
bin/slogger2
bin/stty
[perms=4755] bin/su
bin/sync
bin/tar
bin/true
bin/umount
bin/uname
[type=link] vi=elvis
[type=link]view=elvis
bin/waitfor
bin/aps

[perms=0644] /etc/passwd = {
root:x:0:0:Superuser:/root:/bin/sh
sshd:x:15:6:sshd:/var/chroot/sshd:/bin/false
qnxuser:x:1000:1000:QNX User:/home/qnxuser:/bin/sh
}

# Enabled Username/Password: root/root, qnxuser/qnxuser
[perms=0600] /etc/shadow = {
root::1468494669:0:0
sshd:*:1231323780:0:0
qnxuser::1468488235:0:0
}

[perms=0644] /etc/group = {
root:x:0:root
sshd:x:6:sshd
qnxuser:x:1000:qnxuser
}

[perms=0644] /etc/inetd.conf = {
# Internet services syntax:
#  <service_name> <socket_type> <proto> <flags> <user> <server_pathname> <args>
#
# QNX debug agent service
pdebug    stream    tcp    nowait    root    /usr/bin/pdebug     pdebug -
}

/etc/hosts=${QNX_TARGET}/etc/hosts

[perms=0644] /etc/services = {
pdebug  9000/tcp
}

[perms=0644] /etc/ssh/sshd_config = {
HostKey /etc/ssh/ssh_host_dsa_key
HostKey /etc/ssh/ssh_host_rsa_key
Protocol 2
PermitRootLogin yes
PermitEmptyPasswords yes
LoginGraceTime 600
Subsystem      sftp    /usr/libexec/sftp-server
}

[perms=0644] /etc/profile = {
export QNX_HOST=/
export QNX_TARGET=/
export OS_LIST=nto
export CPU_LIST=x86_64
export PATH=/proc/boot:/bin:/sbin:/usr/bin:/usr/sbin
export LD_LIBRARY_PATH=/proc/boot:/lib:/lib/dll:/lib/dll/pci:/usr/lib
export PCI_CAP_MODULE_DIR=/proc/boot
export QQNX_PHYSICAL_SCREEN_SIZE=640,480
umask 022
}

[perms=0600] /etc/ssh/ssh_host_dsa_key = {
-----BEGIN DSA PRIVATE KEY-----
MIIBuwIBAAKBgQCT3avse29osEr2mOeihb+xqTx0Pr9SoPR32Ca+1SpYXF3aMljP
XsNezlOuZGX/WKWg5gqmauNECo3Mr29+U561rvOrMywpomtCKPMt2WWlk7eDRA5E
u/3+hokRaA7Y9uHa8KsK+IPGPxaDOy9PnxtR3y8IWPP+MUNv4xUyiufz6QIVAK1m
bJU64LLg6lMKIABwCiiawqEDAoGAbIJIbOA399koABJnLF7CuyXOoQfR1VjHrMod
r1GKW8VOoOPWZYv9U56zET6CHl5iIILiTQizZAJV2VU4CrvRuk0LSikqRt73H1Mp
AiJUDmBZPB4qeLGnkH47N++guWlZZ3oz0ZaRKRbvkIddb6HlEvMCzXTMHh9NYvU6
64fqd5ICgYBmx5B7wL+OLAxJ5YQ/PHQ5HzI+wqe0OQTgH9ycABeNXtnJ1xEhtkBV
Y6kjS/ffQJIemTaL1jzkz40fjzJA4acl5bbm9HZvhww/w9sxNB8TauXrRYMzGpmg
4vRHwUeokGdm87PuL5skCpVoRmPJuyGFAC9Z8ZmN7HM0UU8PV1D/NwIVAKLXbXE+
bSAoyYMUuoDSQqHsVpUI
-----END DSA PRIVATE KEY-----
}

[perms=0644] /etc/ssh/ssh_host_dsa_key.pub = {
ssh-dss AAAAB3NzaC1kc3MAAACBAJPdq+x7b2iwSvaY56KFv7GpPHQ+v1Kg9HfYJr7VKlhcXdoyWM9ew17OU65kZf9YpaDmCqZq40QKjcyvb35TnrWu86szLCmia0Io8y3ZZaWTt4NEDkS7/f6GiRFoDtj24drwqwr4g8Y/FoM7L0+fG1HfLwhY8/4xQ2/jFTKK5/PpAAAAFQCtZmyVOuCy4OpTCiAAcAoomsKhAwAAAIBsgkhs4Df32SgAEmcsXsK7Jc6hB9HVWMesyh2vUYpbxU6g49Zli/1TnrMRPoIeXmIgguJNCLNkAlXZVTgKu9G6TQtKKSpG3vcfUykCIlQOYFk8Hip4saeQfjs376C5aVlnejPRlpEpFu+Qh11voeUS8wLNdMweH01i9Trrh+p3kgAAAIBmx5B7wL+OLAxJ5YQ/PHQ5HzI+wqe0OQTgH9ycABeNXtnJ1xEhtkBVY6kjS/ffQJIemTaL1jzkz40fjzJA4acl5bbm9HZvhww/w9sxNB8TauXrRYMzGpmg4vRHwUeokGdm87PuL5skCpVoRmPJuyGFAC9Z8ZmN7HM0UU8PV1D/Nw== ilyas@ilyas-VirtualBox
}

[perms=0600] /etc/ssh/ssh_host_rsa_key = {
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAs6kbhsUGYh7a5AKf4ReH5RvqDny0uZi479f+8fUC50GDIvDe
VDmUU2PJpjsmdMMDj8QcU/5LVSEPULx+Nxp25yd7nPtr7MJZXohQZB/ex8DLb5Tj
wnZ5XAm6oj1k3B7x7BNMQGnTFON1Bnzd10Cq+IYygyX2bS7HUcM6yrsy6fTI0ZEK
fBKeUJA2uaMYgD1PQ5VVBJisDC+dlW+uCyAr/X6JRm2iiuABJNsOth2rhYW52uAN
xAn516TrmMtv5RoFhKpCJqJ89KbnZPKlRu3JE0ynyfNOCUFu1m53tjehi+YoOiDj
r90T/XWyGecRC5SSFWcOLhNgZA/ELxSoz4mDKQIDAQABAoIBAH/mo/IN0b2IucwZ
Ejjsx5ITjU1C+mYmk4IsAxO9mZOI0BLP53eOhknXgHcXJQl6y85Njt086+Ru5LhV
eIVCEeP998KKOwsSUQ07ff/JsJAEcM++72ZBcaRUSMm3a1ZJsXCfTGmO7Pax913n
Bwd2wkCrSMqU/Bo+cyeCFRi+rEBhESjnAV1ZRgh4pTnPKZelgj/2RZ/CzRFNRZXK
IJQ8+VDJtXJLUErmOf/+nYoHkPclDv1Ha8BiJdmalWXbZqRpFZnGZ+QIDPxRmfQF
tA8E3Fv1ujHeabHOlgQboYbz8x02LprsWiK+4oJRY6hVT6mLA522dtZETfzTu4pJ
VmSqtAECgYEA6TPylzUMG54tYZiM28B9n9fx9mpn8AiMv6F+G2QcaZAEBJ7sN06a
REjxBWiitDvn9kZeQpTkjyw1kOZaX7ccTZobQjeE1UDxPCI48fden27Vms9eaCL0
DhGL2MZPiwWNPb8Kw7dWd44/DKB9dxuoro8xyqJkHEVBhSGcnV9oMZUCgYEAxTk6
fLwrMFa9LsA6kHb5fEu5HHZTQP7tMEjW7+VcLc8WDO28DKZgZkMykM4nl20jhknv
1a0jc3jdXM02s3kN56i8pGXl5uNM5jnFxXUsPzwRyxfxzkhR5nXznxk58TUAW3Zf
lB+4GL2XAjduj8J5gxTQXdAwS9b7lq3szbtGDkUCgYBIy+iMfwi6jlQIRUCjUKFm
hliH3Yt4iJK3N0hQcJ3V7hjzAFEoqqbJbiOe1p0DujeczzaZfjUi5GAMTXwkqNpy
9wpPT1lt4InthZlVHy0wg762RslnpJGe2qdXEgC+mwsOHVbU5aReSc8wt+Cyj7XG
V/jpEmxBzvS3BFkJX0D9SQKBgEo+W+0e7Oc6j+csiB9gGlUXMG0tgfPCw8lcckVG
w2efQH7Hc/YTH9D/VOa8JJ1VgX0JElcO4XyTsElCG2h+lqRxmeoNTfmX8Zftgazu
iiSX2V7p+aYdBW/LUVXAKlbKDANiUWKyehweKt2zvlQx8opM6I+YUsYJ/RXhDXb5
G8s9AoGAUqT/Rtn2eMnEwJM2Sui70sfP2/ipUArpTBZKcIcAewFw/YyFNU37mxk0
BDbVAjakwf3he9Qz2KK6OJyez74LvH2CvM8Msymx29BTpgLMxPlfaepiMab8isiA
5lR0kP9h/6tw7J4aZZves30ojMK4OQIJMN+VmMNLnTcC1SOJyc8=
-----END RSA PRIVATE KEY-----
}

[perms=0644] /etc/ssh/ssh_host_rsa_key.pub = {
ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCzqRuGxQZiHtrkAp/hF4flG+oOfLS5mLjv1/7x9QLnQYMi8N5UOZRTY8mmOyZ0wwOPxBxT/ktVIQ9QvH43GnbnJ3uc+2vswlleiFBkH97HwMtvlOPCdnlcCbqiPWTcHvHsE0xAadMU43UGfN3XQKr4hjKDJfZtLsdRwzrKuzLp9MjRkQp8Ep5QkDa5oxiAPU9DlVUEmKwML52Vb64LICv9folGbaKK4AEk2w62HauFhbna4A3ECfnXpOuYy2/lGgWEqkImonz0pudk8qVG7ckTTKfJ804JQW7Wbne2N6GL5ig6IOOv3RP9dbIZ5xELlJIVZw4uE2BkD8QvFKjPiYMp ilyas@ilyas-VirtualBox
}

[prefix=lib]
lib/libstdc++.so.6.0.25
[type=link] libstdc++.so.6=libstdc++.so.6.0.25
lib/libsocket.so.3
[type=link] libsocket.so=libsocket.so.3
lib/libtracelog.so.1
[type=link] libtracelog.so=libtracelog.so.1
lib/libcatalog.so.1

[prefix=lib/dll]
lib/dll/devnp-e1000.so
lib/dll/devnp-virtio.so
lib/dll/qcrypto-openssl.so

[prefix=sbin]
sbin/devc-pty
sbin/dhclient
sbin/dloader
sbin/ifconfig
sbin/io-pkt-v6-hc
sbin/fdisk
sbin/mkqnx6fs
sbin/mqueue
sbin/pipe
sbin/route
sbin/rtc
sbin/shutdown
sbin/sysctl
sbin/io-audio

[prefix=usr/bin]
usr/bin/awk
usr/bin/coreinfo
usr/bin/date
usr/bin/env
usr/bin/file
usr/bin/find
usr/bin/grep
usr/bin/gzip
usr/bin/id
usr/bin/ldd
usr/bin/less
[perms=4755] usr/bin/netstat
[perms=4755] usr/bin/passwd
usr/bin/pdebug
[perms=4755] usr/bin/ping
usr/bin/sleep
usr/bin/traceprinter
usr/bin/tty
usr/bin/use
usr/bin/which
usr/bin/scp
usr/bin/unzip
usr/bin/zip
usr/bin/mkfifo

[prefix=usr/lib perms=0755]
usr/lib/libexpat.so.2
[type=link] libexpat.so=libexpat.so.2

usr/lib/libcrypto.so.2.1
[type=link] libcrypto.so=libcrypto.so.2.1

usr/lib/libc++.so.1.0
[type=link] libc++.so.1=libc++.so.1.0
[type=link] libc++.so=libc++.so.1

[prefix=lib/dll]                  
lib/dll/deva-ctrl-audiopci.so
[prefix=lib/dll]
lib/dll/deva-ctrl-intel_hda.so
[prefix=lib/dll]             
lib/dll/deva-ctrl-usb.so
[prefix=lib/dll]
lib/dll/deva-mixer-ak4531.so
[prefix=lib/dll]
lib/dll/deva-mixer-hda.so


usr/lib/libicudata.so.67.1
[type=link] libicudata.so.67=libicudata.so.67.1
[type=link] libicudata.so=libicudata.so.67

usr/lib/libicui18n.so.67.1
[type=link] libicui18n.so.67=libicui18n.so.67.1
[type=link] libicui18n.so=libicui18n.so.67

usr/lib/libicuuc.so.67.1
[type=link] libicuuc.so.67=libicuuc.so.67.1
[type=link] libicuuc.so=libicuuc.so.67

usr/lib/libpam.so.2
[type=link] libpam.so=libpam.so.2

usr/lib/pam_deny.so.2
[type=link] pam_deny.so=pam_deny.so.2
usr/lib/pam_ftpusers.so.2
[type=link] pam_ftpusers.so=pam_ftpusers.so.2
usr/lib/pam_qnx.so.2
[type=link] pam_qnx.so=pam_qnx.so.2
usr/lib/pam_rootok.so.2
[type=link] pam_rootok.so=pam_rootok.so.2
usr/lib/pam_self.so.2
[type=link] pam_self.so=pam_self.so.2

usr/lib/libncursesw.so.1
[type=link] libncursesw.so=libncursesw.so.1
usr/lib/libpanelw.so.1
[type=link] libpanelw.so=libpanelw.so.1

usr/lib/libbacktrace.so.1
[type=link] libbacktrace.so=libbacktrace.so.1

usr/lib/libtraceparser.so.1
[type=link] libtraceparser.so=libtraceparser.so.1

usr/lib/libscreen.so.1
[type=link] libscreen.so=libscreen.so.1

usr/lib/libz.so.2
[type=link] libz.so=libz.so.2

usr/lib/libbz2.so.1
[type=link] libbz2.so=libbz2.so.1

usr/lib/liblzma.so.5
[type=link] liblzma.so=liblzma.so.5

usr/lib/libxml2.so.2
[type=link] libxml2.so=libxml2.so.2

usr/lib/libiconv.so.1
[type=link] libiconv.so=libiconv.so.1

usr/lib/libssl.so.2.1
[type=link] libssl.so=libssl.so.2.1

[prefix=usr/libexec]
usr/libexec/sftp-server

[prefix=usr/sbin]
usr/sbin/dumper
usr/sbin/if_up
usr/sbin/inetd
usr/sbin/nicinfo
usr/sbin/qconn
usr/sbin/random
usr/sbin/sshd
usr/sbin/tracelogger
usr/sbin/plainrsa-gen

[search=${QNX_TARGET}]

[prefix=etc/pam.d perms=0644]
etc/pam.d/login
etc/pam.d/on
etc/pam.d/passwd
etc/pam.d/su

[prefix=usr/lib/terminfo]
usr/lib/terminfo/a/ansi
usr/lib/terminfo/q/qansi
usr/lib/terminfo/q/qvt101
usr/lib/terminfo/q/qvt102
usr/lib/terminfo/v/vt100
usr/lib/terminfo/v/vt102
usr/lib/terminfo/x/xterm

[prefix=usr/share/misc]
usr/share/misc/magic

[search=${ADAPTIVE_ROOT}]

[prefix=sbin perms=0755]
sbin/amsr_vector_fs_em_executionmanager

[prefix=opt perms=0755]
opt

[prefix=etc]
etc
