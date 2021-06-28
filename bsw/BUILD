load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_bsw_module")

package(default_visibility = ["//visibility:public"])

################
# BSW modules
################

minerva_aa_bsw_module(
    name = "amsr_vector_fs_socal",
    cache_entries = {
        "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_VERBOSE_MAKEFILE": "ON",
        "BUILD_TESTS": "OFF",
        "ENABLE_EXEC_MANAGER": "ON",
    },
    out_include_dirs = [
        "include/Socal/",
    ],
    out_static_libs = [
        "libSocal.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_socal_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
        ":someipd_posix",
    ],
)

filegroup(
    name = "amsr_vector_fs_socal_libsocal_a",
    srcs = [":amsr_vector_fs_socal"],
    output_group = "libSocal.a",
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_libvac",
    out_static_libs = [
        "libvac.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_libvac_srcs",
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_msr4base",
    out_headers_only = True,
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_msr4base_srcs",
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_libiostream",
    cache_entries = {
        "ENABLE_WRAPPER": "OFF",
    },
    out_bin_dir = "sbin",
    out_include_dirs = [
        "include/charconv",
        "include/libcharconv_common",
        "include/iostream",
        "include/libstream",
    ],
    out_static_libs = [
        "libamsr-vector-fs-libiostream.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_libiostream_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libvac",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_thread",
    cache_entries = {
        "ENABLE_WRAPPER": "OFF",
    },
    out_bin_dir = "sbin",
    out_static_libs = [
        "libvathread.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_thread_srcs",
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_vajson",
    out_include_dirs = [
        "include/vajson",
    ],
    out_static_libs = [
        "libvajson.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_vajson_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libvac",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_applicationbase",
    out_static_libs = [
        "libapplication_base.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_applicationbase_srcs",
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_libosabstraction",
    out_include_dirs = [
        "include/",
    ],
    out_static_libs = [
        "libosabstraction.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_libosabstraction_srcs",
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_log_api",
    cache_entries = {
        "ENABLE_DAEMON": "ON",
        "ENABLE_SYS_LOG": "ON",
    },
    out_static_libs = [
        # It is important that libara-logging.a goes
        # before libamsr-log.a. Or else there will be
        # linking errors
        "libara-logging.a",
        "libamsr-log.a",
        "libamsr-vector-fs-log-api-ipc.a",
        "libamsr-vector-fs-log-api-common.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_log_api_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_sec_cryptostack_driver_lib_es",
    out_static_libs = [
        "libamsr-vector-fs-sec-cryptostack-driver-lib_es.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_sec_cryptostack_driver_lib_es_srcs",
    deps = [
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_msr4base",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_em_executionmanager",
    cache_entries = {
        "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
        "ENABLE_ADDON": "OFF",
        "CMAKE_VERBOSE_MAKEFILE": "ON",
        "BUILD_TESTS": "OFF",
        "ENABLE_DOXYGEN": "OFF",
    },
    out_bin_dir = "sbin",
    out_binaries = [
        "amsr_vector_fs_em_executionmanager",
    ],
    out_static_libs = [
        "libamsr-vector-fs-em-executionmanagement_application-client.a",
        "libamsr-vector-fs-em-executionmanagement_state-client.a",
        "libamsr-vector-fs-em-executionmanagement_recovery-action-client.a",
        "libamsr-vector-fs-em-executionmanagement_failure-handler-client.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_em_executionmanager_srcs",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_sec_iam",
    cache_entries = {
        "ADAPTIVE_MICROSAR_SIP_DIR": "$EXT_BUILD_ROOT/external/amsr_xavier/",
    },
    out_static_libs = [
        "libamsr-vector-fs-sec-iam_libserver.a",
        "libamsr-vector-fs-sec-iam_libcommon.a",
        "libamsr-vector-fs-sec-iam_libclient.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_sec_iam_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_sec_cryptostack",
    cache_entries = {
        "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_VERBOSE_MAKEFILE": "ON",
        "ENABLE_DOXYGEN": "OFF",
        "ENABLE_EXEC_MANAGER": "ON",
        "ADAPTIVE_MICROSAR_SIP_DIR": "$EXT_BUILD_ROOT/external/amsr_xavier/",
    },
    out_binaries = [
        "amsr_vector_fs_sec_cryptostack_daemon",
    ],
    out_static_libs = [
        # It is very Important to maintain this order
        # If Changed there will be tons of liniking error
        "libamsr-vector-fs-sec-cryptostack_libclient.a",
        "libamsr-vector-fs-sec-cryptostack_libdriverfactory.a",
        "libamsr-vector-fs-sec-cryptostack_libsoftwareprovider.a",
        "libamsr-vector-fs-sec-cryptostack_libcommon.a",
        "libamsr-vector-fs-sec-cryptostack_libserver.a",
        "libamsr-vector-fs-sec-cryptostack_libipc.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_sec_cryptostack_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_em_executionmanager",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_sec_cryptostack_driver_lib_es",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_sec_libseccom",
    out_static_libs = [
        "libamsr-vector-fs-sec-libseccom_libtls.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_sec_libseccom_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_sec_cryptostack",
        ":amsr_vector_fs_sec_cryptostack_driver_lib_es",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_crc",
    out_static_libs = [
        # Here it is Important that libcrc.a goes before
        # libinternal.a, or else linking error on dependent
        # modules
        "libamsr-vector-fs-crc_libcrc.a",
        "libamsr-vector-fs-crc_libinternal.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_crc_srcs",
    deps = [
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_msr4base",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_e2e",
    out_static_libs = [
        "libamsr-vector-fs-e2e_libe2e.a",
        "libamsr-vector-fs-e2e_libinternal.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_e2e_srcs",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_msr4base",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_log_daemon",
    cache_entries = {
        "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
        "ENABLE_ADDON": "OFF",
        "CMAKE_VERBOSE_MAKEFILE": "ON",
        "BUILD_TESTS": "OFF",
        "ENABLE_DOXYGEN": "OFF",
        "ENABLE_EXEC_MANAGER": "ON",
    },
    out_binaries = [
        "amsr_vector_fs_log_daemon",
    ],
    out_static_libs = [
        "libamsr-vector-fs-log-daemon-service.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_log_daemon_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_em_executionmanager",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_someipprotocol",
    out_include_dirs = [
        "include/SomeIpProtocol",
    ],
    out_static_libs = [
        "libSomeIpProtocol.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_someipprotocol_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_someipbinding",
    out_include_dirs = [
        "include/SomeIpBinding",
        "include/SomeIpBindingInternal",
        "include/SomeIpBindingTransformationLayer",
    ],
    out_static_libs = [
        "libSomeIpBindingInternal.a",
        "libSomeIpBinding.a",
        "libSomeIpBindingTransformationLayer.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_someipbinding_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_someipdaemonclient",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_someipdaemonclient",
    out_include_dirs = [
        "include/SomeIpDaemonClient",
    ],
    out_static_libs = [
        "libSomeIpDaemonClient.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_someipdaemonclient_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "someipd_posix",
    cache_entries = {
        "CMAKE_EXPORT_NO_PACKAGE_REGISTRY": "ON",
        "CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY": "ON",
        "ENABLE_ADDON": "OFF",
        "CMAKE_VERBOSE_MAKEFILE": "ON",
        "ADAPTIVE_MICROSAR_SIP_DIR": "$EXT_BUILD_ROOT/external/amsr_xavier/",
        "BUILD_TESTS": "OFF",
        "ENABLE_DOXYGEN": "OFF",
        "ENABLE_EXEC_MANAGER": "ON",
    },
    out_binaries = [
        "someipd_posix",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_someipdaemon_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_em_executionmanager",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_sec_cryptostack",
        ":amsr_vector_fs_sec_cryptostack_driver_lib_es",
        ":amsr_vector_fs_sec_iam",
        ":amsr_vector_fs_sec_libseccom",
        ":amsr_vector_fs_someipdaemonclient",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_per_libpersistency",
    out_include_dirs = [
        "include/persistency",
        "include/persistency-common",
        "include/persistency-file-storage",
        "include/persistency-fs",
        "include/persistency-key-value-storage",
    ],
    out_static_libs = [
        "libpersistency-fs.a",
        "libpersistency-common.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_per_libpersistency_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_iointegritystream",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_logutility",
    out_static_libs = [
        "liblog-utility.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_logutility_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_iointegritystream",
    out_static_libs = [
        "libiointegritystream.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_iointegritystream_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_ipcbinding",
    out_include_dirs = [
        "include/IpcBinding",
        "include/IpcBindingInternal",
        "include/IpcBindingTransformationLayer",
    ],
    out_static_libs = [
        # It is Important to has the below
        # Libraries in this order
        "libIpcBinding.a",
        "libIpcBindingInternal.a",
        "libIpcBindingTransformationLayer.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_ipcbinding_srcs",
    deps = [
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_timesync",
    cache_entries = {
        "APPLICATION_PREFIX": "opt",
        "ENABLE_EXAMPLES": "OFF",
        "ADAPTIVE_MICROSAR_SIP_DIR": "$EXT_BUILD_ROOT/external/amsr_xavier/",
    },
    out_binaries = [
        "tsyncd",
    ],
    out_static_libs = [
        "libamsr-vector-fs-tsync_common.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_timesync_srcs",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_em_executionmanager",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_characterconversion",
    out_include_dirs = [
        "include/common",
        "include/charconv_vector",
    ],
    out_static_libs = [
        "libamsr-vector-fs-characterconversion_common.a",
        "libamsr-vector-fs-characterconversion_vector.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_characterconversion",
    deps = [
        ":amsr_vector_fs_libvac",
    ],
)

# In this library the ARG_INTERFACE flag is Default set
# Depending on this flag it either creas an static library
# Because the flag it set to true it doesn't create one.
minerva_aa_bsw_module(
    name = "amsr_vector_fs_udstransport",
    out_headers_only = True,
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_udstransport",
    deps = [
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_diagnosticutility",
    out_static_libs = [
        "libLibDiagUtility.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_diagnosticutility",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

# In this library the ARG_INTERFACE flag is Default set
# Depending on this flag it either creas an static library
# Because the flag it set to true it doesn't create one.
minerva_aa_bsw_module(
    name = "amsr_vector_fs_pduhdrtpbinding",
    out_headers_only = True,
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_pduhdrtpbinding",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_diagnosticutility",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_udstransport",
        ":amsr_vector_fs_vajson",
    ],
)

# In this library the ARG_INTERFACE flag is Default set
# Depending on this flag it either creas an static library
# Because the flag it set to true it doesn't create one.
minerva_aa_bsw_module(
    name = "amsr_vector_fs_doipbinding",
    out_headers_only = True,
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_doipbinding",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_diagnosticutility",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_iointegritystream",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_per_libpersistency",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_udstransport",
        ":amsr_vector_fs_vajson",
    ],
)

# In this library the ARG_INTERFACE flag is Default set
# Depending on this flag it either creas an static library
# Because the flag it set to true it doesn't create one.
minerva_aa_bsw_module(
    name = "amsr_vector_fs_diagnosticrpc",
    out_headers_only = True,
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_diagnosticrpc",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_diagnosticutility",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_udstransport",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_diagnosticrpccombinding",
    out_static_libs = [
        "libLibDiagnosticRpcComBinding.a",
    ],
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_diagnosticrpccombinding",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_diagnosticrpc",
        ":amsr_vector_fs_diagnosticutility",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_vajson",
    ],
)

# In this library the ARG_INTERFACE flag is Default set
# Depending on this flag it either creas an static library
# Because the flag it set to true it doesn't create one.
minerva_aa_bsw_module(
    name = "amsr_vector_fs_aradiag",
    out_headers_only = True,
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_aradiag",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_diagnosticrpc",
        ":amsr_vector_fs_diagnosticrpccombinding",
        ":amsr_vector_fs_diagnosticutility",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_udstransport",
        ":amsr_vector_fs_vajson",
    ],
)

minerva_aa_bsw_module(
    name = "amsr_vector_fs_diagnosticmanager",
    out_headers_only = True,
    srcs_filegroup = "@amsr_xavier//:amsr_vector_fs_diagnosticmanager",
    deps = [
        ":amsr_vector_fs_applicationbase",
        ":amsr_vector_fs_characterconversion",
        ":amsr_vector_fs_crc",
        ":amsr_vector_fs_diagnosticrpc",
        ":amsr_vector_fs_diagnosticrpccombinding",
        ":amsr_vector_fs_diagnosticutility",
        ":amsr_vector_fs_e2e",
        ":amsr_vector_fs_iointegritystream",
        ":amsr_vector_fs_ipcbinding",
        ":amsr_vector_fs_libiostream",
        ":amsr_vector_fs_libosabstraction",
        ":amsr_vector_fs_libvac",
        ":amsr_vector_fs_log_api",
        ":amsr_vector_fs_logutility",
        ":amsr_vector_fs_msr4base",
        ":amsr_vector_fs_per_libpersistency",
        ":amsr_vector_fs_socal",
        ":amsr_vector_fs_someipbinding",
        ":amsr_vector_fs_someipdaemonclient",
        ":amsr_vector_fs_someipprotocol",
        ":amsr_vector_fs_thread",
        ":amsr_vector_fs_udstransport",
        ":amsr_vector_fs_vajson",
    ],
)

py_binary(
    name = "amsrswpkg_generator",
    srcs = ["@amsr_xavier//:amsrswpkg_generator"],
    main = "Examples/nvidia-update-strategy/addon/amsrswpkg_generator/generate.py",
    python_version = "PY3",
    srcs_version = "PY3",
)
