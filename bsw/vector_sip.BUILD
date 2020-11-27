load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("//:config/defs.bzl", "selecty_genrule")

package(default_visibility = ["//visibility:public"])

CMAKE_SYSTEM_NAME_LINUX = "Linux"

string_flag(name = "build-target", build_setting_default = "minerva-host")

config_setting(
    name = "minerva-host",
    flag_values = {
        ":build-target": "minerva-host",
    },
)

config_setting(
    name = "minerva-drive-sdk",
    flag_values = {
        ":build-target": "minerva-drive-sdk",
    },
)

config_setting(
    name = "minerva-target",
    flag_values = {
        ":build-target": "minerva-target",
    },
)

CMAKE_TOOLCHAIN_DICT = {
    ":minerva-host":{},
    ":minerva-drive-sdk":{
        "CMAKE_TRY_COMPILE_TARGET_TYPE":"STATIC_LIBRARY",
    },
    ":minerva-target":{
        "CMAKE_TRY_COMPILE_TARGET_TYPE":"STATIC_LIBRARY",
    },
    "//conditions:default":{},
}

GEN_CROSSTOOL_FILE = select({
    ":minerva-host": False,
    ":minerva-drive-sdk": False,
    ":minerva-target": True,
    "//conditions:default": False,
})

######################################################################################
# amsr-vector-fs-libvac
######################################################################################

