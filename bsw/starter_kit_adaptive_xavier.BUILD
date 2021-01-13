load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@minerva_mpu_adaptive//bsw:defs.bzl", "extend_and_select", "minerva_aa_codegen_declare")

package(default_visibility = ["//visibility:public"])

CMAKE_SYSTEM_NAME_LINUX = "Linux"

string_flag(
    name = "build-target",
    build_setting_default = "minerva-host",
)

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
    ":minerva-host": {},
    ":minerva-drive-sdk": {
        "CMAKE_TRY_COMPILE_TARGET_TYPE": "STATIC_LIBRARY",
    },
    ":minerva-target": {
        "CMAKE_TRY_COMPILE_TARGET_TYPE": "STATIC_LIBRARY",
    },
    "//conditions:default": {},
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
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libvac/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-libvac",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
        },
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
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-msr4base/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-msr4base",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    headers_only = True,
    lib_source = ":amsr-vector-fs-msr4base-srcs",
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr-vector-fs-libiostream
######################################################################################

filegroup(
    name = "amsr-vector-fs-libiostream-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libiostream/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-libiostream",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "ENABLE_WRAPPER": "OFF",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-libiostream-srcs",
    out_bin_dir = "sbin",
    static_libraries = [
        "libamsr-vector-fs-libiostream_libcharconv_vector_stl.a",
        "libamsr-vector-fs-libiostream_libstream_vector_stl.a",
        "libamsr-vector-fs-libiostream_libcharconv_common.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libvac",
    ],
)

######################################################################################
# amsr-vector-fs-vathread
######################################################################################

filegroup(
    name = "amsr-vector-fs-thread-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-thread/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-thread",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "ENABLE_WRAPPER": "OFF",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-thread-srcs",
    out_bin_dir = "sbin",
    static_libraries = [
        "libvathread.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libvac",
    ],
)

######################################################################################
# amsr-vector-fs-vajson
######################################################################################

filegroup(
    name = "amsr-vector-fs-vajson-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-vajson/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-vajson",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "amsr-vector-fs-libiostream_libstream_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libiostream/lib/cmake/amsr-vector-fs-libiostream_libstream_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_common/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-vajson-srcs",
    static_libraries = [
        "libvajson.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libiostream",
        ":amsr-vector-fs-libvac",
    ],
)

######################################################################################
# amsr-vector-fs-applicationbase
######################################################################################

filegroup(
    name = "amsr-vector-fs-applicationbase-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-applicationbase/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-applicationbase",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-applicationbase-srcs",
    static_libraries = [
        "libapplication_base.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libvac",
    ],
)

######################################################################################
# amsr-vector-fs-libosabstraction
######################################################################################

filegroup(
    name = "amsr-vector-fs-libosabstraction-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libosabstraction/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-libosabstraction",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-libosabstraction-srcs",
    static_libraries = [
        "libosabstraction.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libvac",
    ],
)

######################################################################################
# amsr-vector-fs-log-api
######################################################################################

filegroup(
    name = "amsr-vector-fs-log-api-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-api/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-log-api",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "vathread_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-thread/lib/cmake/vathread/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-log-api-srcs",
    static_libraries = [
        "libamsr-log.a",
        "libara-logging.a",
        "libamsr-vector-fs-log-api-ipc.a",
        "libamsr-vector-fs-log-api-common.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-thread",
        ":amsr-vector-fs-vajson",
    ],
)

######################################################################################
# amsr-vector-fs-sec-cryptostack-driver-lib_es
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-cryptostack-driver-lib_es-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-cryptostack-driver-lib_es/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-cryptostack-driver-lib_es",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-msr4base/lib/cmake/amsr-vector-fs-msr4base/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-sec-cryptostack-driver-lib_es-srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-cryptostack-driver-lib_es.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-msr4base",
    ],
)

######################################################################################
# amsr-vector-fs-em-executionmanager
######################################################################################

