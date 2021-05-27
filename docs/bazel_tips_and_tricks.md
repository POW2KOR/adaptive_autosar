# Bazel tips and tricks

## Where to find build artifacts

Build results are under `bazel-bin`.

## Optimized compilation

For building the debug version use `--compilation_mode=dbg`. For building binaries stripped of debug information, use
`--compilation_mode=opt`.  Other useful parameters for debugging purposes are `--verbose_failures` and `--sandbox_debug`.

## Try out modifications to the amsr_xavier or starter_kit

There are two different approaches to try out modifications on the different repositories.

If you want to build the stack with a modified version of the starter kit or the BSW, first clone the starter kit:

```
git clone ssh://git@git.swf.daimler.com:7999/adasdai/starter_kit_adaptive_xavier.git
# or
git clone ssh://git@git.swf.daimler.com:7999/adasdai/amsr_xavier.git
```

Then do your modifications to the source. Finally, there are two methods to get Bazel to use your changes.

### Method 1: modifying WORKSPACE

Open the `WORKSPACE` file at the root of this repository and look for the commented-out `new_local_repository` with
`name = "starter_kit_adaptive_xavier"` or `name = "amsr_xavier"`. Uncomment it and replace `<local_path_to_reposittory>`
with the path where you checked out the the repository. Then comment or temporarily remove the corresponding
`new_git_repository` that you want to replace.

### Method 2: using --override_repository

Copy the corresponding `BUILD` file and add a `WORKSPACE` file using the commands below:

```
cp minerva_mpu_adaptive/bsw/starter_kit_adaptive_xavier.BUILD <path to starter_kit clone>/BUILD
echo "workspace(name = \"starter_kit_adaptive_xavier\")" > <path to starter_kit clone>/WORKSPACE
# or
cp minerva_mpu_adaptive/bsw/amsr_xavier.BUILD <path to amsr_xavier clone>/BUILD
echo "workspace(name = \"amsr_xavier\")" > <path to amsr_xavier clone>/WORKSPACE
```

Finally, in a [.bazelrc](https://docs.bazel.build/versions/master/guide.html#where-are-the-bazelrc-files), add the
following line:
```
build --override_repository=starter_kit_adaptive_xavier=<path to starter_kit clone>
# or
build --override_repository=amsr_xavier=<path to amsr_xavier clone>
```

Where you replace `<path to ...>` with the path to your modified starter kit repository.

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
