filegroup(
    name = "sda_model",
    srcs = [
        "self_diag_agent/model/SelfDiagnosticAgent.arxml",
        "self_diag_agent/model/SWUC_Types.arxml",
        "self_diag_agent/model/SWUC_SDA_Interface_Design.arxml",
        "self_diag_agent/model/SWUC_SDA_Interface_Deployment.arxml",
        "self_diag_agent/model/SWUC_SDA_Ipc_Required.arxml",
        "self_diag_agent/model/starter_kit_adaptive_xavier.arxml",
        #"self_diag_agent/model/IDC_GEN6_P_000102_20210602.arxml",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "self_diag_agent_srcs",
    srcs = glob(["self_diag_agent/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "logging_config",
    srcs = ["self_diag_agent/etc/logging_config.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "com_application",
    srcs = ["self_diag_agent/etc/com_application.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "exec_config",
    srcs = ["self_diag_agent/etc/exec_config.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "per_file_storage_config",
    srcs = ["self_diag_agent/etc/per_file_storage_config.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "per_key_value_storage_config",
    srcs = ["self_diag_agent/etc/per_key_value_storage_config.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "swcl_db",
    srcs = ["self_diag_agent/etc/swcl_db.json"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "updatemanager",
    srcs = ["self_diag_agent/etc/updatemanager.json"],
    visibility = ["//visibility:public"],
)
