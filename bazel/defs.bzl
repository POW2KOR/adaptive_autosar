"""
This file contains several utility functions and macros used within or with the
Adaptive AUTOSAR BSW Bazel files.
"""

def extend_and_select(select_dict, extension):
    """
    Take a select dict, extend each option with another value and then select

    This function takes in a dictionary in the format required for the select
    Bazel function. It then extends each of the options of the dictionary with
    a given extension value. Finally, it does a select and returns it as the
    final output.

    Args:
        select_dict: The dictionary in format.

        extension: The value to use to extend each of the select options.
    """
    for _, value in select_dict.items():
        value.update(extension)

    return select(select_dict)

def minerva_aa_codegen_declare(name, path_to_generators, generators):
    """
    A wrapper around native filegroup for Adaptive AUTOSAR code generators.

    This macro is a wrapper around the native filegroup rule with the
    appropriate configuration so that it can be used in genrule tools field
    later on.

    This macro creates filegroup targets with the following name
    format: <name>_<generator>. Therefore, with a name value of "generator"
    and a generator value of "amsr_em_machine_config", the final name of the
    target would be "generator_amsr_em_machine_config".

    Args:
        name: This name is used as a prefix for the tool targets.

        path_to_generators: Filesystem path to the generators folder.

        generators: List of generators to build tool targets for.
    """
    for generator in generators:
        # Unfortunately since rule macros only run the analysis phase, we can't
        # do extra filesystem checks to see if the requested generators exist
        # on the filesystem or other nice things like this.
        native.filegroup(
            name = "{}_{}".format(name, generator),
            srcs = [
                "{}/{}".format(path_to_generators, generator),
            ],
            visibility = ["//visibility:public"],
        )

