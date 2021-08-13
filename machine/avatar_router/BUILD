load("@apricot_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "em_logging_config",
    srcs = [
        "etc/logging_config.json",
    ],
)

filegroup(
    name = "machine_exec_config",
    srcs = [
        "etc/machine_exec_config.json",
    ],
)

minerva_aa_codegen_rule(
    name = "adaptive_machine_exec_config_gen_rule",
    arxml_srcs = ["//arxmls:Gen20x_Civic_i3_ECU_Extract"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_machine_config",
    ],
    outs_list_dict = {
        "adaptive_machine_exec_config": ["avatar_router/machine_exec_config.json"],
    },
)
