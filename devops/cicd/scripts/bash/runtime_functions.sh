set -ex

compile_x86_64_linux_ubuntu()
{
    bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --//:mt --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --//:mt --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    # For now we need config stripped because the parition size is limited to
    # 512MB and our binaries have more than that.
    bazel build //deployment/minerva_mpu_adaptive:filesystem_update_package --config=stripped --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
}

compile_aarch64_linux_ubuntu()
{
    bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --//:mt --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --//:mt --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    # For now we need config stripped because the parition size is limited to
    # 512MB and our binaries have more than that.
    bazel build //deployment/minerva_mpu_adaptive:filesystem_update_package --config=stripped --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
}

compile_aarch64_linux_linaro()
{
    bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    bazel build //deployment/minerva_mpu_adaptive:filesystem_tar --//:mt --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
    bazel build //:minerva_mpu_adaptive_filesystem --//:mt --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

    # For now we need config stripped because the parition size is limited to
    # 512MB and our binaries have more than that.
    bazel build //deployment/minerva_mpu_adaptive:filesystem_update_package --config=stripped --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
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
