
load("@minerva_mpu_adaptive//bsw:defs.bzl", "minerva_aa_codegen_rule")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "machine_arxml",
    srcs = ["arxml/machine.arxml"],
)

minerva_aa_codegen_rule(
    name = "minerva_machine_exec_config_gen_rule",
    arxml_srcs = [":machine_arxml"],
    outs_list_dict = {
        "minerva_machine_exec_config": ["example-machine/machine_exec_config.json"],
    },
    generators = [
        "@starter_kit_adaptive_xavier//:generator_amsr_em_machine_config"
    ]
)
