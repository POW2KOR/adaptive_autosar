#Connecting over SSH to the QEMU virtual ECU"

The following steps shall be executed after running of `./run_aarch64_qemu.sh` with `BOOT_ADAPTIVE_STACK_TO_FOREGROUND`
being set to `false`.

## On Guest system (in qemu)

Go to directory `/etc/ssh` and check that the following files exist. They are required for the ssh connection.

```
nvidia@tegra-ubuntu:~ cd /etc/ssh
nvidia@tegra-ubuntu:/etc/ssh$ ll
total 584
drwxr-xr-x  2 root root   4096 Jun 18 10:58 ./
drwxr-xr-x 75 root root   4096 Jun 18 10:29 ../
-rw-r--r--  1 root root 553122 Mar  4  2019 moduli
-rw-r--r--  1 root root   1580 Mar  4  2019 ssh_config
-rw-------  1 root root    227 Jun 18 10:58 ssh_host_ecdsa_key
-rw-r--r--  1 root root    179 Jun 18 10:58 ssh_host_ecdsa_key.pub
-rw-------  1 root root    411 Jun 18 10:58 ssh_host_ed25519_key
-rw-r--r--  1 root root     99 Jun 18 10:58 ssh_host_ed25519_key.pub
-rw-------  1 root root   1675 Jun 18 10:57 ssh_host_rsa_key
-rw-r--r--  1 root root    399 Jun 18 10:57 ssh_host_rsa_key.pub
-rw-r--r--  1 root root   3264 Mar  4  2019 sshd_config
```

Otherwise generate them via below commands -
```
sudo ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key
sudo ssh-keygen -t ecdsa -f /etc/ssh/ssh_host_ecdsa_key
sudo ssh-keygen -t ed25519 -f /etc/ssh/ssh_host_ed25519_key
```

Ssh keygen will prompt you for password. You may leave it empty.

## On Host system

```
saksinh@cmtcleu60844879:~/minerva_mpu_adaptive$ ssh -p 10022 nvidia@localhost
```

After you successfully log in, you should see the following message:
```
Welcome to Ubuntu 18.04.5 LTS (GNU/Linux 5.12.0-tegra aarch64)

nvidia@tegra-ubuntu:~$
```

## Transferring files between Host and Qemu VM

On the **host system** create the directory, which will be used for sharing files
```
mkdir /tmp/guest
```

On the **guest system (in qemu)** create another directory, which will be used for sharing files
```
mkdir /tmp/host
```

On the **host system**:

Use sshfs for mounting the directory. It might be required to install it: `sudo apt install sshfs`
```
$ sshfs  -p 10022 nvidia@localhost:/tmp/host /tmp/guest
```

Check that directory was successfully mounted
```
$ mount | grep nvidia
nvidia@localhost:/tmp/host on /tmp/guest type fuse.sshfs (rw,nosuid,nodev,relatime,user_id=365560177,group_id=2130182657)
```

Now you should be able to read and modify files that are located in `/tmp/host` in qemu via modifying files in
`/tmp/guest` in host system.
