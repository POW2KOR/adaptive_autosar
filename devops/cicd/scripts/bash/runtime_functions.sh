set -ex

compile_x86_64_linux_ubuntu()
{
    
    # Actual build
    bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --//:mt --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
}

compile_aarch64_linux_ubuntu()
{
    # Actual build
    bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --//:mt --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
}

compile_aarch64_linux_linaro()
{
    
    # Actual build
    bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --//:mt --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
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
