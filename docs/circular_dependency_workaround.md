# Circular dependency workaround

Currently, there is a circular linking dependency between `amsr_vector_fs_socal` and the generated source code for
`ara::com`. Bazel does not support circular linking dependencies, but allows `.a` files to be used in the `srcs`
field of `cc_binary`. Therefore, we make use of `.a` libraries to order things around and resolve the dependencies
without the need for the dependencies to be declared explicity in the Bazel DAG. `libSocal.a` is extracted using the
output group into `//bsw:amsr_vector_fs_socal_libsocal_a`.

This is better than the previous approach where we had a special target which had to be build ahead of time in a
separate call to `bazel build.` This was inconvenient and didn't scale well with the increasing number of applications.

We expect that there will be similar circular dependencies within the persistency BSW module and diagnostics.
