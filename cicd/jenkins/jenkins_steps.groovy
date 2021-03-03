// -*- mode: groovy -*-
lib_depot_utilities = load('ci-depot/jenkins/utilities.groovy')

DOCKER_IMAGE_COMPILATION = "artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:20210216120747"

// stash libraries
STASH_LIB_X86_64_LINUX_UBUNTU = '' //TODO: Fill in artifacts
STASH_LIB_AARCH64_LINUX_UBUNTU = '' //TODO: Fill in artifacts
STASH_LIB_AARCH64_LINUX_LINARO = '' //TODO: Fill in artifacts

def initialize() {
    return ['Initialize': {
      node(env.NODE_UTILITY) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()
            // TODO: Try to get rid of the mess in here as much as possible
            rootDir = pwd()

            registryUrl = "https://artifact.${env.SWF_DOMAIN}"
            registryCredentials = 'adasdai-artifactory'
            userId = sh (script: 'id -u', returnStdout: true).trim()
            groupId = sh (script: 'id -g', returnStdout: true).trim()
            isMaster = (env.BRANCH_NAME == 'master')
            remoteUpload = "-e isMaster=${isMaster}"

            bazelrc  = "${env.WORKSPACE}/.bazelrc"
            DISK_CACHE = sh ( script: """sed -n 's/.*--disk_cache="\\(.*\\)"/\\1/p' ${bazelrc}""", returnStdout: true).trim()
            env.diskCache = "-v /home/efs_cache/mpu:${DISK_CACHE}"
        }
      }
    }]
}


def compile_x86_64_linux_ubuntu(lib_name) {
    return ['x86_64_linux_ubuntu': {
      node(env.NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()

            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image(DOCKER_IMAGE_COMPILATION).inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                    sshagent([env.sshJenkinsCredentials]) {
                        // TODO: Move into external shellscript
                        sh '''
                            # Workaround for circular dependency
                            bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

                            # Actual build
                            bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                        '''
                    }

                    //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                    //This will explode as soon as issues during the build arise as files will be left as root and undeletable
                    sh "chown -R ${userId}:${groupId} ."
                }
            }

            lib_depot_utilities.pack_lib(lib_name, STASH_LIB_X86_64_LINUX_UBUNTU)
        }
      }
    }]
}


def compile_aarch64_linux_ubuntu(lib_name) {
    return ['aarch64_linux_ubuntu': {
      node(env.NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()

            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image(DOCKER_IMAGE_COMPILATION).inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                    sshagent([env.sshJenkinsCredentials]) {
                        // TODO: Move into external shellscript
                        sh '''
                            # Workaround for circular dependency
                            bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

                            # Actual build
                            bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                        '''
                    }

                    //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                    //This will explode as soon as issues during the build arise as files will be left as root
                    sh "chown -R ${userId}:${groupId} ."
                }
            }

            lib_depot_utilities.pack_lib(lib_name, STASH_LIB_AARCH64_LINUX_UBUNTU)
        }
      }
    }]
}



def compile_aarch64_linux_linaro(lib_name) {
    return ['aarch64_linux_linaro': {
      node(env.NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()

            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image(DOCKER_IMAGE_COMPILATION).inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                    sshagent([env.sshJenkinsCredentials]) {
                        // TODO: Move into external shellscript
                        sh '''
                            # Workaround for circular dependency
                            bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

                            # Actual build
                            bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                        '''
                    }

                    //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                    //This will explode as soon as issues during the build arise as files will be left as root
                    sh "chown -R ${userId}:${groupId} ."
                }
            }

            lib_depot_utilities.pack_lib(lib_name, STASH_LIB_AARCH64_LINUX_LINARO)
        }
      }
    }]
}

return this