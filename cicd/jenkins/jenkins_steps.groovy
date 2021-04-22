// -*- mode: groovy -*-
lib_depot_utilities = load('ci-depot/jenkins/utilities.groovy')

DOCKER_IMAGE_COMPILATION = "artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:bdcc935587335d4ccff41d0945384396e0014ab7"

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
                        sh 'cicd/scripts/bash/runtime_functions.sh compile_x86_64_linux_ubuntu'
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
                        sh 'cicd/scripts/bash/runtime_functions.sh compile_aarch64_linux_ubuntu'
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
                        sh 'cicd/scripts/bash/runtime_functions.sh compile_aarch64_linux_linaro'
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
