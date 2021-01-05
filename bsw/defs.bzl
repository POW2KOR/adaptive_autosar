# This custom function takes in the CMAKE_TOOLCHAIN_FILE path dictionary
# for various targets and adds the cache_entries to each key's value
# and returns bazel select type object. This slect type output is
# assigned to cache_entries of cmake_external bazel rule

def selecty_genrule(select_cmd, cmake_deps):
    for _, value in select_cmd.items():
        value.update(cmake_deps)

    return select(select_cmd)


def minerva_aa_codegen_rule(name, arxml_srcs, outs, generators):
    """
    This macro is a wrapper around the native genrule with the appropriate
    configuration and script to generate code using the Vector Adaptive AUTOSAR
    code generators.
    """

    tools_list = [
        "@starter_kit_adaptive_xavier//:generator_common_tools",
        "@starter_kit_adaptive_xavier//:amsrgen_sh",
        "@starter_kit_adaptive_xavier//:setup_jre_link_sh",
    ]

    generators_arg_list = []

    for generator in generators:
        tools_list.append(generator)
        generators_arg_list.append("-g $(locations {})".format(generator))

    arxml_srcs_arg_list = []

    for arxml_src in arxml_srcs:
        arxml_srcs_arg_list.append("$(locations {})".format(arxml_src))

    native.genrule(
        name = name,
        srcs = arxml_srcs,
        outs = outs,
        cmd = """
        mkdir -p $(RULEDIR)/src_gen
        mkdir -p $(RULEDIR)/arxml_folder
        cp {arxml_srcs} $(RULEDIR)/arxml_folder

        $(location @starter_kit_adaptive_xavier//:amsrgen_sh) -v \
        {generators_arg} \
        -x $(RULEDIR)/arxml_folder -o $(RULEDIR)/src_gen --saveProject > /dev/null
        """.format(
            generators_arg = " ".join(generators_arg_list),
            arxml_srcs = " ".join(arxml_srcs_arg_list)
        ),
        tools = tools_list
    )