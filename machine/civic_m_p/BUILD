load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "complete_arxml",
    srcs = [
        "//arxmls:civic_export_with_roller_bliner_rear_arxml",
        "@amsr_xavier//:mex_arxml",
    ],
)

filegroup(
    name = "em_logging_config",
    srcs = [
        "etc/logging_config.json",
    ],
)

minerva_aa_codegen_rule(
    name = "i3_machine_exec_config_gen_rule",
    arxml_srcs = [":complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_machine_config",
    ],
    outs_list_dict = {
        "i3_machine_exec_config": ["CIVIC_M_P_STAR_35/machine_exec_config.json"],
    },
)
