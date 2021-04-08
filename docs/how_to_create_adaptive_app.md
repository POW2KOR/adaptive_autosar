# How to create adaptive AUTOSAR app

## About the document

We keep the document for tracking steps that a develop needs to take to write the adaptive
AUTOSAR app.

The document may change as the adaptive AUTOSAR process in the project matures.

## Input data

The story beginns with an ARXML. For an AUTOSAR application you need a valid ARXML file.
An example of the valid ARXML file you can find in this repo, just search for files with 
extention `*.arxml`.

## Code generators

Autosar havily utilizes code generation. So the very first that you need to do is to run
code generators to obtain headers and cpp files.

We have a special Bazel rule called `minerva_aa_codegen_rule` which runs the code generator and gives you a bunch of
generated files as an output. For more info on this read the docstring for `minerva_aa_codegen_rule` in
`bazel/defs.bzl`.

Keep in mind to run the code generator successfuly, you need not only ARXML for your app,
but also general ARXMLs.

```bash
filegroup(
    name = "app_arxml",
    srcs = [
        # app related ARXML
        "sw_update_client_minerva_adapter_app/arxml/sw_update_client_minerva_adapter_app.arxml",
        "sw_update_client_minerva_adapter_interface/arxml/swuc_if.arxml",

        # general ARXML that you need for every app
        "@starter_kit_adaptive_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:ncd_arxml",
        "@starter_kit_adaptive_xavier//:standard_types_arxml",
    ],
)
```

## Build libraries from code generated files

Once you generated the files, you need to create libraries from files so that bazel can use them. Depending on your
scenario, the number of libraries may vary. Anyway we will take a look on 2 types of libraries: 
 - header or srcs library
 - socal codegen library

### Header or srcs library

The first case is a simple example of the libary:

```bash
cc_library(
    name = "library_name",
    hdrs = [
        ":headers_group_that_is_generated",
    ],
    strip_include_prefix = "path/you/want/to/strip",
)
```

They all are more or less the same. The only library that is different is Socal. Socal has a cyclic
dependency and Bazel is not that great in resolving cyclic depdendencies, but we have a temporary workaround 
for this until Vector removes this cyclic dependency. So lat's take a deeper look on socal source code 
library.

### Socal library based on the code generated files

This is a real example of the socal codegen source code library:

```bash
cc_library(
    name = "sw_update_client_minerva_adapter_app_socal_srcs_lib",
    srcs = [
        ":sw_update_client_minerva_adapter_app_socal_srcs",
        ":sw_update_client_minerva_adapter_app_someipbinding_srcs",
        ":sw_update_client_minerva_adapter_app_someipprotocol_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    deps = [
        # code generated dependencies
        ":sw_update_client_minerva_adapter_app_modeldatatypes_hdrs_lib",
        ":sw_update_client_minerva_adapter_app_socal_hdrs_lib",
        ":sw_update_client_minerva_adapter_app_someipbinding_hdrs_lib",
        ":sw_update_client_minerva_adapter_app_someipprotocol_hdrs_lib",

        # vector libraries
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_comcommon",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_headers",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_someipbinding",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_vajson",
    ],
)
```

As we can see, it has 2 types of dependencies: code generated libraries and vector libraries.

But do not be afraid, once you saw it, you can build the socal source code library for any app.

Once you have the socal codegen source code library, you need to build the BSW socal library
(I know it sounds very similar).

```bash
minerva_aa_bsw_module(
    name = "amsr_vector_fs_socal_for_software_update",
    cache_entries = {
        "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_VERBOSE_MAKEFILE": "ON",
        "BUILD_TESTS": "OFF",
    },
    srcs_filegroup = "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_srcs",
    static_libraries = [
        "libSocal.a",
    ],
    deps = [
        # this should point to the socal code gen library for this application
        "@minerva_mpu_adaptive//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_socal_srcs_lib",

        # standard set of dependencies. The same for all apps.
        ":amsr_vector_fs_comcommon",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",

    ],
)
```

It is important here only 1 thing, check the first depedency.
The BSW socal library should depend on the socal codegen source code library.

Now once we have it, we need to make the generated `libSocal.a` visible outside.
For this we modify BUILD file from the root of the project and add the following:

```bash
target_build_dir_for_socal_sw_update = select({
    ":k8": [
        "bazel-out/k8-fastbuild/bin/external/starter_kit_adaptive_xavier/amsr_vector_fs_socal_for_software_update/lib/libSocal.a",
    ],
    ":aarch64": [
        "bazel-out/aarch64-fastbuild/bin/external/starter_kit_adaptive_xavier/amsr_vector_fs_socal_for_software_update/lib/libSocal.a",
    ],
})

filegroup(
    name = "socal_lib_for_sw_update",
    srcs = target_build_dir_for_socal_sw_update,
    visibility = ["//visibility:public"],
)
```

Once you have done it, you are good to write and build the executable. Hopefully the need for this complicated step
will be removed soon.

## Build the executable

Executable is also slightly tricky part, because we need to resolve cyclic dependency. But no worries.
We know how to solve it.

The exacutable should look like this:

```bash
cc_binary(
    name = "sw_update_client_minerva_adapter_app",
    srcs = [
        # source code, your implementation of the exacutable
        "main.cpp",
        "sw_update_error_domain.h",
        "application.h",

        # This a workaround to resolve cyclic dependency. This is the reason why the target sw_update_client_minerva_adapter_app
        # build in 2 steps.
        # The code generators depend on libSocal.a, contained in the @minerva_mpu_adaptive//:socal_lib_for_sw_update below.
        # That is why we put it in sources. It is important that this `:socal_lib_for_sw_update` is positioned earlier in
        # the list than the generated sources in `:sw_update_client_minerva_adapter_app_socal_srcs_lib` and
        # `:sw_update_client_minerva_adapter_app_applicationbase_init_deinit_srcs`
        "@minerva_mpu_adaptive//:socal_lib_for_sw_update",
        ":sw_update_client_minerva_adapter_app_socal_srcs_lib",
        ":sw_update_client_minerva_adapter_app_applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    deps = [
        ":sw_update_client_minerva_adapter_app_modeldatatypes_hdrs_lib",
        ":sw_update_client_minerva_adapter_app_socal_hdrs_lib",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_em_executionmanager",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_libvac",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_log_api",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_someipbinding",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_vajson",
    ],
)
```

As we can see, we need to follow the order of `srcs`. All libraries
we build on the previous step. So just keep in mind the order. And also do not forget
to mention all libraries you depend on. Also `copts` and `linkopts` are mandatory.

Once you are done, congratulations! We are close to be done. We now miss the runtime 
config manifest files.

Every app should have a set of configs and one executable. Let's add created executable 
to the filesystem.

In the `BUILD` file in the ROOT of the repositry we have a target `minerva_mpu_adaptive_binaries`.
It is important to add our executable to the files list and define the location of the 
executable in the docker image.

As we can see, executable location has the following pattern: `opt/NAME/bin/NAME`.

```bash
pkg_tar(
    name = "minerva_mpu_adaptive_binaries",
    files = {
        ":adaptive_autosar_someipdaemon_binary": "opt/someipd_posix/bin/someipd_posix",
        ":adaptive_autosar_log_daemon_binary": "opt/amsr_vector_fs_log_daemon/bin/amsr_vector_fs_log_daemon",
        ":adaptive_autosar_executionmanager_binary": "sbin/amsr_vector_fs_em_executionmanager",
        "//bsw:executionmanager_state_client_binary": "opt/executionmanager_state_client_app/bin/executionmanager_state_client_app",
        "//bsw:skeleton_demo_idc6": "opt/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/bin/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable",
        "//bsw:proxy_demo_idc6": "opt/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/bin/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable",

        # We add here the executable
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app": "opt/sw_update_client_minerva_adapter_app/bin/sw_update_client_minerva_adapter_app",
    },
    mode = "0755",
    package_dir = "/",
)
```

Now let's clarify the config files we need to run the app.

We need the following configs:
- logging_config.json 
- com_application.json
- exec_config.json
- someip_config.json
- ... any other json config files from code gen

Most of the config files are the result of the code generator. At this moment, 
the exception is `logging_config.json`and `com_application.json`.

Example of the `logging_config.json`:

```bash
{
    "name": "SwUpdateApp",
    "description": "Software update application",
    "dlt_id": "SWUD",
    "log_mode": ["kConsole"],
    "log_level": "kInfo",
    "log_dir_path": "./log",
    "ipc_port": 33,
    "reconnection_retry_offset": 0,
    "msg_buf_size": 1000
}
```

Example of the `com_application.json`:

```bash
{}
```

Yes, it is not a mistake, it should be empty.

All config files should be included into the docker image.
We do it in similar way, as we did it with binary.

```bash
pkg_tar(
    name = "adaptive_sw_update_client_minerva_adapter_configs",
    files = {
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_updatemanager_daemon_db": "opt/sw_update_client_minerva_adapter_app/etc/swcl_db.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_updatemanager_config": "opt/sw_update_client_minerva_adapter_app/etc/updatemanager.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_updatemanager_swcluser_meta": "opt/sw_update_client_minerva_adapter_app/etc/swcl_package_metadata.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_someip_config": "opt/sw_update_client_minerva_adapter_app/etc/someip_config.json",
        "//application/sw_update_client_minerva_adapter:sw_update_client_minerva_adapter_app_exec_config": "opt/sw_update_client_minerva_adapter_app/etc/exec_config.json",
        "//application/sw_update_client_minerva_adapter:logging_config_json": "opt/sw_update_client_minerva_adapter_app/etc/logging_config.json",
        "//application/sw_update_client_minerva_adapter:com_application_json": "opt/sw_update_client_minerva_adapter_app/etc/com_application.json",
    },
    mode = "0755",
)
```

Config files should be located in `opt/NAME/etc/`.

All configs are collected in `minerva_mpu_adaptive_configs`.

```bash
pkg_tar(
    name = "minerva_mpu_adaptive_configs",
    mode = "0755",
    package_dir = "",
    deps = [
        ":adaptive_autosar_executionmanager_state_client_configs",
        ":adaptive_autosar_log_daemon_configs",
        ":adaptive_autosar_proxy_configs",
        ":adaptive_autosar_skeleton_configs",
        ":adaptive_autosar_someipdaemon_configs",

        # here we add new configs
        ":adaptive_sw_update_client_minerva_adapter_configs",
    ],
)
```

And the very last step you need to do is to add `someipd-posix.json`. Currently 
we use `bsw/configs/someipd_posix/someipd-posix.json` to store all someip configs.

Example of the file `someipd-posix.json`:

```bash
{
    "applications": [
        "/opt/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/etc/someip_config.json",
        "/opt/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/etc/someip_config.json",

        # here we add our config, the path you define here is the path from the docker.
        "/opt/sw_update_client_minerva_adapter_app/etc/someip_config.json"
    ]
}
```

And that is it! You did it!

Now we can build and run the app:

```bash
# build the socal
bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_software_update

# build the docker image
bazel build //:minerva_mpu_adaptive_docker

# run the app in the docker
bazel run //:minerva_mpu_adaptive_docker
```

Have fun!
