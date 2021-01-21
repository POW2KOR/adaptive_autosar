
load("@minerva_mpu_adaptive//bsw:defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "machine_arxml",
    srcs = ["arxmls/machine.arxml"],
)

filegroup(
    name = "executionmanager_state_client_app_arxml",
    srcs = ["arxmls/executionmanager_state_client_app.arxml"],
)

filegroup(
    name = "complete_arxml",
    srcs = [
        "@starter_kit_adaptive_xavier//:ncd_arxml",
        "@starter_kit_adaptive_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:standard_types_arxml",
    ]
)

filegroup(
    name = "amsr_vector_fs_log_daemon_exec_config",
    srcs = [
        "configs/amsr_vector_fs_log_daemon/exec_config.json"
    ]
)

filegroup(
    name = "amsr_vector_fs_log_daemon_logd_config",
    srcs = [
        "configs/amsr_vector_fs_log_daemon/logd_config.json"
    ]
)

filegroup(
    name = "amsr_vector_fs_log_daemon_logging_config",
    srcs = [
        "configs/amsr_vector_fs_log_daemon/logging_config.json"
    ]
)

filegroup(
    name = "proxy_com_application_config",
    srcs = [
        "configs/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/com_application.json"
    ]
)

filegroup(
    name = "proxy_logging_config",
    srcs = [
        "configs/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/logging_config.json"
    ]
)

filegroup(
    name = "skeleton_com_application_config",
    srcs = [
        "configs/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/com_application.json"
    ]
)

filegroup(
    name = "skeleton_logging_config",
    srcs = [
        "configs/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/logging_config.json"
    ]
)

filegroup(
    name = "someipd_posix_logging_config",
    srcs = [
        "configs/someipd_posix/logging_config.json"
    ]
)

filegroup(
    name = "someipd_posix_exec_config",
    srcs = [
        "configs/someipd_posix/exec_config.json"
    ]
)

filegroup(
    name = "someipd_posix_someip_config",
    srcs = [
        "configs/someipd_posix/someipd-posix.json"
    ]
)

filegroup(
    name = "executionmanager_state_client_app_logging_config",
    srcs = [
        "configs/executionmanager_state_client_app/logging_config.json"
    ]
)

filegroup(
    name = "executionmanager_state_client_app_exec_config",
    srcs = [
        "configs/executionmanager_state_client_app/exec_config.json"
    ]
)


filegroup(
    name = "em_logging_config",
    srcs = [
        "configs/etc/logging_config.json"
    ]
)


filegroup(
    name = "machine_exec_config",
    srcs = [
        "configs/etc/machine_exec_config.json"
    ]
)