filegroup(
    name = "amsr_vector_fs_em_executionmanager_addon_demo_application_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-em-executionmanager/addon/amsr-vector-fs-em-executionmanager-demo-application/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr-vector-fs-em-executionmanager-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-em-executionmanager/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-em-executionmanager",
    binaries = [
        "amsr_vector_fs_em_executionmanager",
    ],
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "ENABLE_ADDON": "OFF",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_DOXYGEN": "OFF",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "amsr-log_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-log/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "amsr-vector-fs-libiostream_libstream_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libiostream/lib/cmake/amsr-vector-fs-libiostream_libstream_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_common/",
            "application_base_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-applicationbase/lib/cmake/application_base/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-em-executionmanager-srcs",
    out_bin_dir = "sbin",
    static_libraries = [
        "libamsr-vector-fs-em-executionmanagement_application-client.a",
        "libamsr-vector-fs-em-executionmanagement_state-client.a",
        "libamsr-vector-fs-em-executionmanagement_recovery-action-client.a",
        "libamsr-vector-fs-em-executionmanagement_failure-handler-client.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-vajson",
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-applicationbase",
        ":amsr-vector-fs-libiostream",
        ":amsr-vector-fs-libosabstraction",

    ],
)

######################################################################################
# amsr-vector-fs-sec-iam
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-iam-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-iam/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-iam",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "ADAPTIVE_MICROSAR_SIP_DIR": "$EXT_BUILD_ROOT/external/starter_kit_adaptive_xavier/mb_base_layer_adaptive_xavier/amsr_xavier",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-sec-iam-srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-iam_libserver.a",
        "libamsr-vector-fs-sec-iam_libcommon.a",
        "libamsr-vector-fs-sec-iam_libclient.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
    ],
)

######################################################################################
# amsr-vector-fs-comcommon
######################################################################################

filegroup(
    name = "amsr-vector-fs-comcommon-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-comcommon/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-comcommon",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "amsr-log_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-log/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-comcommon-srcs",
    static_libraries = [
        "libComCommon.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-vajson",
    ],
)

######################################################################################
# amsr-vector-fs-sec-cryptostack
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-cryptostack-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-cryptostack/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-cryptostack",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "ENABLE_DOXYGEN": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-msr4base/lib/cmake/amsr-vector-fs-msr4base/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "amsr-log_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-log/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-em-executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
            "amsr-vector-fs-sec-cryptostack-driver-lib_es_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack-driver-lib_es/lib/cmake/amsr-vector-fs-sec-cryptostack-driver-lib_es/",
        },
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
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-em-executionmanager",
        ":amsr-vector-fs-sec-cryptostack-driver-lib_es",
    ],
)

######################################################################################
# amsr-vector-fs-sec-libseccom
######################################################################################

filegroup(
    name = "amsr-vector-fs-sec-libseccom-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-libseccom/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-sec-libseccom",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/",
            "amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/",
            "amsr-vector-fs-sec-cryptostack_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/",
            "amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/",
            "amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr-vector-fs-sec-libseccom-srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-libseccom_libtls.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-sec-cryptostack",
    ],
)

######################################################################################
# amsr-vector-fs-communicationmiddleware
######################################################################################

filegroup(
    name = "amsr-vector-fs-communicationmiddleware-srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-communicationmiddleware/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr-vector-fs-communicationmiddleware",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "amsr-vector-fs-sec-iam_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libclient/",
            "amsr-vector-fs-sec-iam_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libcommon/",
            "amsr-vector-fs-sec-iam_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libara/",
            "amsr-vector-fs-sec-libseccom_libcrypto_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libcrypto/",
            "amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/",
            "amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/",
            "amsr-vector-fs-sec-cryptostack_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/",
            "amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/",
            "amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/",
            "amsr-vector-fs-sec-libseccom_libtls_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libtls/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-em-executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        },
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
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-sec-libseccom",
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-sec-cryptostack",
        ":amsr-vector-fs-sec-iam",
        ":amsr-vector-fs-comcommon",
    ],
)

######################################################################################
# amsr-vector-fs-crc
######################################################################################

filegroup(
    name = "amsr_vector_fs_crc_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-crc/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_crc",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-msr4base/lib/cmake/amsr-vector-fs-msr4base/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_crc_srcs",
    static_libraries = [
        "libamsr-vector-fs-crc_libinternal.a",
        "libamsr-vector-fs-crc_libcrc.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-msr4base",
        ":amsr-vector-fs-libvac",
    ],
)

######################################################################################
# amsr-vector-fs-e2e
######################################################################################

