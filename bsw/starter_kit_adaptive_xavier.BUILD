load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")
load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "extend_and_select", "minerva_aa_codegen_declare")

package(default_visibility = ["//visibility:public"])

CMAKE_SYSTEM_NAME_LINUX = "Linux"

string_flag(
    name = "build_target",
    build_setting_default = "minerva_host",
)

config_setting(
    name = "minerva_host",
    flag_values = {
        ":build_target": "minerva_host",
    },
)

config_setting(
    name = "minerva_drive_sdk",
    flag_values = {
        ":build_target": "minerva_drive_sdk",
    },
)

config_setting(
    name = "minerva_target",
    flag_values = {
        ":build_target": "minerva_target",
    },
)

# CMAKE_TRY_COMPILE_TARGET_TYPE set to STATIC_LIBRARY is needed to make aarch64
# builds work, I do not know exactly why using this option affects the linking
# of pthread, but it seems it does, so we're linking pthread manually where
# it's needed. Furthermore, we make the approach uniform across all the targets
# so that we don't have any mismatches that might be harder to debug in the
# future.
CMAKE_TOOLCHAIN_DICT = {
    ":minerva_host": {
        "CMAKE_TRY_COMPILE_TARGET_TYPE": "STATIC_LIBRARY",
    },
    ":minerva_drive_sdk": {
        "CMAKE_TRY_COMPILE_TARGET_TYPE": "STATIC_LIBRARY",
    },
    ":minerva_target": {
        "CMAKE_TRY_COMPILE_TARGET_TYPE": "STATIC_LIBRARY",
    },
    "//conditions:default": {
        "CMAKE_TRY_COMPILE_TARGET_TYPE": "STATIC_LIBRARY",
    },
}

GEN_CROSSTOOL_FILE = select({
    ":minerva_host": False,
    ":minerva_drive_sdk": False,
    ":minerva_target": True,
    "//conditions:default": False,
})

######################################################################################
# amsr_vector_fs_libvac
######################################################################################