minerva_aa_codegen_rule(
    name = "executionmanager_state_client_app_gen_rule",
    arxml_srcs = [":executionmanager_state_client_app_arxml"],
    outs_list_dict = {
        "executionmanager_state_client_updatemanager_daemon_db": [
            "executionmanager_state_client_app/etc/swcl_db.json"
        ],
        "executionmanager_state_client_updatemanager_swcluser_meta": [
            "executionmanager_state_client_app/swcl_package_metadata.json"
        ],
        # We're not using this exec_config because the code generator isn't
        # able to generate a proper config file when category PLATFORM_LEVEL
        # is selected. So instead,
        # :executionmanager_state_client_app_exec_config gets used. 
        "executionmanager_state_client_exec_config": [
            "executionmanager_state_client_app/configuration/exec_config.json"
        ],
        "executionmanager_state_client_applicationbase_init_deinit_srcs": [
            "executionmanager_state_client_app/src/ara/core/initialization.cpp"
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_swcluster_meta",
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_daemon",
        "@starter_kit_adaptive_xavier//:generator_amsr_em_exec_config",
        "@starter_kit_adaptive_xavier//:generator_amsr_applicationbase_init_deinit",
    ]
)

cc_binary(
    name = "executionmanager_state_client_binary",
    deps = [
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-applicationbase",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-log-api",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-em-executionmanager",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-libiostream"
    ],
    srcs = [
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_em_executionmanager_addon_demo_application_srcs",
        ":executionmanager_state_client_applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
)


minerva_aa_codegen_rule(
    name = "minerva_machine_exec_config_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "minerva_machine_exec_config": ["IDC_M_P/machine_exec_config.json"],
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_em_machine_config"
    ]
)

minerva_aa_codegen_rule(
    name = "starter_kit_application_modeldatatypes_api_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_modeldatatypes_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y/impl_type_dummyservicerecorddatatype_4tuekbbgqsijk4yv29iawd34y.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/STD_UUCategory/impl_type_std_uucategory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Object_ST3/impl_type_arr_lrr_object_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Segment_ST3/impl_type_arr_lrr_segment_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_ManeuverListState_ST3_42w45002bze5mo286svxxsdbx/impl_type_rec_maneuverliststate_st3_42w45002bze5mo286svxxsdbx.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Pr7_ST3/impl_type_rec_lrr_object_pr7_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_Add_Maneuver_ST3_euk2owpx15avykqntci714wbp/impl_type_rec_add_maneuver_st3_euk2owpx15avykqntci714wbp.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_200/impl_type_arr_08_uint_nosna_200.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_objects_nest_pr7_st3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_trgrcrowddata_st3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_1000/impl_type_arr_08_uint_nosna_1000.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_32/impl_type_arr_08_uint_nosna_32.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_128/impl_type_arr_08_uint_nosna_128.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_1454/impl_type_arr_08_uint_nosna_1454.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segment_Pr6_ST3/impl_type_rec_lrr_segment_pr6_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7/impl_type_rec_lrr_object_stat_pr6_st3_6hptq6rv1r5w7spodrls7hwl7.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_34/impl_type_arr_08_uint_nosna_34.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataTypeTwo/impl_type_dummyservicerecorddatatypetwo.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_RemPark_ManeuverListNames_ST3/impl_type_rec_rempark_maneuverlistnames_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg/impl_type_rec_lrr_sens_stat_pr6_st3_2k3hoaz4lmdyzji1cc23c8ymg.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr/impl_type_rec_lrr_lanepoly_pr6_st3_3pbdqiss5ghx5e8f9twrfswzr.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp/impl_type_rec_device_authorized_status_st3_euk2owpx15avykqntci714wbp.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_84/impl_type_arr_08_uint_nosna_84.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_30/impl_type_arr_08_uint_nosna_30.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_segments_nest_pr6_st3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_RemPark_DeviceListNames_Rs_ST3/impl_type_rec_rempark_devicelistnames_rs_st3.h",

        ],
        "starter_kit_proxy_modeldatatypes_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y/impl_type_dummyservicerecorddatatype_4tuekbbgqsijk4yv29iawd34y.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/STD_UUCategory/impl_type_std_uucategory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Object_ST3/impl_type_arr_lrr_object_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Segment_ST3/impl_type_arr_lrr_segment_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Pr7_ST3/impl_type_rec_lrr_object_pr7_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_200/impl_type_arr_08_uint_nosna_200.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_objects_nest_pr7_st3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_trgrcrowddata_st3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_32/impl_type_arr_08_uint_nosna_32.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_128/impl_type_arr_08_uint_nosna_128.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_1454/impl_type_arr_08_uint_nosna_1454.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segment_Pr6_ST3/impl_type_rec_lrr_segment_pr6_st3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7/impl_type_rec_lrr_object_stat_pr6_st3_6hptq6rv1r5w7spodrls7hwl7.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_34/impl_type_arr_08_uint_nosna_34.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataTypeTwo/impl_type_dummyservicerecorddatatypetwo.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg/impl_type_rec_lrr_sens_stat_pr6_st3_2k3hoaz4lmdyzji1cc23c8ymg.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr/impl_type_rec_lrr_lanepoly_pr6_st3_3pbdqiss5ghx5e8f9twrfswzr.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp/impl_type_rec_device_authorized_status_st3_euk2owpx15avykqntci714wbp.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_84/impl_type_arr_08_uint_nosna_84.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_30/impl_type_arr_08_uint_nosna_30.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_segments_nest_pr6_st3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_RemPark_DeviceListNames_Rs_ST3/impl_type_rec_rempark_devicelistnames_rs_st3.h",
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_modelleddatatypes_api"
    ]
)


minerva_aa_codegen_rule(
    name = "starter_kit_application_exec_config_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_exec_config": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/configuration/exec_config.json",
        ],
        "starter_kit_proxy_exec_config": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/configuration/exec_config.json",
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_em_exec_config",
    ],
)

