load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

minerva_aa_codegen_rule(
    name = "socal_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_socal",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
    ],
    outs_list_dict = {
        "socal_srcs": [
            "TestBaseApplicationExecutable/src/ara/com/runtime_gen.cpp",
            "TestBaseApplicationExecutable/src/comdummyserviceoneinterface/comdummyserviceoneinterface.cpp",
            "TestBaseApplicationExecutable/src/comdummyserviceoneinterface/comdummyserviceoneinterface_skeleton.cpp",
            "TestBaseApplicationExecutable/src/dummyserviceoneinterface/dummyserviceoneinterface.cpp",
            "TestBaseApplicationExecutable/src/dummyserviceoneinterface/dummyserviceoneinterface_proxy.cpp",
            "TestBaseApplicationExecutable/src/dummyservicethreeinterface/dummyservicethreeinterface.cpp",
            "TestBaseApplicationExecutable/src/dummyservicethreeinterface/dummyservicethreeinterface_proxy.cpp",
            "TestBaseApplicationExecutable/src/dummyservicetwointerface/dummyservicetwointerface.cpp",
            "TestBaseApplicationExecutable/src/dummyservicetwointerface/dummyservicetwointerface_proxy.cpp",
        ],
        "socal_hdrs": [
            "TestBaseApplicationExecutable/includes/comdummyserviceoneinterface/comDummyServiceOneInterface.h",
            "TestBaseApplicationExecutable/includes/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_impl_interface.h",
            "TestBaseApplicationExecutable/includes/comdummyserviceoneinterface/comDummyServiceOneInterface_types.h",
            "TestBaseApplicationExecutable/includes/comdummyserviceoneinterface/comdummyserviceoneinterface_common.h",
            "TestBaseApplicationExecutable/includes/comdummyserviceoneinterface/comdummyserviceoneinterface_skeleton.h",
            "TestBaseApplicationExecutable/includes/dummyserviceoneinterface/dummyServiceOneInterface.h",
            "TestBaseApplicationExecutable/includes/dummyserviceoneinterface/dummyServiceOneInterface_proxy_internal.h",
            "TestBaseApplicationExecutable/includes/dummyserviceoneinterface/dummyServiceOneInterface_types.h",
            "TestBaseApplicationExecutable/includes/dummyserviceoneinterface/dummyserviceoneinterface_common.h",
            "TestBaseApplicationExecutable/includes/dummyserviceoneinterface/dummyserviceoneinterface_proxy.h",
            "TestBaseApplicationExecutable/includes/dummyservicethreeinterface/dummyServiceThreeInterface.h",
            "TestBaseApplicationExecutable/includes/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_internal.h",
            "TestBaseApplicationExecutable/includes/dummyservicethreeinterface/dummyServiceThreeInterface_types.h",
            "TestBaseApplicationExecutable/includes/dummyservicethreeinterface/dummyservicethreeinterface_common.h",
            "TestBaseApplicationExecutable/includes/dummyservicethreeinterface/dummyservicethreeinterface_proxy.h",
            "TestBaseApplicationExecutable/includes/dummyservicetwointerface/dummyServiceTwoInterface.h",
            "TestBaseApplicationExecutable/includes/dummyservicetwointerface/dummyServiceTwoInterface_proxy_internal.h",
            "TestBaseApplicationExecutable/includes/dummyservicetwointerface/dummyServiceTwoInterface_types.h",
            "TestBaseApplicationExecutable/includes/dummyservicetwointerface/dummyservicetwointerface_common.h",
            "TestBaseApplicationExecutable/includes/dummyservicetwointerface/dummyservicetwointerface_proxy.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "modeldatatypes_api_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_modelleddatatypes_api",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
    ],
    outs_list_dict = {
        "modeldatatypes_hdrs": [
            "TestBaseApplicationExecutable/includes/ARR_Stat_16_UInt_noSNA_100/impl_type_arr_stat_16_uint_nosna_100.h",
            "TestBaseApplicationExecutable/includes/ARR_Stat_REC_100/impl_type_arr_stat_rec_100.h",
            "TestBaseApplicationExecutable/includes/ARR_Stat_REC_600/impl_type_arr_stat_rec_600.h",
            "TestBaseApplicationExecutable/includes/DataTypes/impl_type_arr_stat_uint16_100_element_adar.h",
            "TestBaseApplicationExecutable/includes/DataTypes/impl_type_c08_uint_sna_na1.h",
            "TestBaseApplicationExecutable/includes/DataTypes/impl_type_c16_uint_sna_na.h",
            "TestBaseApplicationExecutable/includes/DataTypes/impl_type_rec_adummyrecord.h",
            "TestBaseApplicationExecutable/includes/DataTypes/impl_type_rec_statarray_adar.h",
            "TestBaseApplicationExecutable/includes/DataTypes/impl_type_uint16_element_adar.h",
            "TestBaseApplicationExecutable/includes/DataTypes/impl_type_uint8_element_adar.h",
            "TestBaseApplicationExecutable/includes/NS_REC_Uint8_Uint16_Uint16_AdAR/impl_type_rec_uint8_uint16_uint16_adar.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipbinding_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_someipbinding",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
    ],
    outs_list_dict = {
        "someip_config": [
            "TestBaseApplicationExecutable/configuration/someip_config.json",
        ],
        "someipbinding_srcs": [
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_someip_binding.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_someip_binding_init.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_someip_event_manager.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_proxy_someip_binding.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_proxy_someip_binding_init.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_proxy_someip_event_manager.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_someip_binding.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_someip_binding_init.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_someip_event_manager.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_proxy_someip_binding.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_proxy_someip_binding_init.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_proxy_someip_event_manager.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_binding_transformation_layer/internal/life_cycle_gen.cpp",
        ],
        "someipbinding_hdrs": [
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_someip_binding.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_someip_binding_init.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_someip_event_manager.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_skeleton_someip_methods.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/comdummyserviceoneinterface/comDummyServiceOneInterface_someip_skeleton_factory.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_proxy_someip_binding.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_proxy_someip_binding_init.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_proxy_someip_event_manager.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_proxy_someip_methods.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyserviceoneinterface/dummyServiceOneInterface_someip_proxy_factory.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_someip_binding.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_someip_binding_init.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_someip_event_manager.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_proxy_someip_methods.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicethreeinterface/dummyServiceThreeInterface_someip_proxy_factory.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_proxy_someip_binding.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_proxy_someip_binding_init.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_proxy_someip_event_manager.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_proxy_someip_methods.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_binding_transformation_layer/internal/dummyservicetwointerface/dummyServiceTwoInterface_someip_proxy_factory.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "someipprotocol_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_someipprotocol",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
    ],
    outs_list_dict = {
        "someipprotocol_srcs": [
            "TestBaseApplicationExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/dummyserviceoneinterface/events/deserializer_OneDummyEvent.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/dummyserviceoneinterface/methods/deserializer_getDummyDataOneParameterOut.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/dummyservicethreeinterface/events/deserializer_TwoDummyEvent.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/dummyservicethreeinterface/methods/deserializer_getDummyDataTwoUML_Parameter105.cpp",
            "TestBaseApplicationExecutable/src/amsr/someip_protocol/internal/dataprototype_deserialization/dummyservicetwointerface/events/deserializer_ThreeDummyEvent.cpp",
        ],
        "someipprotocol_hdrs": [
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/dummyserviceoneinterface/events/deserializer_OneDummyEvent.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/dummyserviceoneinterface/methods/deserializer_getDummyDataOneParameterOut.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/dummyservicethreeinterface/events/deserializer_TwoDummyEvent.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/dummyservicethreeinterface/methods/deserializer_getDummyDataTwoUML_Parameter105.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/dummyservicetwointerface/events/deserializer_ThreeDummyEvent.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_serialization/comdummyserviceoneinterface/events/serializer_aComDummyOneEvent.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_serialization/dummyserviceoneinterface/methods/serializer_getDummyDataOneParameterIn.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/dataprototype_serialization/dummyservicetwointerface/methods/serializer_setDummyDataThreeUML_Parameter106.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/deserializer_REC_StatArray_AdAR.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/datatype_deserialization/DataTypes/deserializer_REC_aDummyRecord.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/datatype_deserialization/NS_REC_Uint8_Uint16_Uint16_AdAR/deserializer_REC_Uint8_Uint16_Uint16_AdAR.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/datatype_serialization/NS_REC_Uint8_Uint16_Uint16_AdAR/serializer_REC_Uint8_Uint16_Uint16_AdAR.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/method_deserialization/dummyserviceoneinterface/methods/deserializer_Response_getDummyDataOne.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/method_deserialization/dummyservicethreeinterface/methods/deserializer_Response_getDummyDataTwo.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/method_deserialization/dummyservicetwointerface/methods/deserializer_Response_setDummyDataThree.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/method_serialization/dummyserviceoneinterface/methods/serializer_Request_getDummyDataOne.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/method_serialization/dummyservicethreeinterface/methods/serializer_Request_getDummyDataTwo.h",
            "TestBaseApplicationExecutable/includes/amsr/someip_protocol/internal/method_serialization/dummyservicetwointerface/methods/serializer_Request_setDummyDataThree.h",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "applicationbase_init_deinit_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "shutdown_app_demo_idc6.*",
        "update_app_demo_idc6.*",
    ],
    outs_list_dict = {
        "applicationbase_init_deinit_srcs": [
            "TestBaseApplicationExecutable/src/ara/core/initialization.cpp",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "exec_config_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_exec_config",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "shutdown_app_demo_idc6.*",
        "update_app_demo_idc6.*",
        "amsr_vector_fs_sec_cryptostack_daemon.*",
    ],
    outs_list_dict = {
        "exec_config": [
            "TestBaseApplicationExecutable/configuration/exec_config.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "shutdown_app_demo_idc6.*",
        "update_app_demo_idc6.*",
        "amsr_vector_fs_sec_cryptostack_daemon.*",
    ],
    outs_list_dict = {
        "updatemanager_swcluster_meta": [
            "TestBaseApplicationExecutable/swcl_package_metadata.json",
        ],
    },
)

minerva_aa_codegen_rule(
    name = "updatemanager_daemon_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_updatemanager_daemon",
    ],
    ignore_matches = [
        "BaseApplicationExecutable.*",
        "DiagnosticManagerDeamonExecutable.*",
        "SelfDiagnosticAgentExecutable.*",
        "amsr_vector_fs_ucm_updatemanager.*",
        "software_update_client.*",
        "restart_app_demo_idc6.*",
        "shutdown_app_demo_idc6.*",
        "update_app_demo_idc6.*",
        "amsr_vector_fs_sec_cryptostack_daemon.*",
    ],
    outs_list_dict = {
        "updatemanager_daemon": [
            "TestBaseApplicationExecutable/etc/updatemanager.json",
        ],
        "updatemanager_swcl_db_daemon": [
            "TestBaseApplicationExecutable/etc/swcl_db.json",
        ],
    },
)

cc_library(
    name = "socal_hdrs_lib",
    hdrs = [
        ":socal_hdrs",
    ],
    strip_include_prefix = "socal_hdrs/output/TestBaseApplicationExecutable/includes",
)

cc_library(
    name = "modeldatatypes_hdrs_lib",
    hdrs = [
        ":modeldatatypes_hdrs",
    ],
    strip_include_prefix = "modeldatatypes_hdrs/output/TestBaseApplicationExecutable/includes",
)

cc_library(
    name = "someipbinding_hdrs_lib",
    hdrs = [
        ":someipbinding_hdrs",
    ],
    strip_include_prefix = "someipbinding_hdrs/output/TestBaseApplicationExecutable/includes",
)

cc_library(
    name = "someipprotocol_hdrs_lib",
    hdrs = [
        ":someipprotocol_hdrs",
    ],
    strip_include_prefix = "someipprotocol_hdrs/output/TestBaseApplicationExecutable/includes",
)

cc_library(
    name = "socal_srcs_lib",
    srcs = [
        ":socal_srcs",
        ":someipbinding_srcs",
        ":someipprotocol_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    deps = [
        ":modeldatatypes_hdrs_lib",
        ":socal_hdrs_lib",
        ":someipbinding_hdrs_lib",
        ":someipprotocol_hdrs_lib",
        "//bsw:amsr_vector_fs_sec_libseccom",
        "//bsw:amsr_vector_fs_socal_headers",
        "//bsw:amsr_vector_fs_someipbinding",
        "//bsw:amsr_vector_fs_someipprotocol",
        "//bsw:amsr_vector_fs_vajson",
    ],
)

filegroup(
    name = "com_application_config",
    srcs = [
        "config/com_application.json",
    ],
)

filegroup(
    name = "logging_config",
    srcs = [
        "config/logging_config.json",
    ],
)

cc_binary(
    name = "app",
    srcs = [
        "@starter_kit_adaptive_xavier//:proxy_demo_idc6_srcs",

        # This a workaround to resolve cyclic dependency. This is the reason why the target proxy_demo_idc6
        # build in 2 steps.
        # The code generators depend on libSocal.a, contained in the @minerva_mpu_adaptive//:socal_lib_for_proxy below.
        # That is why we put it in sources. It is important that this `:socal_lib_for_proxy` is positioned earlier in
        # the list than the generated sources in `:starter_kit_test_base_application_proxy_socal_srcs_lib` and
        # `:starter_kit_test_base_application_proxy_applicationbase_init_deinit_srcs`
        "@minerva_mpu_adaptive//:socal_lib_for_proxy",
        ":socal_srcs_lib",
        ":applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    features = [
        "pthread",
    ],
    linkstatic = 1,
    deps = [
        ":modeldatatypes_hdrs_lib",
        ":socal_hdrs_lib",
        "//bsw:amsr_vector_fs_em_executionmanager",
        "//bsw:amsr_vector_fs_libvac",
        "//bsw:amsr_vector_fs_log_api",
        "//bsw:amsr_vector_fs_socal_for_proxy",
        "//bsw:amsr_vector_fs_someipbinding",
        "//bsw:amsr_vector_fs_vajson",
    ],
)
