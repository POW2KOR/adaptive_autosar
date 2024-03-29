load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_declare")

# Model extensions

filegroup(
    name = "mex_arxml",
    srcs = [
        "BSW/amsr-vector-fs-applicationbase/mex/BswExecutableModelExtension.arxml",
        "BSW/amsr-vector-fs-applicationbase/mex/PhmMexDefsExecutable.arxml",
        "BSW/amsr-vector-fs-dm-diagnosticmanager/mex/MexDefsAraDiagConfig.arxml",
        "BSW/amsr-vector-fs-dm-diagnosticmanager/mex/MexDefsTransportProtocols.arxml",
        "BSW/amsr-vector-fs-em-executionmanager/mex/MexDefs.arxml",
        "BSW/amsr-vector-fs-log-api/mex/MexDefs.arxml",
        "BSW/amsr-vector-fs-log-daemon/mex/MexDefs.arxml",
        "BSW/amsr-vector-fs-nm-networkmanager/mex/MexDefsNmExtensionModel.arxml",
        "BSW/amsr-vector-fs-phm-healthmanager/mex/MexDefsAdditionalModelParameters.arxml",
        "BSW/amsr-vector-fs-phm-healthmanager/mex/MexDefsAliveSupervision.arxml",
        "BSW/amsr-vector-fs-phm-healthmanager/mex/MexDefsHealthChannelID.arxml",
        "BSW/amsr-vector-fs-phm-healthmanager/mex/MexDefsLocalSupervision.arxml",
        "BSW/amsr-vector-fs-phm-healthmanager/mex/MexDefsRule.arxml",
        "BSW/amsr-vector-fs-phm-healthmanager/mex/MexDefsSupervisedEntityID.arxml",
        "BSW/amsr-vector-fs-someipbinding/mex/SignalbasedModelExtension.arxml",
    ],
    visibility = ["//visibility:public"],
)

# BSW modules