minerva_aa_codegen_rule(
    name = "starter_kit_application_someipbinding_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_someip_config": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/configuration/someip_config.json",
        ],
        "starter_kit_proxy_someip_config": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/configuration/someip_config.json",
        ],
        "starter_kit_skeleton_someipbinding_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/aracom_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_skeleton_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_skeleton_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_skeleton_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_skeleton_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_skeleton_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_skeleton_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_skeleton_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_skeleton_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_skeleton_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_someip_binding_init.cpp",
        ],
        "starter_kit_proxy_someipbinding_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/aracom_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_skeleton_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_skeleton_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_skeleton_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_skeleton_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_skeleton_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_skeleton_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_someip_event_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_skeleton_someip_binding.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_skeleton_someip_binding_init.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_skeleton_someip_event_manager.cpp",
        ],
        "starter_kit_skeleton_someipbinding_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_someip_skeleton_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_skeleton_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_skeleton_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_skeleton_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_skeleton_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_someip_proxy_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_skeleton_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_skeleton_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_someip_skeleton_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_skeleton_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_skeleton_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_someip_proxy_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_skeleton_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_skeleton_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_skeleton_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_someip_skeleton_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_skeleton_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_someip_proxy_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_someip_event_manager.h",
        ],
        "starter_kit_proxy_someipbinding_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_someip_skeleton_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_skeleton_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_skeleton_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_skeleton_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_skeleton_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_someip_proxy_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_skeleton_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_skeleton_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_skeleton_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_skeleton_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_someip_skeleton_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_someip_proxy_factory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_skeleton_someip_methods.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_skeleton_someip_binding_init.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_skeleton_someip_binding.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_skeleton_someip_event_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_binding_transformation_layer/internal/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_someip_skeleton_factory.h",
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_someipbinding",
    ],
)

minerva_aa_codegen_rule(
    name = "starter_kit_application_updatemanager_swcluster_meta_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_updatemanager_swcluster_meta": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/swcl_package_metadata.json",
        ],
        "starter_kit_proxy_updatemanager_swcluster_meta": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/swcl_package_metadata.json",
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_swcluster_meta",
    ],
)

minerva_aa_codegen_rule(
    name = "starter_kit_application_updatemanager_daemon_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_updatemanager_daemon": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/etc/updatemanager.json",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/etc/swcl_db.json",
        ],
        "starter_kit_proxy_updatemanager_daemon": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/etc/updatemanager.json",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/etc/swcl_db.json",
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_daemon",
    ],
)

minerva_aa_codegen_rule(
    name = "starter_kit_application_applicationbase_init_deinit_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_applicationbase_init_deinit_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/ara/core/initialization.cpp",
        ],
        "starter_kit_proxy_applicationbase_init_deinit_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/ara/core/initialization.cpp",
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_applicationbase_init_deinit",
    ],
)

