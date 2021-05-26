# Known issues and fixes

## Proxy handling in Docker

In order to allow Internet access from inside our docker containers, we need to pass to them proper
environment variables. For now, we should take care on the following settings:

- proxy settings in `~/.docker/config.json`: needed to set up access from ubuntu_18.04 image
  when it is started on host
- proxy settings which are passed with `docker run` command: needed to set up access from
  minerva_mpu_docker
- proxy settings in `BUILD` file: needed to set up access from ubuntu_18.04 image when it is started
  from inside minerva_mpu_docker container

In case of proxy settings change, please change corresponding parameters according to your build and
launch strategy.

## Workaround for the "no such package" issue

If a build without docker has beed initiated, and Bazel-generated directories present in the working directory, then the
following error might happen when Docker build container is used:

```
ERROR: Skipping '//:os': no such package 'bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_skeleton/lib':
Unable to determine the local repository for directory
/workspaces/minerva_mpu_adaptive/bazel-out/aarch64-fastbuild/bin/bsw/amsr_vector_fs_socal_for_skeleton/lib
WARNING: Target pattern parsing failed.
```

In such a case, it is needed to remove Bazel-generated directories (`bazel-bin`, `bazel-minerva_mpu_adaptive`,
`bazel-out`, `bazel-testlogs`) from host.

## Connection timeout issue while submodule init of gnulibs in collectd repo with VPN on

If you face connection timeout issues while submodule init of `gnulibs` in collectd repo through `collectd_mbient` rule
of WORKSPACE file, then open `~/.gitconfig` file and add below 2 lines:

```
[url "https://git.savannah.gnu.org/git/"]
      insteadOf = git://git.savannah.gnu.org/
```
