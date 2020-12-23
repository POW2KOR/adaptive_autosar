package(default_visibility = ["//visibility:public"])

filegroup(
    name = "machine_arxml",
    srcs = glob(["arxmls/machine.arxml"]),
)

##
## This will generate the model_gen folder that will contain all the arxml
## Then that model_gen will be used to generate the source code in src_gen
## src_gen will be available in the bazel-out directory
##
genrule(
    name = "src_gen_rule",
    srcs = [
        ":machine_arxml",
        "@starter_kit_adaptive_xavier//:amsrgen_sh",
        "@starter_kit_adaptive_xavier//:setup_jre_link_sh",
    ],
    outs = [
        "src_gen/example-machine/machine_exec_config.json",
    ],
    cmd = """
    mkdir -p $(RULEDIR)/src_gen
    mkdir -p $(RULEDIR)/arxml_folder
    cp $(locations :machine_arxml) $(RULEDIR)/arxml_folder

    $(location @starter_kit_adaptive_xavier//:amsrgen_sh) -v \
    -g external/starter_kit_adaptive_xavier/mb_base_layer_adaptive_xavier/amsr_xavier/Generators/amsr_em_machine_config \
    -x $(RULEDIR)/arxml_folder -o $(RULEDIR)/src_gen --saveProject > /dev/null
    """,
    tools = [
        "@starter_kit_adaptive_xavier//:generator_tools_amsr_em_machine_config",
    ],
)

genrule(
    name = "src_gen_amsr_modelleddatatypes_api",
    srcs = [
        "@starter_kit_adaptive_xavier//:application_arxml",
        "@starter_kit_adaptive_xavier//:amsrgen_sh",
        "@starter_kit_adaptive_xavier//:setup_jre_link_sh",
    ],
    outs = [
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y/impl_type_dummyservicerecorddatatype_4tuekbbgqsijk4yv29iawd34y.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/STD_UUCategory/impl_type_std_uucategory.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Object_ST3/impl_type_arr_lrr_object_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Segment_ST3/impl_type_arr_lrr_segment_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_ManeuverListState_ST3_42w45002bze5mo286svxxsdbx/impl_type_rec_maneuverliststate_st3_42w45002bze5mo286svxxsdbx.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Pr7_ST3/impl_type_rec_lrr_object_pr7_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_Add_Maneuver_ST3_euk2owpx15avykqntci714wbp/impl_type_rec_add_maneuver_st3_euk2owpx15avykqntci714wbp.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_200/impl_type_arr_08_uint_nosna_200.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_objects_nest_pr7_st3_71njeubj9ico1p8v4pmslfcno.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_trgrcrowddata_st3_71njeubj9ico1p8v4pmslfcno.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_1000/impl_type_arr_08_uint_nosna_1000.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_32/impl_type_arr_08_uint_nosna_32.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_128/impl_type_arr_08_uint_nosna_128.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_1454/impl_type_arr_08_uint_nosna_1454.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segment_Pr6_ST3/impl_type_rec_lrr_segment_pr6_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7/impl_type_rec_lrr_object_stat_pr6_st3_6hptq6rv1r5w7spodrls7hwl7.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_34/impl_type_arr_08_uint_nosna_34.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataTypeTwo/impl_type_dummyservicerecorddatatypetwo.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_RemPark_ManeuverListNames_ST3/impl_type_rec_rempark_maneuverlistnames_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg/impl_type_rec_lrr_sens_stat_pr6_st3_2k3hoaz4lmdyzji1cc23c8ymg.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr/impl_type_rec_lrr_lanepoly_pr6_st3_3pbdqiss5ghx5e8f9twrfswzr.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp/impl_type_rec_device_authorized_status_st3_euk2owpx15avykqntci714wbp.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_84/impl_type_arr_08_uint_nosna_84.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_30/impl_type_arr_08_uint_nosna_30.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_segments_nest_pr6_st3_71njeubj9ico1p8v4pmslfcno.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_RemPark_DeviceListNames_Rs_ST3/impl_type_rec_rempark_devicelistnames_rs_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataType_4tuekbbgqsijk4yv29iawd34y/impl_type_dummyservicerecorddatatype_4tuekbbgqsijk4yv29iawd34y.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/STD_UUCategory/impl_type_std_uucategory.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Object_ST3/impl_type_arr_lrr_object_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_LRR_Segment_ST3/impl_type_arr_lrr_segment_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Pr7_ST3/impl_type_rec_lrr_object_pr7_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_200/impl_type_arr_08_uint_nosna_200.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Objects_Nest_Pr7_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_objects_nest_pr7_st3_71njeubj9ico1p8v4pmslfcno.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_TrgrCrowdData_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_trgrcrowddata_st3_71njeubj9ico1p8v4pmslfcno.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_32/impl_type_arr_08_uint_nosna_32.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_128/impl_type_arr_08_uint_nosna_128.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_1454/impl_type_arr_08_uint_nosna_1454.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segment_Pr6_ST3/impl_type_rec_lrr_segment_pr6_st3.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Object_Stat_Pr6_ST3_6hptq6rv1r5w7spodrls7hwl7/impl_type_rec_lrr_object_stat_pr6_st3_6hptq6rv1r5w7spodrls7hwl7.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_34/impl_type_arr_08_uint_nosna_34.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/DummyServiceRecordDataTypeTwo/impl_type_dummyservicerecorddatatypetwo.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Sens_Stat_Pr6_ST3_2k3hoaz4lmdyzji1cc23c8ymg/impl_type_rec_lrr_sens_stat_pr6_st3_2k3hoaz4lmdyzji1cc23c8ymg.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_LanePoly_Pr6_ST3_3pbdqiss5ghx5e8f9twrfswzr/impl_type_rec_lrr_lanepoly_pr6_st3_3pbdqiss5ghx5e8f9twrfswzr.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_Device_Authorized_Status_ST3_euk2owpx15avykqntci714wbp/impl_type_rec_device_authorized_status_st3_euk2owpx15avykqntci714wbp.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_84/impl_type_arr_08_uint_nosna_84.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/ARR_08_UInt_noSNA_30/impl_type_arr_08_uint_nosna_30.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_LRR_Segments_Nest_Pr6_ST3_71njeubj9ico1p8v4pmslfcno/impl_type_rec_lrr_segments_nest_pr6_st3_71njeubj9ico1p8v4pmslfcno.h",
        "src_gen/IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/includes/daimler/cppDataTypes/common/REC_RemPark_DeviceListNames_Rs_ST3/impl_type_rec_rempark_devicelistnames_rs_st3.h",
    ],
    cmd = """
    mkdir -p $(RULEDIR)/src_gen
    mkdir -p $(RULEDIR)/arxml_folder
    cp $(locations @starter_kit_adaptive_xavier//:application_arxml) $(RULEDIR)/arxml_folder

    $(location @starter_kit_adaptive_xavier//:amsrgen_sh) -v \
    -g external/starter_kit_adaptive_xavier/mb_base_layer_adaptive_xavier/amsr_xavier/Generators/amsr_modelleddatatypes_api/ \
    -x $(RULEDIR)/arxml_folder -o $(RULEDIR)/src_gen --saveProject

    """,
    tools = [
        "@starter_kit_adaptive_xavier//:generator_tools_amsr_modelleddatatypes_api",
    ],
)