minerva_aa_codegen_rule(
    name = "starter_kit_application_someipprotocol_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_someipprotocol_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/deserializer_aDummyMethodSWC_Dummy_Argument.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/events/deserializer_LRR_Objects_Pr7_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicedeviceIdIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesindexIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestIdentifierExchangehuIdentification.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestExternalAuthenable.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataindexIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_Sens_Stat_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_Segments_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_Object_Stat_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_LanePoly_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverListStatesenable.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverListNamesindexIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverIconindexIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestSetManeuvermaneuverName.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestSetManeuvermaneuverFavorite.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverIconmaneuverIdIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestSetManeuvermaneuverID.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestDeleteStoredManeuvermaneuverIdIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/deserializer_LRR_CrowdData_Upload_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/deserializer_LRR_TrgrCrowdData_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_2_z_dummy_service_10/events/serializer_Dummy_Event_SWC_Data_Element.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestIdentifierExchangepmIdentification.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestExternalAuthstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicestat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicelistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListSizelistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicedeviceIdOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataindexMax.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesindexOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteAllDeviceslistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDatastat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataindexOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListSizestat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataqrData.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestIdentifierExchangestat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesdeviceListNames.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestExternalAuthqrHash.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteAllDevicesstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/events/serializer_Device_Authorized_Status_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconmaneuverIdOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuverhpMemorytotal.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListSizestat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestSetManeuverstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesindexOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconindexMax.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListSizehpMemorytotal.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesmaneuverListNames.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuverlistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteAllStoredManeuvershpMemorytotal.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListSizelistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteAllStoredManeuversstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuverstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuvermaneuverIdOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconindexOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesiconHash.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListStatesstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteAllStoredManeuverslistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconiconData.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/events/serializer_Maneuver_Set_Stat_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/events/serializer_Maneuver_List_State_ST3.cpp",
        ],
        "starter_kit_skeleton_someipprotocol_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y/serializer_DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/STD_UUCategory/serializer_STD_UUCategory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_ManeuverListState_ST3_42w45002bze5mo286svxxsdbx/serializer_REC_ManeuverListState_ST3_42w45002bze5mo286svxxsdbx.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_Add_Maneuver_ST3_euk2owpx15avykqntci714wbp/serializer_REC_Add_Maneuver_ST3_euk2owpx15avykqntci714wbp.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/DummyServiceRecordDataTypeTwo/serializer_DummyServiceRecordDataTypeTwo.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_RemPark_ManeuverListNames_ST3/serializer_REC_RemPark_ManeuverListNames_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp/serializer_REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_RemPark_DeviceListNames_Rs_ST3/serializer_REC_RemPark_DeviceListNames_Rs_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_LRR_Object_Pr7_ST3/deserializer_REC_LRR_Object_Pr7_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno/deserializer_REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno/deserializer_REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_LRR_Segment_Pr6_ST3/deserializer_REC_LRR_Segment_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7/deserializer_REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg/deserializer_REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr/deserializer_REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno/deserializer_REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/deserializer_aDummyMethodSWC_Dummy_Argument.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/events/deserializer_LRR_Objects_Pr7_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesindexIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestIdentifierExchangehuIdentification.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestExternalAuthenable.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicedeviceIdIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataindexIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_LanePoly_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_Sens_Stat_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_Object_Stat_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/deserializer_LRR_Segments_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverIconindexIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestSetManeuvermaneuverName.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestSetManeuvermaneuverID.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestDeleteStoredManeuvermaneuverIdIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverListNamesindexIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverListStatesenable.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_requestSetManeuvermaneuverFavorite.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_getManeuverIconmaneuverIdIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/deserializer_LRR_TrgrCrowdData_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/deserializer_LRR_CrowdData_Upload_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/serializer_Response_aDummyMethod.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Response_requestDeleteAllDevices.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Response_getQrCodeData.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Response_requestIdentifierExchange.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Response_getDeviceListSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Response_requestDeleteDevice.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Response_getDeviceListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Response_requestExternalAuth.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_Response_getManeuverListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_Response_requestDeleteStoredManeuver.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_Response_requestDeleteAllStoredManeuvers.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_Response_getManeuverListStates.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_Response_requestSetManeuver.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_Response_getManeuverIcon.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_Response_getManeuverListSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_2_z_dummy_service_10/events/serializer_Dummy_Event_SWC_Data_Element.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicestat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestExternalAuthqrHash.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestIdentifierExchangepmIdentification.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicelistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteAllDeviceslistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataindexMax.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataqrData.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDatastat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesdeviceListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListSizelistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicedeviceIdOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataindexOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesindexOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestIdentifierExchangestat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListSizestat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestExternalAuthstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteAllDevicesstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/events/serializer_Device_Authorized_Status_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuverstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteAllStoredManeuverslistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListSizestat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesiconHash.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListSizelistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListSizehpMemorytotal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteAllStoredManeuversstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuverhpMemorytotal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconiconData.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconmaneuverIdOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconindexOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesindexOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestSetManeuverstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverIconindexMax.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListStatesstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuverlistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteAllStoredManeuvershpMemorytotal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_requestDeleteStoredManeuvermaneuverIdOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/serializer_getManeuverListNamesmaneuverListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/events/serializer_Maneuver_List_State_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/events/serializer_Maneuver_Set_Stat_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/deserializer_Request_aDummyMethod.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Request_requestDeleteAllDevices.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Request_getDeviceListSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Request_requestDeleteDevice.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Request_requestIdentifierExchange.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Request_getQrCodeData.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Request_getDeviceListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Request_requestExternalAuth.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_Request_getManeuverListStates.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_Request_getManeuverIcon.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_Request_requestDeleteStoredManeuver.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_Request_getManeuverListSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_Request_requestDeleteAllStoredManeuvers.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_Request_getManeuverListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18069_prk_homeparking_ui_service_st3_10/methods/deserializer_Request_requestSetManeuver.h",
        ],
        "starter_kit_proxy_someipprotocol_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_2_z_dummy_service_10/events/deserializer_Dummy_Event_SWC_Data_Element.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesindexOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListSizestat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestExternalAuthstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataqrData.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestExternalAuthqrHash.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListSizelistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestIdentifierExchangepmIdentification.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteAllDeviceslistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestIdentifierExchangestat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataindexMax.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicestat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataindexOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicedeviceIdOut.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicelistSize.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDatastat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesdeviceListNames.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteAllDevicesstat.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/events/deserializer_Device_Authorized_Status_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/serializer_aDummyMethodSWC_Dummy_Argument.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/events/serializer_LRR_Objects_Pr7_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestIdentifierExchangehuIdentification.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesindexIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicedeviceIdIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestExternalAuthenable.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataindexIn.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_Object_Stat_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_Sens_Stat_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_LanePoly_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_Segments_Pr6_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/serializer_LRR_TrgrCrowdData_ST3.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/serializer_LRR_CrowdData_Upload_ST3.cpp",
        ],
        "starter_kit_proxy_someipprotocol_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_LRR_Object_Pr7_ST3/serializer_REC_LRR_Object_Pr7_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno/serializer_REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno/serializer_REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_LRR_Segment_Pr6_ST3/serializer_REC_LRR_Segment_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7/serializer_REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg/serializer_REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr/serializer_REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_serialization/daimler/cppDataTypes/common/REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno/serializer_REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y/deserializer_DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/STD_UUCategory/deserializer_STD_UUCategory.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/DummyServiceRecordDataTypeTwo/deserializer_DummyServiceRecordDataTypeTwo.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp/deserializer_REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/datatype_deserialization/daimler/cppDataTypes/common/REC_RemPark_DeviceListNames_Rs_ST3/deserializer_REC_RemPark_DeviceListNames_Rs_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_2_z_dummy_service_10/events/deserializer_Dummy_Event_SWC_Data_Element.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicestat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestExternalAuthqrHash.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataindexMax.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesindexOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestIdentifierExchangepmIdentification.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListNamesdeviceListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListSizelistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getDeviceListSizestat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestExternalAuthstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteAllDeviceslistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataindexOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicedeviceIdOut.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteDevicelistSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestIdentifierExchangestat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDatastat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_getQrCodeDataqrData.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_requestDeleteAllDevicesstat.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/events/deserializer_Device_Authorized_Status_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/serializer_Request_aDummyMethod.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Request_requestExternalAuth.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Request_requestDeleteDevice.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Request_getDeviceListSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Request_getDeviceListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Request_getQrCodeData.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Request_requestIdentifierExchange.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_Request_requestDeleteAllDevices.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/serializer_aDummyMethodSWC_Dummy_Argument.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/events/serializer_LRR_Objects_Pr7_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getQrCodeDataindexIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestIdentifierExchangehuIdentification.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestExternalAuthenable.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_requestDeleteDevicedeviceIdIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/serializer_getDeviceListNamesindexIn.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_Sens_Stat_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_Object_Stat_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_LanePoly_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9618_dap_sens_lr_radar_service_st3_10/events/serializer_LRR_Segments_Pr6_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/serializer_LRR_CrowdData_Upload_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/dataprototype_serialization/daimler_services_common_srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/events/serializer_LRR_TrgrCrowdData_ST3.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_2_z_dummy_service_10/methods/deserializer_Response_aDummyMethod.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Response_requestExternalAuth.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Response_requestDeleteDevice.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Response_requestIdentifierExchange.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Response_requestDeleteAllDevices.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Response_getDeviceListNames.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Response_getDeviceListSize.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/amsr/someip_protocol/internal/method_deserialization/daimler_services_common_srvifc_18068_prk_remoteparking_ui_service_st3_10/methods/deserializer_Response_getQrCodeData.h",
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_someipprotocol",
    ],
)

