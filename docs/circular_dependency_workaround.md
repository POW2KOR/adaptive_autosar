# Circular dependency workaround

Currently, there is a circular linking dependency between `amsr_vector_fs_socal` and the generated source code for
`ara::com`. Bazel does not support circular linking dependencies. Currently, the only way to get rid of this circular
dependency is through some custom temporary targets called `amsr_vector_fs_socal_for_proxy` and
`amsr_vector_fs_socal_for_skeleton`. Whenever the generated sources for `ara::com` change (or on the first build),
these targets have to be rebuilt manually. The manual rebuild is necessary these are not explicit build dependencies in
the Bazel build system, but hard-coded path includes.

These steps are necessary due to the circular dependency workaround. They will not be needed once Vector ships a fix in
the SIP:

```
bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=<CONFIGURATION>
bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=<CONFIGURATION>

# For now we are commenting out the references for socal_for_software_update as we are not able to build the target
with latest delivery, but we're bringing it back in a future step.
# bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=<CONFIGURATION>
```

After that, you can initiate your actual building, because the circular dependency is worked around with the
`//bsw:amsr_vector_fs_socal_headers` target and both `\\:socal_lib_for_proxy` and `\\:socal_lib_for_socal` file groups.