filegroup(
    name = "amsr_vector_fs_e2e_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-e2e/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_e2e",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "amsr-vector-fs-crc_libinternal_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_crc/lib/cmake/amsr-vector-fs-crc_libinternal/",
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-msr4base/lib/cmake/amsr-vector-fs-msr4base/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_e2e_srcs",
    static_libraries = [
        "libamsr-vector-fs-e2e_libe2e.a",
        "libamsr-vector-fs-e2e_libinternal.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-msr4base",
        ":amsr-vector-fs-libvac",
        ":amsr_vector_fs_crc",
        ":amsr-vector-fs-applicationbase",
    ],
)

######################################################################################
# amsr-vector-fs-socal
######################################################################################

filegroup(
    name = "amsr_vector_fs_socal_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-socal/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_socal",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "amsr-vector-fs-crc_libinternal_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_crc/lib/cmake/amsr-vector-fs-crc_libinternal/",
            "amsr-vector-fs-e2e_libe2e_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_e2e/lib/cmake/amsr-vector-fs-e2e_libe2e/",
            "amsr-vector-fs-e2e_libinternal_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_e2e/lib/cmake/amsr-vector-fs-e2e_libinternal/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_socal_srcs",
    static_libraries = [
        "libSocal.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        # "@minerva_mpu_adaptive//bsw:starter_kit_proxy_socal_srcs_lib",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-comcommon",
    ],
)

######################################################################################
# amsr-vector-fs-socal-headers
######################################################################################

cmake_external(
    name = "amsr_vector_fs_socal_headers",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "amsr-vector-fs-crc_libinternal_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_crc/lib/cmake/amsr-vector-fs-crc_libinternal/",
            "amsr-vector-fs-e2e_libe2e_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_e2e/lib/cmake/amsr-vector-fs-e2e_libe2e/",
            "amsr-vector-fs-e2e_libinternal_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_e2e/lib/cmake/amsr-vector-fs-e2e_libinternal/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_socal_srcs",
    headers_only = True,
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-comcommon",
    ],
)

######################################################################################
# Generators
######################################################################################

