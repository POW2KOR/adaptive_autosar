"""
This file contains several utility functions and macros used within or with the
Adaptive AUTOSAR BSW Bazel files.
"""

load("@rules_foreign_cc//foreign_cc:cmake.bzl", "cmake")

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

def minerva_aa_codegen_rule(
        name,
        arxml_srcs,
        outs_list_dict,
        generators,
        ignore_matches = None):
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
        "@amsr_xavier//:generator_common_tools",
        "@amsr_xavier//:amsrgen_sh",
        "@amsr_xavier//:setup_jre_link_sh",
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

    # Ignoring GeneratorReport.html because it somehow doesn't always get
    # generated even though everything runs successfully.
    for generator_report_file in [
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
        tmp_folder=$$(mktemp -d)
        output_folder="$(RULEDIR)/{output_folder}"
        arxml_srcs_folder="$(RULEDIR)/{arxml_srcs_folder}"
        generator_log="$$output_folder/generator_log.txt"
        generator_messages_tempfile=`tempfile`

        rm -rf $$output_folder
        rm -rf $$arxml_srcs_folder
        mkdir -p $$tmp_folder
        mkdir -p $$output_folder
        mkdir -p $$arxml_srcs_folder
        cp --parents {arxml_srcs} $$arxml_srcs_folder

        # Propagate the failure past the pipe
        set -o pipefail

        # Don't stop immediately on error, so we can handle it gracefully
        set +e
        
        # In case of generator failure, we retry up to five times as a temporary workaround
        tries=0
        until [ "$$tries" -ge 5 ]
        do
            rm -rf $$output_folder/*
            rm -f $$generator_log
            $(location @amsr_xavier//:amsrgen_sh) -v {generators_arg} -x $$arxml_srcs_folder -o $$output_folder --saveProject 1>$$generator_log 2>&1 && break
            tries=$$((tries+1)) 
            sleep 15
        done

        # Process error messages from code generator
        if [ $$? -ne 0 ]; then
            # We cannot use xmllint to display the generator error messages
            # because the generator does not output a generator report xml file
            # in case of fatal errors.
            echo ""
            echo "The generator has failed executing. Please check the log for more details:"
            echo $$generator_log
            echo ""
            
            exit 1
        fi

        # If xmllint is installed, we print the generator's warning and
        # non-fatal error messages.
        if [ -x "$$(command -v xmllint)" ]; then
            # Unfortunately, we can't use XPath text() to print because of a bug in
            # xmllint which doesn't print new lines, so we're doing the newline add
            # in sed in the next step

            # Take the non-fatal error messages
            xmllint --xpath "//ValidationResult[@severity=\\"Error\\"]/Description" $$output_folder/GeneratorReport.xml 1>$$generator_messages_tempfile 2>/dev/null

            # Take the warning messages
            xmllint --xpath "//ValidationResult[@severity=\\"Warning\\"]/Description" $$output_folder/GeneratorReport.xml 1>>$$generator_messages_tempfile 2>/dev/null

            # This sed removes the <Description> xml tag and adds new lines.
            # This is due to the aforementioned xmllint bug.
            sed -i "s/<\\/Description>/\\\\n/g ; s/<Description>/- /g" $$generator_messages_tempfile

            if [[ $$(wc -l $$generator_messages_tempfile | awk '{{print $$1}}') > 0 ]]; then
                echo ""
                echo "The code generator emitted the following warnings and non-fatal errors:"
                cat $$generator_messages_tempfile
                echo ""
            fi
        else
            if grep -q -E 'severity="(Warning|Error)"' $$output_folder/GeneratorReport.xml; then
                echo ""
                echo "The generator has emitted some non-fatal errors or warnings. Please check the log for more details:"
                echo $$generator_log
                echo ""
            fi

        fi

        # End process error messages from code generator

        # Start process generated files

        # From now we can stop on error
        set -e

        echo $(OUTS) | tr " " "\\\\n" | sort > $$tmp_folder/outs.txt
        find $$output_folder -type f | sort > $$tmp_folder/generated.txt

        # Compare the list of files generated to the list of files in the outs
        # list.
        comm -23 $$tmp_folder/generated.txt $$tmp_folder/outs.txt > $$tmp_folder/comparison.txt

        # Ignore the generator_log.txt, GeneratorReport.html and 
        # GeneratorReport.xml files for the purpose of this error message.
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
        # End process generated files
        """.format(
            arxml_srcs_folder = "{}/arxml_srcs".format(gen_rule_name),
            output_folder = gen_rule_output_folder,
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

def minerva_aa_bsw_module(
        name,
        srcs_filegroup,
        cache_entries = None,
        out_binaries = None,
        out_static_libs = None,
        deps = None,
        out_headers_only = False,
        out_bin_dir = "bin",
        out_include_dirs = None):
    """
    A macro to handle Vector BSW CMake target definitions.

    It makes use of the deps fields to determine the cache_entries for the
    cmake_external $EXT_BUILD_DEPS, to remove the need for duplicate
    information and making the dependencies paths less error-prone.

    Args:
        name: A unique name for this bsw target.

        srcs_filegroup: Filegroup containing the source for this CMake BSW
            module.

        cache_entries: Optional dictionary containing CMake cache entry
            definitions to use for this module. The macro overrides some of
            these cache entry definitions by itself.

        out_binaries: Optional names of the resulting binaries.

        out_static_libs: Optional names of the resulting static libraries.

        deps: Optional dependencies to be copied into the directory structure.
            If the macro is a target of another BSW module, the cache_entries
            get extended to add corect `<package>_DIR` entries and everything
            should be handled.

        out_headers_only: Optional flag variable to indicate that the library
            produces only headers

        out_bin_dir: Optional name of the output subdirectory with the binary
            files, defaults to 'bin'.

        out_include_dirs: Optional list of out directory contaning header files

    """
    if not deps:
        deps = []

    if not out_static_libs:
        out_static_libs = []

    if not out_binaries:
        out_binaries = []

    if not cache_entries:
        cache_entries = {}

    if not out_include_dirs:
        out_include_dirs = []

    # CMAKE_TRY_COMPILE_TARGET_TYPE set to STATIC_LIBRARY is needed to make
    # aarch64 builds work, I do not know exactly why using this option affects
    # the linking of pthread, but it seems it does, so we're linking pthread
    # manually where it's needed. Furthermore, we make the approach uniform
    # across all the targets so that we don't have any mismatches that might be
    # harder to debug in the future.
    cache_entries["CMAKE_TRY_COMPILE_TARGET_TYPE"] = "STATIC_LIBRARY"

    for dep in deps:
        if dep == ":amsr_vector_fs_thread":
            cache_entries["vathread_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_thread/lib/cmake/vathread/"

        elif dep == ":amsr_vector_fs_msr4base":
            cache_entries["amsr-vector-fs-msr4base_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_msr4base/lib/cmake/amsr-vector-fs-msr4base/"

        elif dep == ":amsr_vector_fs_libiostream":
            cache_entries["amsr-vector-fs-libiostream_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_libiostream/lib/cmake/amsr-vector-fs-libiostream/"

        elif dep == ":amsr_vector_fs_libosabstraction":
            cache_entries["osabstraction_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_libosabstraction/lib/cmake/osabstraction/"

        elif dep == ":amsr_vector_fs_libvac":
            cache_entries["vac_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_libvac/lib/cmake/vac/"

        elif dep == ":amsr_vector_fs_vajson":
            cache_entries["vajson_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_vajson/lib/cmake/vajson/"

        elif dep == ":amsr_vector_fs_log_api":
            cache_entries["amsr-vector-fs-log-api-common_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-common/"
            cache_entries["amsr-vector-fs-log-api-ipc-common_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc-common/"
            cache_entries["amsr-vector-fs-log-api-ipc_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-vector-fs-log-api-ipc/"
            cache_entries["amsr-log_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/amsr-log/"
            cache_entries["ara-logging_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_log_api/lib/cmake/ara-logging/"

        elif dep == ":amsr_vector_fs_sec_libseccom":
            cache_entries["amsr-vector-fs-sec-libseccom_libcrypto_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libcrypto/"
            cache_entries["amsr-vector-fs-sec-libseccom_libtls_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_libseccom/lib/cmake/amsr-vector-fs-sec-libseccom_libtls/"

        elif dep == ":amsr_vector_fs_comcommon":
            cache_entries["ComCommon_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_comcommon/lib/cmake/ComCommon/"

        elif dep == ":amsr_vector_fs_sec_iam":
            cache_entries["amsr-vector-fs-sec-iam_libcommon_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libcommon/"
            cache_entries["amsr-vector-fs-sec-iam_libara_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libara/"
            cache_entries["amsr-vector-fs-sec-iam_libclient_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_iam/lib/cmake/amsr-vector-fs-sec-iam_libclient/"

        elif dep == ":amsr_vector_fs_em_executionmanager":
            cache_entries["amsr-vector-fs-em-executionmanagement_application-client_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_application-client/"
            cache_entries["amsr-vector-fs-em-executionmanagement_common-lib_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_common-lib/"
            cache_entries["amsr-vector-fs-em-executionmanagement_failure-handler-client_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_failure-handler-client/"
            cache_entries["amsr-vector-fs-em-executionmanagement_recovery-action-client_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_recovery-action-client/"
            cache_entries["amsr-vector-fs-em-executionmanagement_state-client_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_em_executionmanager/lib/cmake/amsr-vector-fs-em-executionmanagement_state-client/"

        elif dep == ":amsr_vector_fs_someipprotocol":
            cache_entries["SomeIpProtocol_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_someipprotocol/lib/cmake/SomeIpProtocol/"

        elif dep == ":amsr_vector_fs_someipdaemonclient":
            cache_entries["SomeIpDaemonClient_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_someipdaemonclient/lib/cmake/SomeIpDaemonClient/"

        elif dep == ":amsr_vector_fs_sec_cryptostack":
            cache_entries["amsr-vector-fs-sec-cryptostack_libclient_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libclient/"
            cache_entries["amsr-vector-fs-sec-cryptostack_libcommon_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libcommon/"
            cache_entries["amsr-vector-fs-sec-cryptostack_libara_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libara/"
            cache_entries["amsr-vector-fs-sec-cryptostack_libdriverfactory_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libdriverfactory/"
            cache_entries["amsr-vector-fs-sec-cryptostack_libsoftwareprovider_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libsoftwareprovider/"
            cache_entries["amsr-vector-fs-sec-cryptostack_libipc_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack/lib/cmake/amsr-vector-fs-sec-cryptostack_libipc/"

        elif dep == ":amsr_vector_fs_sec_cryptostack_driver_lib_es":
            cache_entries["amsr-vector-fs-sec-cryptostack-driver-lib_es_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_sec_cryptostack_driver_lib_es/lib/cmake/amsr-vector-fs-sec-cryptostack-driver-lib_es/"

        elif dep == ":amsr_vector_fs_applicationbase":
            cache_entries["application_base_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_applicationbase/lib/cmake/application_base/"

        elif dep == ":amsr_vector_fs_crc":
            cache_entries["amsr-vector-fs-crc_libinternal_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_crc/lib/cmake/amsr-vector-fs-crc_libinternal/"
            cache_entries["amsr-vector-fs-crc_libcrc_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_crc/lib/cmake/amsr-vector-fs-crc_libcrc/"

        elif dep == ":amsr_vector_fs_e2e":
            cache_entries["amsr-vector-fs-e2e_libe2e_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_e2e/lib/cmake/amsr-vector-fs-e2e_libe2e/"
            cache_entries["amsr-vector-fs-e2e_libinternal_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_e2e/lib/cmake/amsr-vector-fs-e2e_libinternal/"

        elif dep == ":amsr_vector_fs_logutility":
            cache_entries["log-utility_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_logutility/lib/cmake/log-utility/"

        elif dep == ":amsr_vector_fs_iointegritystream":
            cache_entries["iointegritystream_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_iointegritystream/lib/cmake/iointegritystream/"

        elif dep == ":amsr_vector_fs_socal_headers":
            cache_entries["Socal_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_socal_headers/lib/cmake/Socal/"

        elif dep == ":amsr_vector_fs_socal":
            cache_entries["Socal_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_socal/lib/cmake/Socal/"

        elif dep == ":amsr_vector_fs_someipbinding":
            cache_entries["SomeIpBinding_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_someipbinding/lib/cmake/SomeIpBinding/"
            cache_entries["SomeIpBindingInternal_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_someipbinding/lib/cmake/SomeIpBindingInternal/"
            cache_entries["SomeIpBindingTransformationLayer_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_someipbinding/lib/cmake/SomeIpBindingTransformationLayer/"

        elif dep == ":amsr_vector_fs_ipcbinding":
            cache_entries["IpcBinding_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_ipcbinding/lib/cmake/IpcBinding/"
            cache_entries["IpcBindingInternal_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_ipcbinding/lib/cmake/IpcBindingInternal"
            cache_entries["IpcBindingTransformationLayer_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_ipcbinding/lib/cmake/IpcBindingTransformationLayer"

        elif dep == ":amsr_vector_fs_per_libpersistency":
            cache_entries["persistency_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_per_libpersistency/lib/cmake/persistency/"
            cache_entries["persistency-key-value-storage_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_per_libpersistency/lib/cmake/persistency-key-value-storage/"
            cache_entries["persistency-common_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_per_libpersistency/lib/cmake/persistency-common/"
            cache_entries["persistency-file-storage_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_per_libpersistency/lib/cmake/persistency-file-storage/"
            cache_entries["persistency-fs_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_per_libpersistency/lib/cmake/persistency-fs/"

        elif dep == ":amsr_vector_fs_characterconversion":
            cache_entries["amsr-vector-fs-characterconversion_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_characterconversion/lib/cmake/amsr-vector-fs-characterconversion/"
            cache_entries["amsr-vector-fs-characterconversion_common_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_characterconversion/lib/cmake/amsr-vector-fs-characterconversion_common/"
            cache_entries["amsr-vector-fs-characterconversion_vector_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_characterconversion/lib/cmake/amsr-vector-fs-characterconversion_vector/"

        elif dep == ":amsr_vector_fs_udstransport":
            cache_entries["LibUdsTransportApi_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_udstransport/lib/cmake/LibUdsTransportApi/"

        elif dep == ":amsr_vector_fs_diagnosticutility":
            cache_entries["LibDiagUtility_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_diagnosticutility/lib/cmake/LibDiagUtility/"

        elif dep == ":amsr_vector_fs_pduhdrtpbinding":
            cache_entries["LibPduHdrTpBinding_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_pduhdrtpbinding/lib/cmake/LibPduHdrTpBinding/"

        elif dep == ":amsr_vector_fs_doipbinding":
            cache_entries["LibDoipBinding_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_doipbinding/lib/cmake/LibDoIpBinding/"

        elif dep == ":amsr_vector_fs_diagnosticrpc":
            cache_entries["LibDiagApiRpc_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_diagnosticrpc/lib/cmake/LibDiagApiRpc/"
            cache_entries["LibDiagComCommon_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_diagnosticrpc/lib/cmake/LibDiagComCommon/"
            cache_entries["LibDiagDaemonRpc_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_diagnosticrpc/lib/cmake/LibDiagDaemonRpc/"

        elif dep == ":amsr_vector_fs_diagnosticrpccombinding":
            cache_entries["LibDiagComApi_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_diagnosticrpccombinding/lib/cmake/LibDiagComApi/"
            cache_entries["LibDiagComDaemon_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_diagnosticrpccombinding/lib/cmake/LibDiagComDaemon/"
            cache_entries["LibDiagnosticRpcComBinding_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_diagnosticrpccombinding/lib/cmake/LibDiagnosticRpcComBinding/"

        elif dep == ":amsr_vector_fs_aradiag":
            cache_entries["LibAraDiag_DIR:PATH"] = \
                "$EXT_BUILD_DEPS/amsr_vector_fs_aradiag/lib/cmake/LibAraDiag/"

    cmake(
        name = name,
        cache_entries = extend_and_select(
            {
                "//:qnx": {
                    "CMAKE_SYSTEM_NAME": "QNX",
                },
                "//:linux": {
                    "CMAKE_SYSTEM_NAME": "Linux",
                },
            },
            cache_entries,
        ),
        generate_crosstool_file = True,
        lib_source = srcs_filegroup,
        out_headers_only = out_headers_only,
        out_static_libs = out_static_libs,
        visibility = ["//visibility:public"],
        deps = deps,
        env = select({
            "//:aarch64": {
                # This enables QNX building to work, and is harmless in non-QNX building
                "QNX_TARGET": "$$EXT_BUILD_ROOT$$/external/aarch64_qnx_compiler/qnx_target",
                "QNX_HOST": "$$EXT_BUILD_ROOT$$/external/aarch64_qnx_compiler/qnx_host",
            },
            "//:k8": {
                # This enables QNX building to work, and is harmless in non-QNX building
                "QNX_TARGET": "$$EXT_BUILD_ROOT$$/external/x86_64_qnx_compiler/qnx_target",
                "QNX_HOST": "$$EXT_BUILD_ROOT$$/external/x86_64_qnx_compiler/qnx_host",
            },
        }),
        out_binaries = out_binaries,
        out_bin_dir = out_bin_dir,
        out_include_dirs = out_include_dirs,
        make_commands = [
            "make -j",
            "make install",
        ],
    )
