package(default_visibility = ["//visibility:public"])

filegroup(
    name = "machine_arxml",
    srcs = ["arxmls/machine.arxml"],
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
    mkdir $(RULEDIR)/arxml_folder    
    cp $(locations :machine_arxml) $(RULEDIR)/arxml_folder

    $(location @starter_kit_adaptive_xavier//:amsrgen_sh) -v \
    -g external/starter_kit_adaptive_xavier/mb_base_layer_adaptive_xavier/amsr_xavier/Generators/amsr_em_machine_config \
    -x $(RULEDIR)/arxml_folder -o $(RULEDIR)/src_gen --saveProject > /dev/null
    """,
    tools = [
        "@starter_kit_adaptive_xavier//:generator_tools",
    ],
)
