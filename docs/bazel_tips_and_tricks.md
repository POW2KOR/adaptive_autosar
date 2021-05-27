# Bazel tips and tricks

## Where to find build artifacts

Build results are under `bazel-bin`.

## Optimized compilation

For building the debug version use `--compilation_mode=dbg`. For building binaries stripped of debug information, use
`--compilation_mode=opt`.  Other useful parameters for debugging purposes are `--verbose_failures` and `--sandbox_debug`.

## Try out modifications to the BSW or starter kit

If you want to build the stack with a modified version of the starter kit or the BSW, first clone the starter kit:

```
git clone --recurse-submodules ssh://git@git.swf.daimler.com:7999/adasdai/starter_kit_adaptive_xavier.git
```

Then do your modifications to the source. At the end you have to copy the `BUILD` file and add a `WORKSPACE` file:

```
cp minerva_mpu_adaptive/bsw/starter_kit_adaptive_xavier.BUILD <path to starter kit clone>/BUILD
echo "workspace(name = \"starter_kit_adaptive_xavier\")" > <path to starter kit clone>/WORKSPACE
```

Finally, open `.bazelrc`, and add the following line:
```
build --override_repository=starter_kit_adaptive_xavier=<path to starter kit clone>
```

Where you replace `<path to starter kit clone>` with the path to your modified starter kit
repository.

## Increasing the size of the swap

The current build configuration has enough parallelism that it will eat through your RAM very quickly. To avoid
out-of-memory issues, increase the size of the machine swap like so:

```
sudo fallocate -l 64G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile

sudo swapon /swapfile
```

You should now be able to see when running `top` or `htop` that the swap available has increased.

To persist this change between restarts, add this line to the end of your `/etc/fstab`:

```
/swapfile swap swap defaults 0 0
```

And check it with `sudo mount -fav`.
