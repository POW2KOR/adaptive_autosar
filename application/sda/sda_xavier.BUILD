filegroup(
    name = "sda_model",
    srcs = [
        "self_diag_agent/model/IDC_GEN6_P._20210609.arxml",
        "self_diag_agent/model/SWUC_SDA_Interface_Deployment.arxml",
        "self_diag_agent/model/SWUC_SDA_Interface_Design.arxml",
        "self_diag_agent/model/SWUC_Types.arxml",
        "self_diag_agent/model/SelfDiagnosticAgent.arxml",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "self_diag_agent_srcs",
    srcs = glob(["self_diag_agent/src/**/*.cpp"]),
    visibility = ["//visibility:public"],
)

# The below header libraries are needed becasue the SDA repo has headers in
# nested subdirectories inside the source directory. Also, the inclusion of
# headers is like "did_f1a1_hpc_info_service.h" instead of
# "id_data/swuc_interface/did_f1a1_hpc_info_service.h"

cc_library(
    name = "sda_hdrs_lib",
    hdrs = glob(["self_diag_agent/src/**/*.h"]),
    strip_include_prefix = "self_diag_agent/src",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs1",
    hdrs = glob(["self_diag_agent/src/*.h"]),
    strip_include_prefix = "self_diag_agent/src",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs2",
    hdrs = glob(["self_diag_agent/src/dem_port_interfaces/*.h"]),
    strip_include_prefix = "self_diag_agent/src/dem_port_interfaces",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs3",
    hdrs = glob(["self_diag_agent/src/env_data/*.h"]),
    strip_include_prefix = "self_diag_agent/src/env_data",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs4",
    hdrs = glob(["self_diag_agent/src/generic_uds_services/*.h"]),
    strip_include_prefix = "self_diag_agent/src/generic_uds_services",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs5",
    hdrs = glob(["self_diag_agent/src/id_data/*.h"]),
    strip_include_prefix = "self_diag_agent/src/id_data",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs6",
    hdrs = glob(["self_diag_agent/src/id_data/swuc_interface/*.h"]),
    strip_include_prefix = "self_diag_agent/src/id_data/swuc_interface",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs7",
    hdrs = glob(["self_diag_agent/src/id_data/system_info/*.h"]),
    strip_include_prefix = "self_diag_agent/src/id_data/system_info",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs8",
    hdrs = glob(["self_diag_agent/src/persistency/*.h"]),
    strip_include_prefix = "self_diag_agent/src/persistency",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs9",
    hdrs = glob(["self_diag_agent/src/routines/*.h"]),
    strip_include_prefix = "self_diag_agent/src/routines",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs10",
    hdrs = glob(["self_diag_agent/src/security_access/*.h"]),
    strip_include_prefix = "self_diag_agent/src/security_access",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs11",
    hdrs = glob(["self_diag_agent/src/signals/*.h"]),
    strip_include_prefix = "self_diag_agent/src/signals",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "self_diagnostic_agent_hdrs12",
    hdrs = glob(["self_diag_agent/src/standard_services/*.h"]),
    strip_include_prefix = "self_diag_agent/src/standard_services",
    visibility = ["//visibility:public"],
)