minerva_aa_codegen_rule(
    name = "starter_kit_application_socal_gen_rule",
    arxml_srcs = [":complete_arxml"],
    outs_list_dict = {
        "starter_kit_skeleton_socal_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10_skeleton_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10_skeleton.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_proxy_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_proxy.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_skeleton.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_skeleton_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_proxy.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_proxy_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_skeleton.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_skeleton_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_proxy_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_proxy.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/ara/com/someip_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/ara/com/runtime_gen.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/ara/com/resource_manager.cpp",
        ],
        "starter_kit_skeleton_socal_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10_skeleton.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/SrvIfc_18069_Prk_HomeParking_UI_Service_ST3_10_proxy_backend_interface.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10_skeleton_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18069_prk_homeparking_ui_service_st3_10/srvifc_18069_prk_homeparking_ui_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_proxy.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_proxy_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_internal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_skeleton.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_skeleton_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_backend_interface.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_proxy_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_internal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_proxy.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_skeleton_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_backend_interface.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_skeleton.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_proxy_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_internal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_proxy.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/ara/com/someip_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/ara/com/resource_manager.h",
        ],
        "starter_kit_proxy_socal_srcs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_skeleton_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_skeleton.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_proxy_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_proxy.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_skeleton_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_skeleton.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_proxy_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_proxy.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_skeleton.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_skeleton_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/ara/com/someip_resource_manager.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/ara/com/runtime_gen.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/ara/com/resource_manager.cpp",
        ],
        "starter_kit_proxy_socal_hdrs": [
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_proxy_backend_interface.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/SrvIfc_9619_DAP_Sens_LR_Radar_Obj_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_skeleton.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_skeleton_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10/srvifc_9619_dap_sens_lr_radar_obj_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_proxy.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_proxy_internal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_proxy_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/SrvIfc_18068_Prk_RemoteParking_UI_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_18068_prk_remoteparking_ui_service_st3_10/srvifc_18068_prk_remoteparking_ui_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_skeleton_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_skeleton.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9617_dap_sens_lr_radar_crowddata_service_st3_10/SrvIfc_9617_DAP_Sens_LR_Radar_CrowdData_Service_ST3_10_proxy_backend_interface.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_proxy_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10_proxy_internal.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/srvifc_2_z_dummy_service_10_proxy.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_2_z_dummy_service_10/SrvIfc_2_Z_Dummy_Service_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_common.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_skeleton_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_proxy_backend_interface.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/srvifc_9618_dap_sens_lr_radar_service_st3_10_skeleton.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/services/common/srvifc_9618_dap_sens_lr_radar_service_st3_10/SrvIfc_9618_DAP_Sens_LR_Radar_Service_ST3_10_types.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/ara/com/someip_resource_manager.h",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/ara/com/resource_manager.h",
        ],
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_socal",
    ],
)