filegroup(
    name = "amsr_vector_fs_libvac_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libvac/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_libvac",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_libvac_srcs",
    static_libraries = [
        "libvac.a",
    ],
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr_vector_fs_msr4base
######################################################################################

filegroup(
    name = "amsr_vector_fs_msr4base_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-msr4base/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_msr4base",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    headers_only = True,
    lib_source = ":amsr_vector_fs_msr4base_srcs",
    visibility = ["//visibility:public"],
)

######################################################################################
# amsr_vector_fs_libiostream
######################################################################################

filegroup(
    name = "amsr_vector_fs_libiostream_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libiostream/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_libiostream",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "ENABLE_WRAPPER": "OFF",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_libiostream_srcs",
    out_bin_dir = "sbin",
    static_libraries = [
        "libamsr-vector-fs-libiostream_libcharconv_vector_stl.a",
        "libamsr-vector-fs-libiostream_libstream_vector_stl.a",
        "libamsr-vector-fs-libiostream_libcharconv_common.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

######################################################################################
# amsr_vector_fs_vathread
######################################################################################

filegroup(
    name = "amsr_vector_fs_thread_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-thread/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_thread",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "ENABLE_WRAPPER": "OFF",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_thread_srcs",
    out_bin_dir = "sbin",
    static_libraries = [
        "libvathread.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

######################################################################################
# amsr_vector_fs_vajson
######################################################################################

filegroup(
    name = "amsr_vector_fs_vajson_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-vajson/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_vajson",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "amsr-vector-fs-libiostream_libstream_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libiostream/lib/cmake/amsr-vector-fs-libiostream_libstream_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_common/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_vajson_srcs",
    static_libraries = [
        "libvajson.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libvac",
    ],
)

######################################################################################
# amsr_vector_fs_applicationbase
######################################################################################

filegroup(
    name = "amsr_vector_fs_applicationbase_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-applicationbase/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_applicationbase",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_applicationbase_srcs",
    static_libraries = [
        "libapplication_base.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

######################################################################################
# amsr_vector_fs_libosabstraction
######################################################################################

filegroup(
    name = "amsr_vector_fs_libosabstraction_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libosabstraction/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_libosabstraction",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_libosabstraction_srcs",
    static_libraries = [
        "libosabstraction.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

######################################################################################
# amsr_vector_fs_log_api
######################################################################################

filegroup(
    name = "amsr_vector_fs_log_api_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-api/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_log_api",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "ENABLE_DAEMON": "ON",
            "ENABLE_SYS_LOG": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "vathread_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_thread/lib/cmake/vathread/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_log_api_srcs",
    static_libraries = [
        "libamsr-log.a",
        "libara-logging.a",
        "libamsr-vector-fs-log-api-ipc.a",
        "libamsr-vector-fs-log-api-common.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

######################################################################################
# amsr_vector_fs_sec_cryptostack_driver_lib_es
######################################################################################

filegroup(
    name = "amsr_vector_fs_sec_cryptostack_driver_lib_es_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-cryptostack-driver-lib_es/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_sec_cryptostack_driver_lib_es",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_msr4base/lib/cmake/amsr-vector-fs-msr4base/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_sec_cryptostack_driver_lib_es_srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-cryptostack-driver-lib_es.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_msr4base",
    ],
)

######################################################################################
# amsr_vector_fs_em_executionmanager
######################################################################################

filegroup(
    name = "amsr_vector_fs_em_executionmanager_addon_demo_application_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-em-executionmanager/addon/amsr-vector-fs-em-executionmanager-demo-application/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_em_executionmanager_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-em-executionmanager/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_em_executionmanager",
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
            "CMAKE_EXE_LINKER_FLAGS": "-lpthread",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "amsr-log_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-log/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "amsr-vector-fs-libiostream_libstream_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libiostream/lib/cmake/amsr-vector-fs-libiostream_libstream_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_vector_stl_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_vector_stl/",
            "amsr-vector-fs-libiostream_libcharconv_common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libiostream/lib/cmake/amsr-vector-fs-libiostream_libcharconv_common/",
            "application_base_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_applicationbase/lib/cmake/application_base/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_em_executionmanager_srcs",
    out_bin_dir = "sbin",
    static_libraries = [
        "libamsr-vector-fs-em-executionmanagement_application-client.a",
        "libamsr-vector-fs-em-executionmanagement_state-client.a",
        "libamsr-vector-fs-em-executionmanagement_recovery-action-client.a",
        "libamsr-vector-fs-em-executionmanagement_failure-handler-client.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_vajson",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",

    ],
)

######################################################################################
# amsr_vector_fs_sec_iam
######################################################################################

filegroup(
    name = "amsr_vector_fs_sec_iam_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-iam/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_sec_iam",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "ADAPTIVE_MICROSAR_SIP_DIR": "$EXT_BUILD_ROOT/external/starter_kit_adaptive_xavier/mb_base_layer_adaptive_xavier/amsr_xavier",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_sec_iam_srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-iam_libserver.a",
        "libamsr-vector-fs-sec-iam_libcommon.a",
        "libamsr-vector-fs-sec-iam_libclient.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_log_api",
    ],
)

######################################################################################
# amsr_vector_fs_comcommon
######################################################################################

filegroup(
    name = "amsr_vector_fs_comcommon_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-comcommon/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_comcommon",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "amsr-log_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-log/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_comcommon_srcs",
    static_libraries = [
        "libComCommon.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_vajson",
    ],
)

######################################################################################
# amsr_vector_fs_sec_cryptostack
######################################################################################

filegroup(
    name = "amsr_vector_fs_sec_cryptostack_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-cryptostack/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_sec_cryptostack",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "ENABLE_DOXYGEN": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_msr4base/lib/cmake/amsr-vector-fs-msr4base/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "amsr-log_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-log/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
            "amsr-vector-fs-sec-cryptostack-driver-lib_es_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack_driver_lib_es/lib/cmake/amsr-vector-fs-sec-cryptostack-driver-lib_es/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_sec_cryptostack_srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-cryptostack_libclient.a",
        "libamsr-vector-fs-sec-cryptostack_libserver.a",
        "libamsr-vector-fs-sec-cryptostack_libcommon.a",
        "libamsr-vector-fs-sec-cryptostack_libdriverfactory.a",
        "libamsr-vector-fs-sec-cryptostack_libsoftwareprovider.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_em_executionmanager",
        ":amsr_vector_fs_sec_cryptostack_driver_lib_es",
    ],
)

######################################################################################
# amsr_vector_fs_sec_libseccom
######################################################################################

filegroup(
    name = "amsr_vector_fs_sec_libseccom_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-libseccom/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_sec_libseccom",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/",
            "amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/",
            "amsr-vector-fs-sec-cryptostack_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/",
            "amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/",
            "amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_sec_libseccom_srcs",
    static_libraries = [
        "libamsr-vector-fs-sec-libseccom_libtls.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_sec_cryptostack",
    ],
)

######################################################################################
# amsr_vector_fs_communicationmiddleware
######################################################################################

filegroup(
    name = "amsr_vector_fs_communicationmiddleware_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-communicationmiddleware/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_communicationmiddleware",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
            "amsr-vector-fs-sec-iam_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libclient/",
            "amsr-vector-fs-sec-iam_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libcommon/",
            "amsr-vector-fs-sec-iam_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libara/",
            "amsr-vector-fs-sec-libseccom_libcrypto_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libcrypto/",
            "amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/",
            "amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/",
            "amsr-vector-fs-sec-cryptostack_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/",
            "amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/",
            "amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/",
            "amsr-vector-fs-sec-libseccom_libtls_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libtls/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_communicationmiddleware_srcs",
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
        ":amsr_vector_fs_sec_libseccom",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_sec_cryptostack",
        ":amsr_vector_fs_sec_iam",
        ":amsr_vector_fs_comcommon",
    ],
)

######################################################################################
# amsr_vector_fs_crc
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
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_msr4base/lib/cmake/amsr-vector-fs-msr4base/",
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
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_libvac",
    ],
)

######################################################################################
# amsr_vector_fs_e2e
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
            "amsr-vector-fs-msr4base_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_msr4base/lib/cmake/amsr-vector-fs-msr4base/",
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
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_applicationbase",
    ],
)

######################################################################################
# amsr_vector_fs_socal_for_proxy
######################################################################################

filegroup(
    name = "amsr_vector_fs_socal_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-socal/**"]),
    visibility = ["//visibility:public"],
)

cmake_external(
    name = "amsr_vector_fs_socal_for_proxy",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
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
        "@minerva_mpu_adaptive//bsw:starter_kit_proxy_socal_srcs_lib",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_comcommon",
    ],
)

