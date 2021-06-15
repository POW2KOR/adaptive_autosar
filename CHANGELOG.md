# Change Log

## Unreleased

### Changed

* Release step 1B4 of AMSR is used.
* The IDC ECU extract replaces the Starter Kit ECU extract that was used until now.
* Applications each now have its own `package` target implemented using Bazel `pkg_tar`. The application and the config
files get built into the filesystem using this package.
* The measurement technology is disabled by default for BROP B2. It is now included in the filesystem only if you call
`bazel build` with `--//:mt`.
* Implemented a cyclic dependency workaround for socal which doesn't require extra targets and extra commands to be
run.
* An application base library has been created to contain the common parts for Adaptive applications. Applications
should add `//application/common:application_base` to their `deps` and derive from the base class.
