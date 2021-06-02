# Change Log

## Unreleased

### Changed

* Applications each now have its own `package` target implemented using Bazel `pkg_tar`. The application and the config
files get built into the filesystem using this package.
* The measurement technology is disabled by default for BROP B2. It is now included in the filesystem only if you call
`bazel build` with `--//:mt`.
