#Connecting over SSH to the QEMU virtual ECU

The following steps shall be executed after launching of `./run_aarch64_qemu.sh` or `./run_x86_64_qemu.sh`

## On Host system

### In case of `./run_aarch64_qemu.sh`
```
saksinh@cmtcleu60844879:~/minerva_mpu_adaptive$ ssh -p 10022 nvidia@localhost
```
Password: nvidia

After you successfully log in in QEMU, you should see the following command line prompt:
```
nvidia@tegra-ubuntu:~$
```

### In case of `./run_x86_64_qemu.sh`
```
saksinh@cmtcleu60844879:~/minerva_mpu_adaptive$ ssh -p 10022 ubuntu@localhost
```
Password: ubuntu

After you successfully log in in QEMU, you should see the following command line prompt:
```
ubuntu@ubuntu:~$
```


If you are facing an issue of such type:
```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the ECDSA key sent by the remote host is
SHA256:......
Please contact your system administrator.
Add correct host key in /lhome/username/.ssh/known_hosts to get rid of this message.
Offending ECDSA key in /lhome/username/.ssh/known_hosts:4
  remove with:
  ssh-keygen -f "/lhome/username/.ssh/known_hosts" -R "[localhost]:10022"
ECDSA host key for [localhost]:10022 has changed and you have requested strict checking.
Host key verification failed.
```

then follow its suggestion and execute the command:
```
ssh-keygen -f $HOME"/.ssh/known_hosts" -R "[localhost]:10022"
```

And after that repeat the attempt to log in through SSH.


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
nvidia@localhost:/tmp/host on /tmp/guest type fuse.sshfs (rw,nosuid,nodev,relatime,user_id=...,group_id=...)
```

Now you should be able to read and modify files that are located in `/tmp/host` in qemu via modifying files in
`/tmp/guest` in host system.
