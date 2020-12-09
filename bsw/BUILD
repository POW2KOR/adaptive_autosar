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
        "@vector_sip_aa//:amsrgen_sh",
        "@vector_sip_aa//:setup_jre_link_sh",
    ],
    outs = [
        "src_gen/example-machine/machine_exec_config.json",
    ],
    cmd = """
    mkdir -p $(RULEDIR)/src_gen
    mkdir $(RULEDIR)/arxml_folder    
    cp $(locations :machine_arxml) $(RULEDIR)/arxml_folder

    $(location @vector_sip_aa//:amsrgen_sh) -v \
    -g external/vector_sip_aa/Generators/amsr_em_machine_config \
    -x $(RULEDIR)/arxml_folder -o $(RULEDIR)/src_gen --saveProject > /dev/null
    """,
    tools = [
        "@vector_sip_aa//:generator_tools",
    ],
)
