#Connecting over SSH to the QEMU virtual ECU

The following steps shall be executed after launching of `./run_aarch64_qemu.sh`

## On Host system

```
saksinh@cmtcleu60844879:~/minerva_mpu_adaptive$ ssh -p 10022 nvidia@localhost
```

After you successfully log in in QEMU, you should see the following command line prompt:
```
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