filegroup(
    name = "amsr_vector_fs_libvac_srcs",
    srcs = glob(["BSW/amsr-vector-fs-libvac/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_msr4base_srcs",
    srcs = glob(["BSW/amsr-vector-fs-msr4base/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_libiostream_srcs",
    srcs = glob(["BSW/amsr-vector-fs-libiostream/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_thread_srcs",
    srcs = glob(["BSW/amsr-vector-fs-thread/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_vajson_srcs",
    srcs = glob(["BSW/amsr-vector-fs-vajson/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_applicationbase_srcs",
    srcs = glob(["BSW/amsr-vector-fs-applicationbase/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_libosabstraction_srcs",
    srcs = glob(["BSW/amsr-vector-fs-libosabstraction/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_log_api_srcs",
    srcs = glob(["BSW/amsr-vector-fs-log-api/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_sec_cryptostack_driver_lib_es_srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-cryptostack-driver-lib_es/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_em_executionmanager_addon_demo_application_srcs",
    srcs = glob(["BSW/amsr-vector-fs-em-executionmanager/example/em_example_app/src/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_em_executionmanager_srcs",
    srcs = glob(["BSW/amsr-vector-fs-em-executionmanager/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_sec_iam_srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-iam/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_comcommon_srcs",
    srcs = glob(["BSW/amsr-vector-fs-comcommon/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_sec_cryptostack_srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-cryptostack/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_sec_libseccom_srcs",
    srcs = glob(["BSW/amsr-vector-fs-sec-libseccom/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_communicationmiddleware_srcs",
    srcs = glob(["BSW/amsr-vector-fs-communicationmiddleware/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_crc_srcs",
    srcs = glob(["BSW/amsr-vector-fs-crc/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_e2e_srcs",
    srcs = glob(["BSW/amsr-vector-fs-e2e/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_socal_srcs",
    srcs = glob(["BSW/amsr-vector-fs-socal/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_per_libpersistency_srcs",
    srcs = glob(["BSW/amsr-vector-fs-per-libpersistency/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_per_libpersistency_persistency_key_value_storage_srcs",
    srcs = glob(["BSW/amsr-vector-fs-per-libpersistency/lib/persistency-key-value-storage/src/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_per_libpersistency_persistency_srcs",
    srcs = glob(["BSW/amsr-vector-fs-per-libpersistency/lib/persistency/src/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_per_libpersistency_persistency_file_storage_srcs",
    srcs = glob(["BSW/amsr-vector-fs-per-libpersistency/lib/persistency-file-storage/src/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_logutility_srcs",
    srcs = glob(["BSW/amsr-vector-fs-logutility/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_iointegritystream_srcs",
    srcs = glob(["BSW/amsr-vector-fs-iointegritystream/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_dm_diagnosticmanager_srcs",
    srcs = glob(["BSW/amsr-vector-fs-dm-diagnosticmanager/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_timesync_srcs",
    srcs = glob(["BSW/amsr-vector-fs-timesync/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_ipcbinding_srcs",
    srcs = glob(["BSW/amsr-vector-fs-ipcbinding/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_log_daemon_srcs",
    srcs = glob(["BSW/amsr-vector-fs-log-daemon/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipprotocol_srcs",
    srcs = glob(["BSW/amsr-vector-fs-someipprotocol/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipbinding_srcs",
    srcs = glob(["BSW/amsr-vector-fs-someipbinding/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipdaemonclient_srcs",
    srcs = glob(["BSW/amsr-vector-fs-someipdaemonclient/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipdaemon_srcs",
    srcs = glob(["BSW/amsr-vector-fs-someipdaemon/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_diagnosticrpc",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticrpc/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_diagnosticrpccombinding",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_aradiag",
    srcs = glob(["BSW/amsr-vector-fs-aradiag/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_doipbinding",
    srcs = glob(["BSW/amsr-vector-fs-doipbinding/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_udstransport",
    srcs = glob(["BSW/amsr-vector-fs-udstransport/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_pduhdrtpbinding",
    srcs = glob(["BSW/amsr-vector-fs-pduhdrtpbinding/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_diagnosticutility",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticutility/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_diagnosticmanager",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticmanager/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_swupdateclient",
    srcs = glob(["BSW/amsr-vector-fs-swupdateclient/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_characterconversion",
    srcs = glob(["BSW/amsr-vector-fs-characterconversion/**"]),
    visibility = ["//visibility:public"],
)

# Generators

filegroup(
    name = "amsrgen_sh",
    srcs = [
        "DaVinciConfigurator/Core/amsrgen.sh",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "setup_jre_link_sh",
    srcs = [
        "DaVinciConfigurator/Core/setupJreLinks.sh",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "generator_common_tools",
    srcs = [
        "DaVinciConfigurator/Core/DVACfgCmd",
        "DaVinciConfigurator/Core/jre/lib/amd64/libjsig.so",
        "DaVinciConfigurator/Core/plugins",
    ],
    visibility = ["//visibility:public"],
)

minerva_aa_codegen_declare(
    name = "generator",
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
        "amsr_persistency_config",
        "amsr_logdaemon_config",
        "amsr_logapi_config",
        "amsr_cryptolibes_config",
        "amsr_cryptostack_config",
        "amsr_diag_api",
        "amsr_diag_daemon",
        "amsr_em_daemon",
        "amsr_ipcbinding",
        "amsr_osabstraction_config",
        "amsr_phm_daemon",
        "amsr_seccom_config",
        "amsr_vajson_config",
    ],
    path_to_generators = "Generators",
)

##########################################################################
# These are file groups and libraries required for DiagnosticManagerDeamon
##########################################################################

cc_library(
    name = "diag_daemon_impl",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticmanager/app/diagnostic_manager_daemon_impl/src/**"]),
    hdrs = glob(["BSW/amsr-vector-fs-diagnosticmanager/app/diagnostic_manager_daemon_impl/include/**"]),
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    local_defines = [
        "VIRTUALMOCK=",
        "ENABLE_EXEC_MANAGER=ON",
    ],
    strip_include_prefix = "BSW/amsr-vector-fs-diagnosticmanager/app/diagnostic_manager_daemon_impl/include",
    visibility = ["//visibility:public"],
    deps = [
        "@apricot_adaptive//bsw:amsr_vector_fs_applicationbase",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticrpc",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticrpccombinding",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticutility",
        "@apricot_adaptive//bsw:amsr_vector_fs_libiostream",
        "@apricot_adaptive//bsw:amsr_vector_fs_libosabstraction",
        "@apricot_adaptive//bsw:amsr_vector_fs_libvac",
        "@apricot_adaptive//bsw:amsr_vector_fs_log_api",
        "@apricot_adaptive//bsw:amsr_vector_fs_logutility",
        "@apricot_adaptive//bsw:amsr_vector_fs_per_libpersistency",
        "@apricot_adaptive//bsw:amsr_vector_fs_thread",
        "@apricot_adaptive//bsw:amsr_vector_fs_udstransport",
    ],
)

filegroup(
    name = "amsr_vector_fs_diagnosticmanager_main",
    srcs = [
        "BSW/amsr-vector-fs-diagnosticmanager/app/diagnostic_manager_daemon/src/main.cpp",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "lib_doip_binding_srcs",
    srcs = glob(["BSW/amsr-vector-fs-doipbinding/lib/DoIpBinding/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "diag_deamon_rpc_srcs",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticrpc/lib/DiagDaemonRpc/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "diag_com_deamon_srcs",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComDaemon/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "diag_com_api_srcs",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComApi/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "diag_rpc_com_binding_srcs",
    srcs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagnosticRpcComBinding/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "ara_diag_src",
    srcs = glob(["BSW/amsr-vector-fs-aradiag/lib/AraDiag/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "dupkg_template",
    srcs = glob(["Examples/nvidia-update-strategy/addon/dupkg_generator/dupkg_template/*"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "dupkg_template_tii_a",
    srcs = glob(["Examples/nvidia-update-strategy/addon/dupkg_generator/dupkg_template/tii-a/*"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsrswpkg_generator",
    srcs = ["Examples/nvidia-update-strategy/addon/amsrswpkg_generator/generate.py"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsrswpkg_template",
    srcs = ["Examples/nvidia-update-strategy/addon/amsrswpkg_generator/software_package_manifest_template.json"],
    visibility = ["//visibility:public"],
)

# We need to use "strip_include_prefix" with cc_library to match the
# include paths expected by the C++ code, but "strip_include_prefix" can't be
# used easily if we place the rule do it in bsw/BUILD. So we place it here,
# instead.
#
# We do this in bazel and not cmake, becuase the CMake files for
# amsr-vector-fs-doipbindingthis don't actually build the libraries, but only
# export the C++ files. With the current implementation of rules_foreign_cc,
# we cannot use these C++ files to build our final binary, so we build the
# cc_library using those sources instead.

cc_library(
    name = "lib_doip_binding_src_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-doipbinding/lib/DoIpBinding/src/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-doipbinding/lib/DoIpBinding/src",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lib_doip_binding_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-doipbinding/lib/DoIpBinding/include/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-doipbinding/lib/DoIpBinding/include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "diag_deamon_rpc_src_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-diagnosticrpc/lib/DiagDaemonRpc/src/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-diagnosticrpc/lib/DiagDaemonRpc/src",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "diag_deamon_rpc_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-diagnosticrpc/lib/DiagDaemonRpc/include/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-diagnosticrpc/lib/DiagDaemonRpc/include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "diag_com_deamon_src_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComDaemon/src/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComDaemon/src",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "diag_com_deamon_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComDaemon/include/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComDaemon/include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "diag_com_api_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComApi/include/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagComApi/include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "diag_rpc_com_binding_srcs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagnosticRpcComBinding/include/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-diagnosticrpccombinding/lib/DiagnosticRpcComBinding/include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ara_diag_src_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-aradiag/lib/AraDiag/src/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-aradiag/lib/AraDiag/src",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ara_diag_hdrs_lib",
    hdrs = glob(["BSW/amsr-vector-fs-aradiag/lib/AraDiag/include/**/*.h"]),
    strip_include_prefix = "BSW/amsr-vector-fs-aradiag/lib/AraDiag/include",
    visibility = ["//visibility:public"],
)

##########################################################################
# These are file groups and libraries required for SWUC
##########################################################################

filegroup(
    name = "amsr_vector_fs_swupdateclient_main",
    srcs = glob(["BSW/amsr-vector-fs-swupdateclient/app/swupdateclient/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "amsr_swupdate_common",
    srcs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/common/src/**"]),
    hdrs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/common/include/**"]),
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    strip_include_prefix = "BSW/amsr-vector-fs-swupdateclient/lib/common/include",
    visibility = ["//visibility:public"],
    deps = [
        "@apricot_adaptive//bsw:amsr_vector_fs_applicationbase",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticrpc",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticrpccombinding",
        "@apricot_adaptive//bsw:amsr_vector_fs_diagnosticutility",
        "@apricot_adaptive//bsw:amsr_vector_fs_libiostream",
        "@apricot_adaptive//bsw:amsr_vector_fs_libosabstraction",
        "@apricot_adaptive//bsw:amsr_vector_fs_libvac",
        "@apricot_adaptive//bsw:amsr_vector_fs_log_api",
        "@apricot_adaptive//bsw:amsr_vector_fs_logutility",
        "@apricot_adaptive//bsw:amsr_vector_fs_per_libpersistency",
        "@apricot_adaptive//bsw:amsr_vector_fs_thread",
        "@apricot_adaptive//bsw:amsr_vector_fs_udstransport",
    ],
)

cc_library(
    name = "amsr_swupdate_interface",
    srcs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/update_interface/src/**"]),
    hdrs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/update_interface/include/**"]),
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    strip_include_prefix = "BSW/amsr-vector-fs-swupdateclient/lib/update_interface/include",
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_swupdate_common",
        "@apricot_adaptive//application/amsr_vector_fs_swupdateclient:modeldatatypes_hdrs_lib",
        "@apricot_adaptive//application/amsr_vector_fs_swupdateclient:persistency_config_hdrs_lib",
    ],
)

cc_library(
    name = "amsr_swupdate_ucm_client",
    srcs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/ucm_client/src/**"]),
    hdrs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/ucm_client/include/**"]),
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    strip_include_prefix = "BSW/amsr-vector-fs-swupdateclient/lib/ucm_client/include",
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_swupdate_common",
        ":amsr_swupdate_interface",
    ],
)

cc_library(
    name = "amsr_swupdate_diag_core",
    srcs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/diag_core/src/**"]),
    hdrs = glob(["BSW/amsr-vector-fs-swupdateclient/lib/diag_core/include/**"]),
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    strip_include_prefix = "BSW/amsr-vector-fs-swupdateclient/lib/diag_core/include",
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_swupdate_common",
        ":amsr_swupdate_ucm_client",
        ":ara_diag_hdrs_lib",
        ":ara_diag_src_hdrs_lib",
        "@apricot_adaptive//application/amsr_vector_fs_swupdateclient:diag_hdrs_lib",
        "@apricot_adaptive//application/amsr_vector_fs_swupdateclient:socal_hdrs_lib",
    ],
)

cc_library(
    name = "nvidia_update_strategy",
    srcs = glob(["Examples/nvidia-update-strategy/src/**"]),
    hdrs = glob(["Examples/nvidia-update-strategy/include/**/*.h"]),
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
    strip_include_prefix = "Examples/nvidia-update-strategy/include/",
    visibility = ["//visibility:public"],
    deps = [
        ":amsr_swupdate_interface",
        "@drive//:drive_include_lib",
        "@drive//:libnvducc",
        "@drive//:libnvdulink",
        "@apricot_adaptive//bsw:amsr_vector_fs_libosabstraction",
        "@apricot_adaptive//bsw:amsr_vector_fs_libvac",
        "@apricot_adaptive//bsw:amsr_vector_fs_log_api",
    ],
)
