# Change Log

## Unreleased

### Changed

* The measurement technology is disabled by default for BROP B2. It is now included in the filesystem only if you call
`bazel build` with `--//:mt`.
