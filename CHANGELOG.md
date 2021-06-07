# Change Log

## Unreleased

### Changed

* Applications each now have its own `package` target implemented using Bazel `pkg_tar`. The application and the config
files get built into the filesystem using this package.
* The measurement technology is disabled by default for BROP B2. It is now included in the filesystem only if you call
`bazel build` with `--//:mt`.
* `ara::com` was integrated into `x6aa_config_manager`. Therefore, for the circular dependency workaround, you now need
to run `bazel build //bsw:amsr_vector_fs_socal_for_x6aa_config_manager --config=<CONFIGURATION>` before your
`bazel build //:minerva_mpu_adaptive_filesystem --config=<CONFIGURATION>`.