filegroup(
    name = "amsrgen_sh",
    srcs = [
        "mb_base_layer_adaptive_xavier/amsr_xavier/DaVinciConfigurator/Core/amsrgen.sh",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "setup_jre_link_sh",
    srcs = [
        "mb_base_layer_adaptive_xavier/amsr_xavier/DaVinciConfigurator/Core/setupJreLinks.sh",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "application_arxml",
    srcs = [
        "examples/proxy-skeleton-demo-idc6/arxml/NcdProxySkeletonDemo.ARXML",
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-em-executionmanager/mex/MexDefs.arxml",
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# Log daemon executable
######################################################################################

filegroup(
    name = "amsr_vector_fs_log_daemon_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-daemon/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_log_daemon_configs",
    srcs = [
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-daemon/etc/exec_config.json",
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-daemon/etc/logd_config.json",
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-daemon/etc/logging_config.json",
    ],
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_log_daemon",
    binaries = [
        "amsr_vector_fs_log_daemon",
    ],
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "ENABLE_ADDON": "OFF",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_CCACHE": "ON",
            "ENABLE_DOXYGEN": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-em-executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_log_daemon_srcs",
    static_libraries = [
        "libamsr-vector-fs-log-daemon-service.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-em-executionmanager",
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-vajson",
    ],
)

######################################################################################
# amsr-vector-fs-someipprotocol
######################################################################################

filegroup(
    name = "amsr_vector_fs_someipprotocol_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipprotocol/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_someipprotocol",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_someipprotocol_srcs",
    static_libraries = [
        "libSomeIpProtocol.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-comcommon",
    ],
)

######################################################################################
# amsr-vector-fs-someipbinding
######################################################################################

filegroup(
    name = "amsr_vector_fs_someipbinding_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipbinding/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_someipbinding",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vathread_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-thread/lib/cmake/vathread/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-vajson/lib/cmake/vajson/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "SomeIpProtocol_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipprotocol/lib/cmake/SomeIpProtocol/",
            "SomeIpDaemonClient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipdaemonclient/lib/cmake/SomeIpDaemonClient/",
            "Socal_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-socal/lib/cmake/Socal/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_someipbinding_srcs",
    static_libraries = [
        "libSomeIpBindingInternal.a",
        "libSomeIpBinding.a",
        "libSomeIpBindingTransformationLayer.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-thread",
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-comcommon",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_someipdaemonclient",
        ":amsr-vector-fs-socal",
    ],
)

######################################################################################
# amsr-vector-fs-someipbinding-headers
######################################################################################

cmake_external(
    name = "amsr_vector_fs_someipbinding_headers",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vathread_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-thread/lib/cmake/vathread/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "SomeIpProtocol_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipprotocol/lib/cmake/SomeIpProtocol/",
            "SomeIpDaemonClient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipdaemonclient/lib/cmake/SomeIpDaemonClient/",
            "Socal_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-socal/lib/cmake/Socal/",
        },
    ),
    headers_only = True,
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_someipbinding_srcs",
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-thread",
        ":amsr-vector-fs-comcommon",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_someipdaemonclient",
        ":amsr-vector-fs-socal",
    ],
)

######################################################################################
# amsr-vector-fs-someipdaemonclient
######################################################################################

filegroup(
    name = "amsr_vector_fs_someipdaemonclient_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipdaemonclient/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_someipdaemonclient",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "SomeIpProtocol_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipprotocol/lib/cmake/SomeIpProtocol/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_someipdaemonclient_srcs",
    static_libraries = [
        "libSomeIpDaemonClient.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-comcommon",
        ":amsr-vector-fs-libosabstraction",
        ":amsr_vector_fs_someipprotocol"
    ],
)

######################################################################################
# SomeIP daemon executable
######################################################################################

filegroup(
    name = "amsr_vector_fs_someipdaemon_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipdaemon/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipdaemon_configs",
    srcs = [
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipdaemon/etc/exec_config.json",
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipdaemon/etc/logging_config.json",
        "@minerva_mpu_adaptive//application/configs:someip_posix_json"
    ],
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "someipd_posix",
    binaries = [
        "someipd_posix",
    ],
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "ENABLE_ADDON": "OFF",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "ADAPTIVE_MICROSAR_SIP_DIR": "$EXT_BUILD_ROOT/external/starter_kit_adaptive_xavier/mb_base_layer_adaptive_xavier/amsr_xavier",
            "BUILD_TESTS": "OFF",
            "ENABLE_CCACHE" :"ON",
            "ENABLE_DOXYGEN": "OFF",
            "ENABLE_EXEC_MANAGER" : "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libvac/lib/cmake/vac/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-comcommon/lib/cmake/ComCommon/",
            "SomeIpProtocol_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipprotocol/lib/cmake/SomeIpProtocol/",
            "SomeIpDaemonClient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipdaemonclient/lib/cmake/SomeIpDaemonClient/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-log-api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-sec-iam_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libclient/",
            "amsr-vector-fs-sec-iam_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libcommon/",
            "amsr-vector-fs-sec-iam_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-iam/lib/cmake/amsr-vector-fs-sec-iam_libara/",
            "amsr-vector-fs-sec-libseccom_libtls_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-sec-libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libtls/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr-vector-fs-em-executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_someipdaemon_srcs",
    visibility = ["//visibility:public"],
    deps = [
        ":amsr-vector-fs-thread",
        ":amsr-vector-fs-libosabstraction",
        ":amsr-vector-fs-libvac",
        ":amsr-vector-fs-vajson",
        ":amsr-vector-fs-log-api",
        ":amsr-vector-fs-sec-libseccom",
        ":amsr-vector-fs-comcommon",
        ":amsr-vector-fs-sec-iam",
        ":amsr-vector-fs-em-executionmanager",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_someipdaemonclient",
    ],
)

filegroup(
    name = "generator_common_tools",
    srcs = [
        "mb_base_layer_adaptive_xavier/amsr_xavier/DaVinciConfigurator/Core/DVACfgCmd",
        "mb_base_layer_adaptive_xavier/amsr_xavier/DaVinciConfigurator/Core/jre/lib/amd64/server/libjsig.so",
        "mb_base_layer_adaptive_xavier/amsr_xavier/DaVinciConfigurator/Core/plugins",
    ],
    visibility = ["//visibility:public"],
)

minerva_aa_codegen_declare(
    name = "generator",
    path_to_generators = "mb_base_layer_adaptive_xavier/amsr_xavier/Generators",
    generators = [
        "amsr_em_machine_config",
        "amsr_em_exec_config",
        "amsr_modelleddatatypes_api",
        "amsr_someipbinding",
        "amsr_updatemanager_swcluster_meta",
        "amsr_updatemanager_daemon",
        "amsr_applicationbase_init_deinit",
        "amsr_someipprotocol",
        "amsr_socal",
    ]
)