load("@minerva_mpu_adaptive//:bazel/defs.bzl", "minerva_aa_codegen_rule")

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
    name = "minerva_machine_exec_config_gen_rule",
    arxml_srcs = ["//application:complete_arxml"],
    generators = [
        "@amsr_xavier//:generator_amsr_em_machine_config",
    ],
    outs_list_dict = {
        "minerva_machine_exec_config": ["IDC6_M_P1_XAVIER/machine_exec_config.json"],
    },
)
