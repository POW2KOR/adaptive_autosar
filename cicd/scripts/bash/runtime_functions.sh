set -ex

compile_x86_64_linux_ubuntu() 
{
    # Workaround for circular dependency
    bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    # Actual build
    bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
}

compile_aarch64_linux_ubuntu()
{
    # Workaround for circular dependency
    bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    # Actual build
    bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}                   
}

compile_aarch64_linux_linaro() 
{
    # Workaround for circular dependency
    bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    # Actual build
    bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
}


##############################################################
# MAIN
#
# Run function passed as argument
set +x
if [ $# -gt 0 ]
then
    $@
else
    cat<<EOF
$0: Execute a function by passing it as an argument to the script:
Possible commands:
EOF
    declare -F | cut -d' ' -f3
    echo
fi