cc_library(
    name = "starter_kit_proxy_socal_hdrs_lib",
    hdrs = [
        ":starter_kit_proxy_socal_hdrs"
    ],
    strip_include_prefix = "starter_kit_proxy_socal_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_proxy_modeldatatypes_hdrs_lib",
    hdrs = [
        ":starter_kit_proxy_modeldatatypes_hdrs"
    ],
    strip_include_prefix = "starter_kit_proxy_modeldatatypes_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_proxy_someipbinding_hdrs_lib",
    hdrs = [
        ":starter_kit_proxy_someipbinding_hdrs",
    ],
    strip_include_prefix = "starter_kit_proxy_someipbinding_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_proxy_someipprotocol_hdrs_lib",
    hdrs = [
        ":starter_kit_proxy_someipprotocol_hdrs"
    ],
    strip_include_prefix = "starter_kit_proxy_someipprotocol_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_proxy_socal_srcs_lib",
    srcs = [
        ":starter_kit_proxy_socal_srcs",
        ":starter_kit_proxy_someipprotocol_srcs",
        ":starter_kit_proxy_someipbinding_srcs",
    ],
    deps = [
        ":starter_kit_proxy_modeldatatypes_hdrs_lib",
        ":starter_kit_proxy_socal_hdrs_lib",
        ":starter_kit_proxy_someipbinding_hdrs_lib",
        ":starter_kit_proxy_someipprotocol_hdrs_lib",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-comcommon",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_headers",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-vajson",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_someipbinding_headers",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
)

cc_binary(
    name = "proxy_demo_idc6",
    deps = [
        ":starter_kit_proxy_modeldatatypes_hdrs_lib",
        ":starter_kit_proxy_socal_hdrs_lib",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-vajson",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-em-executionmanager",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-libvac",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-log-api",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_someipbinding",
    ],
    srcs = [
        "@starter_kit_adaptive_xavier//:proxy_demo_idc6_srcs",

        # This a workaround to resolve cyclic dependency. This is the reason why the target proxy_demo_idc6
        # build in 2 steps. 
        # The code generators depend on libSocal.a, contained in the @minerva_mpu_adaptive//:socal_lib_for_proxy below.
        # That is why we put it in sources. It is important that this `:socal_lib_for_proxy` is positioned earlier in
        # the list than the generated sources in `:starter_kit_proxy_socal_srcs_lib` and 
        # `:starter_kit_proxy_applicationbase_init_deinit_srcs` 
        "@minerva_mpu_adaptive//:socal_lib_for_proxy",

        ":starter_kit_proxy_socal_srcs_lib",
        ":starter_kit_proxy_applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
)

cc_library(
    name = "starter_kit_skeleton_socal_hdrs_lib",
    hdrs = [
        ":starter_kit_skeleton_socal_hdrs"
    ],
    strip_include_prefix = "starter_kit_skeleton_socal_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_skeleton_modeldatatypes_hdrs_lib",
    hdrs = [
        ":starter_kit_skeleton_modeldatatypes_hdrs"
    ],
    strip_include_prefix = "starter_kit_skeleton_modeldatatypes_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_skeleton_someipbinding_hdrs_lib",
    hdrs = [
        ":starter_kit_skeleton_someipbinding_hdrs",
    ],
    strip_include_prefix = "starter_kit_skeleton_someipbinding_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_skeleton_someipprotocol_hdrs_lib",
    hdrs = [
        ":starter_kit_skeleton_someipprotocol_hdrs"
    ],
    strip_include_prefix = "starter_kit_skeleton_someipprotocol_hdrs/output/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes",
)

cc_library(
    name = "starter_kit_skeleton_socal_srcs_lib",
    srcs = [
        ":starter_kit_skeleton_socal_srcs",
        ":starter_kit_skeleton_someipprotocol_srcs",
        ":starter_kit_skeleton_someipbinding_srcs",
    ],
    deps = [
        ":starter_kit_skeleton_modeldatatypes_hdrs_lib",
        ":starter_kit_skeleton_socal_hdrs_lib",
        ":starter_kit_skeleton_someipbinding_hdrs_lib",
        ":starter_kit_skeleton_someipprotocol_hdrs_lib",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-comcommon",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_headers",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-vajson",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_someipbinding_headers",
    ],
    copts = [
        "-std=c++14",
    ],
    linkstatic = 1,
)

cc_binary(
    name = "skeleton_demo_idc6",
    deps = [
        ":starter_kit_skeleton_modeldatatypes_hdrs_lib",
        ":starter_kit_skeleton_socal_hdrs_lib",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-vajson",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-em-executionmanager",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-libvac",
        "@starter_kit_adaptive_xavier//:amsr-vector-fs-log-api",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_skeleton",
        "@starter_kit_adaptive_xavier//:amsr_vector_fs_someipbinding",
    ],
    srcs = [
        "@starter_kit_adaptive_xavier//:skeleton_demo_idc6_srcs",

        # This a workaround to resolve cyclic dependency. This is the reason why the target skeleton_demo_idc6
        # build in 2 steps. 
        # The code generators depend on libSocal.a, contained in the @minerva_mpu_adaptive//:socal_lib_for_skeleton below.
        # That is why we put it in sources. It is important that this `:socal_lib_for_skeleton` is positioned earlier in
        # the list than the generated sources in `:starter_kit_skeleton_socal_srcs_lib` and 
        # `:starter_kit_skeleton_applicationbase_init_deinit_srcs`
        "@minerva_mpu_adaptive//:socal_lib_for_skeleton",

        ":starter_kit_skeleton_socal_srcs_lib",
        ":starter_kit_skeleton_applicationbase_init_deinit_srcs",
    ],
    copts = [
        "-std=c++14",
    ],
    linkopts = [
        "-lpthread",
    ],
    linkstatic = 1,
)
