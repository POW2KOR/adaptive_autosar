load("@bazel_skylib//rules:common_settings.bzl", "string_flag")
load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_declare")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "amsr_vector_fs_libvac_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libvac/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_msr4base_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-msr4base/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_libiostream_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libiostream/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_thread_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-thread/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_vajson_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-vajson/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_applicationbase_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-applicationbase/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_libosabstraction_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-libosabstraction/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_log_api_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-api/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_sec_cryptostack_driver_lib_es_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-cryptostack-driver-lib_es/**"]),
    visibility = ["//visibility:public"],
)

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

filegroup(
    name = "amsr_vector_fs_sec_iam_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-iam/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_comcommon_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-comcommon/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_sec_cryptostack_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-cryptostack/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_sec_libseccom_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-sec-libseccom/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_communicationmiddleware_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-communicationmiddleware/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_crc_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-crc/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_e2e_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-e2e/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_socal_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-socal/**"]),
    visibility = ["//visibility:public"],
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
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-applicationbase/mex/BswExecutableModelExtension.arxml",
        "mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-em-executionmanager/mex/MexDefs.arxml",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_log_daemon_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-log-daemon/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipprotocol_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipprotocol/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipbinding_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipbinding/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipdaemonclient_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipdaemonclient/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "amsr_vector_fs_someipdaemon_srcs",
    srcs = glob(["mb_base_layer_adaptive_xavier/amsr_xavier/BSW/amsr-vector-fs-someipdaemon/**"]),
    visibility = ["//visibility:public"],
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
    ],
    path_to_generators = "mb_base_layer_adaptive_xavier/amsr_xavier/Generators",
)

filegroup(
    name = "proxy_demo_idc6_srcs",
    srcs = [
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/etc/com_application.json",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/etc/logging_config.json",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/activation_manager.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/activation_manager.h",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/application.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/application.h",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/main.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/proxy_demo_error_domain.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/proxy_demo_error_domain.h",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/remote_parking.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/proxy-demo-idc6/src/remote_parking.h",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "skeleton_demo_idc6_srcs",
    srcs = [
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/etc/com_application.json",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/etc/logging_config.json",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/HomeParking_server.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/HomeParking_server.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/RemoteParking_server.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/RemoteParking_server.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/activation_manager.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/activation_manager.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/application.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/application.h",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/main.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/skeleton_demo_error_domain.cpp",
        "examples/proxy-skeleton-demo-idc6/applications/skeleton-demo-idc6/src/skeleton_demo_error_domain.h",
    ],
    visibility = ["//visibility:public"],
)
