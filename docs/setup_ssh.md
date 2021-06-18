On Guest -

Check below files needed for ssh exist.

```
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
ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key
ssh-keygen -t ecdsa -f /etc/ssh/ssh_host_ecdsa_key
ssh-keygen -t ed25519 -f /etc/ssh/ssh_host_ed25519_key
```

On Host -
```
saksinh@cmtcleu60844879:~/minerva_mpu_adaptive$ ssh -p 10022 nvidia@localhost
nvidia@localhost's password:
Welcome to Ubuntu 18.04.5 LTS (GNU/Linux 5.12.0-tegra aarch64)

nvidia@tegra-ubuntu:~$
```

To transfer files between Host and Qemu VM instance, sshfs is recommended to create a shared directory.
```
$ sshfs  -p 10022 nvidia@localhost:/tmp/host /tmp/guest
```