filegroup(
    name = "amsr-vector-fs-libvac-srcs",
    srcs = glob(["BSW/amsr-vector-fs-libvac/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-libvac",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-libvac-srcs",
    static_libraries = [
        "libvac.a",
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-msr4base
######################################################################################

filegroup(
    name = "amsr-vector-fs-msr4base-srcs",
    srcs = glob(["BSW/amsr-vector-fs-msr4base/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-msr4base",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-msr4base-srcs",
    headers_only = True,
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-vajson
######################################################################################

filegroup(
    name = "amsr-vector-fs-vajson-srcs",
    srcs = glob(["BSW/amsr-vector-fs-vajson/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-vajson",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-vajson-srcs",
    static_libraries = [
        "libvajson.a",
    ],
    deps = [
        ":amsr-vector-fs-libvac",
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-libosabstraction
######################################################################################

filegroup(
    name = "amsr-vector-fs-libosabstraction-srcs",
    srcs = glob(["BSW/amsr-vector-fs-libosabstraction/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-libosabstraction",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-libosabstraction-srcs",
    static_libraries = [
        "libosabstraction.a",
    ],
    deps = [
        ":amsr-vector-fs-libvac",
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-log-api
######################################################################################

filegroup(
    name = "amsr-vector-fs-log-api-srcs",
    srcs = glob(["BSW/amsr-vector-fs-log-api/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-log-api",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-log-api-srcs",
    static_libraries = [
        "libara-logging.a",
        "libamsr-vector-fs-log-api-ipc.a",
        "libamsr-vector-fs-log-api-ipc-common.a",
        "libamsr-vector-fs-log-api-common.a",
    ],
    deps = [
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-vajson",
        ":amsr-vector-fs-libosabstraction"
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-sec-cryptostack-driver-lib_es
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-cryptostack-driver-lib_es-srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-cryptostack-driver-lib_es/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-cryptostack-driver-lib_es",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "amsr-vector-fs-msr4base_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-msr4base/lib/cmake/amsr-vector-fs-msr4base/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-sec-cryptostack-driver-lib_es-srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-cryptostack-driver-lib_es.a",
    ],
    deps = [
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-msr4base",
    ],
    visibility = ["//visibility:public"],
)


######################################################################################
# amsr-vector-fs-em-executionmanager
######################################################################################

filegroup(
    name = "amsr-vector-fs-em-executionmanager-srcs",
    srcs = glob(["BSW/amsr-vector-fs-em-executionmanager/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-em-executionmanager",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY":"ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY":"ON",
            # "ENABLE_ADDON":"ON",
            "CMAKE_VERBOSE_MAKEFILE":"ON",
            "BUILD_TESTS":"OFF",
            "ENABLE_DOXYGEN":"OFF",
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ara-logging_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-em-executionmanager-srcs",
    out_bin_dir = "sbin",
    binaries = [        
        "amsr_vector_fs_em_executionmanager",
    ],
    static_libraries = [
        "libamsr-vector-fs-em-executionmanagement_application-client.a",
        "libamsr-vector-fs-em-executionmanagement_state-client.a",
        "libamsr-vector-fs-em-executionmanagement_recovery-action-client.a",
        "libamsr-vector-fs-em-executionmanagement_failure-handler-client.a",
    ],
    deps = [
        ":amsr-vector-fs-vajson",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-msr4base",
        ":amsr-vector-fs-sec-cryptostack-driver-lib_es"
    ],
    visibility = ["//visibility:public"],
)


######################################################################################
# amsr-vector-fs-sec-iam
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-iam-srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-iam/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-iam",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ara-logging_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-sec-iam-srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-iam_libserver.a",
        "libamsr-vector-fs-sec-iam_libcommon.a",
        "libamsr-vector-fs-sec-iam_libclient.a",
    ],
    deps = [
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-comcommon
######################################################################################

filegroup(
    name = "amsr-vector-fs-comcommon-srcs",
    srcs = glob(["BSW/amsr-vector-fs-comcommon/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-comcommon",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ara-logging_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-comcommon-srcs",
    static_libraries = [
        "libComCommon.a",
    ],
    deps = [
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-sec-cryptostack
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-cryptostack-srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-cryptostack/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-cryptostack",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY":"ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY":"ON",
            "CMAKE_VERBOSE_MAKEFILE":"ON",
            "ENABLE_DOXYGEN":"OFF",
            "ENABLE_EXEC_MANAGER":"ON",
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-msr4base_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-msr4base/lib/cmake/amsr-vector-fs-msr4base/",
            "amsr-vector-fs-log-api-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-em-executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-sec-cryptostack-srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-cryptostack_libclient.a",
        "libamsr-vector-fs-sec-cryptostack_libserver.a",
        "libamsr-vector-fs-sec-cryptostack_libcommon.a",
        "libamsr-vector-fs-sec-cryptostack_libdriverfactory.a",
        "libamsr-vector-fs-sec-cryptostack_libsoftwareprovider.a",
    ],
    deps = [
        ":amsr-vector-fs-em-executionmanager",
    ],
    visibility = ["//visibility:public"],
)


######################################################################################
# amsr-vector-fs-sec-libseccom
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-libseccom-srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-libseccom/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-libseccom",
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-sec-libseccom-srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-libseccom_libtls.a",
        "libamsr-vector-fs-sec-libseccom_libcrypto.a",
    ],
    deps = [
        ":amsr-vector-fs-sec-cryptostack"
    ],
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/",
            "amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/",
            "amsr-vector-fs-sec-cryptostack_libara_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/",
            "amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/",
            "amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/",
        }
    ),
    visibility = ["//visibility:public"],
)


######################################################################################
# amsr-vector-fs-communicationmiddleware
######################################################################################

filegroup(
    name = "amsr-vector-fs-communicationmiddleware-srcs",
    srcs = glob(["BSW/amsr-vector-fs-communicationmiddleware/**"],),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-communicationmiddleware",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY":"ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY":"ON",
            "CMAKE_VERBOSE_MAKEFILE":"ON",
            "BUILD_TESTS":"OFF",
            "ENABLE_EXEC_MANAGER":"ON",
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "amsr-vector-fs-sec-iam_libclient_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libclient/",
            "amsr-vector-fs-sec-iam_libcommon_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libcommon/",
            "amsr-vector-fs-sec-iam_libara_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libara/",
            "amsr-vector-fs-sec-libseccom_libcrypto_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libcrypto/",
            "amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/",
            "amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/",
            "amsr-vector-fs-sec-cryptostack_libara_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/",
            "amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/",
            "amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/",
            "amsr-vector-fs-sec-libseccom_libtls_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libtls/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-em-executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-communicationmiddleware-srcs",
    static_libraries = [
        "libARA-IpcBinding-posix.a",
        "libARA.a",
        "libARA-SomeIP-posix.a",
        "libIpcBinding-posix.a",
        "libSomeIP-posix.a",
        "libSomeIP-posix-common.a",
    ],
    deps = [
        ":amsr-vector-fs-sec-libseccom",
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-sec-cryptostack",
        ":amsr-vector-fs-sec-iam",
        ":amsr-vector-fs-comcommon",
        #":mbition_app_prototype_src_gen",  # This src-gen will be uncommented once we have application sources and src-gen buildable
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-communicationmiddleware-headers
######################################################################################

# We need the header library to avoid cyclic depenencies between 
# ':code-gen' and ':amsr-vector-fs-communicationmiddleware'

cmake_external(
    name = "amsr-vector-fs-communicationmiddleware-headers",
    cache_entries = selecty_genrule(
        CMAKE_TOOLCHAIN_DICT, 
        {
            "CMAKE_SYSTEM_NAME":CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY":"ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY":"ON",
            "CMAKE_VERBOSE_MAKEFILE":"ON",
            "BUILD_TESTS":"OFF",
            "ENABLE_EXEC_MANAGER":"ON",
            "vac_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "amsr-vector-fs-sec-iam_libclient_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libclient/",
            "amsr-vector-fs-sec-iam_libcommon_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libcommon/",
            "amsr-vector-fs-sec-iam_libara_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libara/",
            "amsr-vector-fs-sec-libseccom_libcrypto_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libcrypto/",
            "amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/",
            "amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/",
            "amsr-vector-fs-sec-cryptostack_libara_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/",
            "amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/",
            "amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/",
            "amsr-vector-fs-sec-libseccom_libtls_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-sec-libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libtls/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH":"$EXT_BUILD_DEPS/amsr-vector-fs-em-executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        }
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-communicationmiddleware-srcs",
    headers_only = True,
    deps = [
        ":amsr-vector-fs-sec-libseccom",
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-sec-cryptostack",
        ":amsr-vector-fs-sec-iam",
        ":amsr-vector-fs-comcommon",
    ],
    visibility = ["//visibility:public"],
)

# src-gen targets are removed as they were dependent on mbition-prototype-app. This app is removed now.
# Once we have new application, the code-gen or src-gen will be enabled. 
