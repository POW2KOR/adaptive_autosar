package(default_visibility = ["//visibility:public"])

filegroup(
    name = "idc_ecu_extract_arxml",
    srcs = ["arxml/TestExport_Base_and_SDA_and_TestBase_wS2S_V6.arxml"],
)

filegroup(
    name = "complete_arxml",
    srcs = [
        ":idc_ecu_extract_arxml",
        "//arxmls::x6aa_idc_ecu_extract_arxml",
        "@amsr_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:ncd_arxml",
        "@starter_kit_adaptive_xavier//:standard_types_arxml",
    ],
)
