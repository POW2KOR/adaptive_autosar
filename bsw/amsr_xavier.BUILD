load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_declare")

# Model extensions

filegroup(
    name = "mex_arxml",
    srcs = [
        "BSW/amsr-vector-fs-applicationbase/mex/BswExecutableModelExtension.arxml",
        "BSW/amsr-vector-fs-em-executionmanager/mex/MexDefs.arxml",
        "BSW/amsr-vector-fs-log-api/mex/MexDefs.arxml",
        "BSW/amsr-vector-fs-log-daemon/mex/MexDefs.arxml",
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
    srcs = glob(["BSW/amsr-vector-fs-em-executionmanager/addon/amsr-vector-fs-em-executionmanager-demo-application/**"]),
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
        "amsr_ipcbinding",
    ],
    path_to_generators = "Generators",
)