######################################################################################
# amsr_vector_fs_socal_for_skeleton
######################################################################################

cmake_external(
    name = "amsr_vector_fs_socal_for_skeleton",
    cache_entries = extend_and_select(
        CMAKE_TOOLCHAIN_DICT,
        {
            "CMAKE_SYSTEM_NAME": CMAKE_SYSTEM_NAME_LINUX,
            "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
            "CMAKE_VERBOSE_MAKEFILE": "ON",
            "BUILD_TESTS": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
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
        "@minerva_mpu_adaptive//bsw:starter_kit_skeleton_socal_srcs_lib",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_comcommon",
    ],
)

######################################################################################
# amsr_vector_fs_socal_headers
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
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "amsr-vector-fs-log-api-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/",
            "amsr-vector-fs-log-api-ipc-common_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/",
            "amsr-vector-fs-log-api-ipc_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
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
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_comcommon",
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
    name = "ncd_arxml",
    srcs = [
        "examples/proxy-skeleton-demo-idc6/arxml/NcdProxySkeletonDemo.ARXML",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "standard_types_arxml",
    srcs = [
        "examples/proxy-skeleton-demo-idc6/arxml/AUTOSAR_MOD_StandardTypes.arxml",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "mex_arxml",
    srcs = [
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-em-executionmanager/mex/MexDefs.arxml",
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-applicationbase/mex/BswExecutableModelExtension.arxml",
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
            "ENABLE_DOXYGEN": "OFF",
            "ENABLE_EXEC_MANAGER": "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "CMAKE_EXE_LINKER_FLAGS": "-lpthread",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_log_daemon_srcs",
    static_libraries = [
        "libamsr-vector-fs-log-daemon-service.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_em_executionmanager",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_vajson",
    ],
)

######################################################################################
# amsr_vector_fs_someipprotocol
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
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_someipprotocol_srcs",
    static_libraries = [
        "libSomeIpProtocol.a",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_comcommon",
    ],
)

######################################################################################
# amsr_vector_fs_someipbinding
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
            "vathread_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_thread/lib/cmake/vathread/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "vajson_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
            "SomeIpProtocol_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipprotocol/lib/cmake/SomeIpProtocol/",
            "SomeIpDaemonClient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipdaemonclient/lib/cmake/SomeIpDaemonClient/",
            "Socal_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_socal_headers/lib/cmake/Socal/",
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
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_comcommon",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_someipdaemonclient",
        ":amsr_vector_fs_socal_headers",
    ],
)

######################################################################################
# amsr_vector_fs_someipdaemonclient
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
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
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
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_comcommon",
        ":amsr_vector_fs_libosabstraction",
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
            "ENABLE_DOXYGEN": "OFF",
            "ENABLE_EXEC_MANAGER" : "ON",
            "vac_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/",
            "ComCommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/",
            "SomeIpProtocol_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipprotocol/lib/cmake/SomeIpProtocol/",
            "SomeIpDaemonClient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_someipdaemonclient/lib/cmake/SomeIpDaemonClient/",
            "ara-logging_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/",
            "osabstraction_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/",
            "amsr-vector-fs-sec-iam_libclient_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libclient/",
            "amsr-vector-fs-sec-iam_libcommon_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libcommon/",
            "amsr-vector-fs-sec-iam_libara_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libara/",
            "amsr-vector-fs-sec-libseccom_libtls_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_sec_libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libtls/",
            "amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH": "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/",
        },
    ),
    generate_crosstool_file = GEN_CROSSTOOL_FILE,
    lib_source = ":amsr_vector_fs_someipdaemon_srcs",
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_vajson",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_sec_libseccom",
        ":amsr_vector_fs_comcommon",
        ":amsr_vector_fs_sec_iam",
        ":amsr_vector_fs_em_executionmanager",
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

filegroup(
    name = "proxy_demo_idc6_srcs",
    srcs = [
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/etc/com_application.json",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/etc/logging_config.json",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/proxy_demo_error_domain.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/activation_manager.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/proxy_demo_error_domain.h",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/application.h",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/remote_parking.h",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/application.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/main.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/activation_manager.h",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/remote_parking.cpp",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "skeleton_demo_idc6_srcs",
    srcs = [
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/etc/com_application.json",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/etc/logging_config.json",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/skeleton_demo_error_domain.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/activation_manager.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/skeleton_demo_error_domain.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/application.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/RemoteParking_server.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/application.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/main.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/activation_manager.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/RemoteParking_server.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/HomeParking_server.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/HomeParking_server.cpp",

    ],
    visibility = ["//visibility:public"],
)