def minerva_aa_codegen_rule(name, arxml_srcs, outs_list_dict, generators, ignore_matches = None):
    """
    A wrapper around genrule for Adaptive AUTOSAR code generation.

    This macro is a wrapper around the native genrule with the appropriate
    configuration and script to generate code using the Vector Adaptive AUTOSAR
    code generators. It is designed to split the generated code into multiple
    sub-targets (configured by the outs_list_dict parameter) each containing
    its own files in a dedicated subfolders. This helps, for example, if you
    want to have a folder of headers which doesn't contain other files. An
    error is thrown if the generator generates files which are not found in the
    outs list.

    For the rest of this document, <name> should be understood as the value
    given to the name parameter of this macro.

    Apart from the targets specified in outs_list_dict, there is a special
    target defined by this macro. It is called just <name> and it is a
    catch-all which contains all the files in the outs_list_dict, as well as the
    generator reports and generator logs.

    Note that the <name>_* subtargets are only run on-demand (or when depended
    upon). But the <name> target is always an implicit dependency of all of
    these subtargets. Therefore, the sub-targets have to be explicitly
    asked-for to generate anything meaningful.

    Args:
        name: A unique name for this target.

            You may refer to this rule by name in the srcs or deps section of
            other BUILD rules. If the rule generates source files, you should
            use the srcs attribute.

        arxml_srcs:  A list of inputs for code generation. Expected to be ARXML
            source files.

        outs_list_dict: A dict of lists of files generated by this rule. Each
            key in the first level dictionary will become a target and the
            files it will offer will be the ones listed in the corresponding
            list. The lists cannot have overlapping items. Output files must
            not cross package boundaries. Output filenames are interpreted as
            relative to the package.

        generators: A list of code generator dependencies for this rule.

        ignore_matches: A list of regex filters for files generated by the
        code generators that should be ignored. Please use this feature
        sparingly, and don't put `.*` in the list of ignores, as this negates
        the benefits of the out_list_dict mismatch detection.
    """

    # Python has a quirk with mutable defaults. I don't know if this happens in
    # starlark as well, but I will change it like this defensively to avoid any
    # potential issues which may be harder to debug in the future.
    if ignore_matches == None:
        ignore_matches = []

    gen_rule_name = name
    gen_rule_output_folder = "{}/output".format(gen_rule_name)

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

    concatenated_outs = []

    for outs_list_name, outs_list in outs_list_dict.items():
        for out in outs_list:
            full_out_path = "{output_folder}/{file_name}".format(
                output_folder = gen_rule_output_folder,
                file_name = out,
            )

            if full_out_path in concatenated_outs:
                fail("The outs_lists in outs_list_dict cannot have overlapping items")

            concatenated_outs.append(full_out_path)

    for generator_report_file in [
        "GeneratorReport.html",
        "GeneratorReport.xml",
        "generator_log.txt",
    ]:
        full_out_path = "{output_folder}/{file_name}".format(
            output_folder = gen_rule_output_folder,
            file_name = generator_report_file,
        )

        concatenated_outs.append(full_out_path)

    native.genrule(
        name = gen_rule_name,
        srcs = arxml_srcs,
        outs = concatenated_outs,
        cmd = """
        tmp_folder="/tmp/{tmp_folder}"
        output_folder="$(RULEDIR)/{output_folder}"
        arxml_srcs_folder="$(RULEDIR)/{arxml_srcs_folder}"
        generator_log="$$output_folder/generator_log.txt"

        rm -rf $$output_folder
        rm -rf $$arxml_srcs_folder
        mkdir -p $$tmp_folder
        mkdir -p $$output_folder
        mkdir -p $$arxml_srcs_folder
        cp {arxml_srcs} $$arxml_srcs_folder

        # Propagate the failure past the pipe
        set -o pipefail

        # Don't stop immediately on error, so we can handle it gracefully
        set +e
        $(location @starter_kit_adaptive_xavier//:amsrgen_sh) -v {generators_arg} -x $$arxml_srcs_folder -o $$output_folder --saveProject 1>$$generator_log 2>&1 

        if [ $$? -ne 0 ]; then
            echo ""
            echo "The generator has failed executing. Please check the log for more details:"
            echo $$generator_log
            echo ""
            
            exit 1
        fi

        # From now you can stop on error
        set -e

        echo $(OUTS) | tr " " "\\\\n" | sort > $$tmp_folder/outs.txt
        find $$output_folder -type f | sort > $$tmp_folder/generated.txt

        # Compare the list of files generated to the list of files in the outs
        # list.
        comm -23 $$tmp_folder/generated.txt $$tmp_folder/outs.txt > $$tmp_folder/comparison.txt

        # Ignore the GeneratorReport.html and GeneratorReport.xml files for the
        # purpose of this error message.
        # 
        # Also ignore any other files which match ignore_matches

        for IGNORE_MATCH in generator_log.txt 'GeneratorReport.(html|xml)' {ignore_matches}
        do
            sed -ri "/$$IGNORE_MATCH/d" $$tmp_folder/comparison.txt
        done
       
        if [[ $$(wc -l $$tmp_folder/comparison.txt | awk '{{print $$1}}') > 0 ]]; then
            echo ""
            echo "Error: some generated files weren't found in the outs_list_dict list and weren't matched by any ignore_matches:"

            # Escaping path so it can be used in sed
            escaped_ruledir=`echo $$output_folder | sed 's/\\//\\\\\\\\\\//g'`

            # We are replacing $(RULEDIR) before printing on the screen to make
            # it easier for developers to copy paste into the Bazel file after.
            cat $$tmp_folder/comparison.txt | sed "s/$$escaped_ruledir\\///g"
            echo ""

            exit 1
        fi
        """.format(
            arxml_srcs_folder = "{}/arxml_srcs".format(gen_rule_name),
            output_folder = gen_rule_output_folder,
            tmp_folder = gen_rule_name,
            generators_arg = " ".join(generators_arg_list),
            arxml_srcs = " ".join(arxml_srcs_arg_list),
            ignore_matches = " ".join(ignore_matches),
        ),
        tools = tools_list,
    )

    for outs_list_name, outs_list in outs_list_dict.items():
        out_rule_name = outs_list_name
        out_rule_outs_folder = "{}/output".format(out_rule_name)
        out_rule_srcs_label = ":{}".format(gen_rule_name)

        full_path_outs_list = []

        for out in outs_list:
            full_path_outs_list.append(
                "{output_folder}/{file_name}".format(
                    output_folder = out_rule_outs_folder,
                    file_name = out,
                ),
            )

        native.genrule(
            name = out_rule_name,
            srcs = [out_rule_srcs_label],
            cmd = """
                rm -rf $(RULEDIR)/{output_folder}
                mkdir -p $(RULEDIR)/{output_folder}

                for file in $(locations {out_rule_srcs_label}); do\
                    final_path=`dirname $(RULEDIR)/{output_folder}/$${{file#$(RULEDIR)/{srcs_folder}/}}`; \
                    mkdir -p $$final_path; \
                    cp $$file $$final_path; \
                done
            """.format(
                srcs_folder = gen_rule_output_folder,
                output_folder = out_rule_outs_folder,
                out_rule_srcs_label = out_rule_srcs_label,
            ),
            outs = full_path_outs_list,
        )
