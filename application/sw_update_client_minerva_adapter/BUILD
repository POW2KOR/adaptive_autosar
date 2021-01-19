load("@minerva_mpu_adaptive//bsw:defs.bzl", "minerva_aa_codegen_rule")

filegroup(
    name = "app_arxml",
    srcs = [
        "sw_update_client_minerva_adapter_app/arxml/sw_update_client_minerva_adapter_app.arxml",
        "sw_update_client_minerva_adapter_interface/arxml/swuc_if.arxml",
        "@starter_kit_adaptive_xavier//:mex_arxml",
        "@starter_kit_adaptive_xavier//:ncd_arxml",
        "@starter_kit_adaptive_xavier//:standard_types_arxml",
    ],
)

minerva_aa_codegen_rule(
    name = "sw_update_client_minerva_adapter_app_gen_rule",
    arxml_srcs = [":app_arxml"],
    outs_list_dict = {
        "sw_update_client_minerva_adapter_app_updatemanager_daemon_db": [
            "sw_update_client_minerva_adapter_app/etc/swcl_db.json",
            "sw_update_client_minerva_adapter_app/etc/updatemanager.json"
        ],
        "sw_update_client_minerva_adapter_app_updatemanager_swcluser_meta": [
            "sw_update_client_minerva_adapter_app/swcl_package_metadata.json"
        ],
        "sw_update_client_minerva_adapter_app_exec_config": [
            "sw_update_client_minerva_adapter_app/configuration/exec_config.json"
        ],
        "sw_update_client_minerva_adapter_app_applicationbase_init_deinit_srcs": [
            "sw_update_client_minerva_adapter_app/src/ara/core/initialization.cpp"
        ],
        "ignore": [
            # Ideally the NCD would not contain any applications, but it does so we get the following files generated
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/configuration/exec_config.json",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/etc/swcl_db.json",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/etc/updatemanager.json",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/src/ara/core/initialization.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_SwComponentType_Executable/swcl_package_metadata.json",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/configuration/exec_config.json",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/etc/swcl_db.json",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/etc/updatemanager.json",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/src/ara/core/initialization.cpp",
            "IDC_M_P_SoftwareClusterDesign_Base_TEST_SwComponentType_Executable/swcl_package_metadata.json"
        ]
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_swcluster_meta",
        "@starter_kit_adaptive_xavier//:generator_amsr_updatemanager_daemon",
        "@starter_kit_adaptive_xavier//:generator_amsr_em_exec_config",
        "@starter_kit_adaptive_xavier//:generator_amsr_applicationbase_init_deinit",
    ]
)