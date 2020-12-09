# This custom function takes in the CMAKE_TOOLCHAIN_FILE path dictionary
# for various targets and adds the cache_entries to each key's value
# and returns bazel select type object. This slect type output is
# assigned to cache_entries of cmake_external bazel rule

def selecty_genrule(select_cmd, cmake_deps):
    for _, value in select_cmd.items():
        value.update(cmake_deps)

    return select(select_cmd)
