// -*- mode: groovy -*-
import groovy.json.JsonOutput

lib_depot_utilities = load('devops/ci-depot/jenkins/utilities.groovy')
imgName = 'artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu'

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

            commitId = sh(returnStdout: true, script: 'git rev-parse HEAD').trim()
            imgNameVer = imgName + ":${commitId}"
            currentBuild.description = imgNameVer

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

def collect_deps() {
    sh 'python3 devops/docker/scripts/collect_deps.py -a'
    def JsonOutput = groovy.json.JsonOutput
    def downloadSpec = readJSON file: "${env.WORKSPACE}/devops/docker/configuration/tools.json"
    def server = Artifactory.server 'default-artifactory-server-id'

    server.credentialsId = registryCredentials
    server.download spec: JsonOutput.toJson(downloadSpec)

    sh 'ls -la tools/bazel'
}

def sw_package_create() {
    sh "python3 /usr/packageList/package_in_html.py -o ${commitId} -d ${imgNameVer}"
    def uploadSpec = """
        {
            "files": [
                {
                    "pattern": "${commitId}.html",
                    "target": "adasdai/minerva/minerva_mpu_docker/",
                    "recursive": "false"
                }
            ]
        }"""
    def server = Artifactory.server 'default-artifactory-server-id'
    server.credentialsId = registryCredentials
    echo 'Uploading binaries to the artifactory'
    server.upload(uploadSpec)
}

def compile_x86_64_linux_ubuntu(lib_name) {
    return ['x86_64_linux_ubuntu': {
      node(env.NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()
            collect_deps()
            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                withEnv(['DOCKER_BUILDKIT=1']) {
                    def builderImg = docker.build(imgNameVer, '-f ./devops/docker/Dockerfile.build_env  --build-arg BUILDKIT_INLINE_CACHE=1 .')
                    builderImg.inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                        sshagent([env.sshJenkinsCredentials]) {
                            sh 'devops/cicd/scripts/bash/runtime_functions.sh compile_x86_64_linux_ubuntu bin_x86_64_linux_ubuntu'
                            upload_artifacts('x86_64_linux_ubuntu')
                        }
                        //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                        //This will explode as soon as issues during the build arise as files will be left as root and undeletable
                        sh "chown -R ${userId}:${groupId} ."
                    }
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
            collect_deps()
            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                withEnv(['DOCKER_BUILDKIT=1']) {
                    def builderImg = docker.build(imgNameVer, '-f ./devops/docker/Dockerfile.build_env  --build-arg BUILDKIT_INLINE_CACHE=1 .')
                    builderImg.inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                        sshagent([env.sshJenkinsCredentials]) {
                            sh 'devops/cicd/scripts/bash/runtime_functions.sh compile_aarch64_linux_ubuntu bin_aarch64_linux_ubuntu'
                            upload_artifacts('aarch64_linux_ubuntu')
                        }
                        //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                        //This will explode as soon as issues during the build arise as files will be left as root
                        sh "chown -R ${userId}:${groupId} ."
                    }
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
            collect_deps()
            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                withEnv(['DOCKER_BUILDKIT=1']) {
                    def builderImg = docker.build(imgNameVer, '-f ./devops/docker/Dockerfile.build_env  --build-arg BUILDKIT_INLINE_CACHE=1 .')
                    builderImg.inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                        sshagent([env.sshJenkinsCredentials]) {
                            sh 'devops/cicd/scripts/bash/runtime_functions.sh compile_aarch64_linux_linaro bin_aarch64_linux_linaro'
                            upload_artifacts('aarch64_linux_linaro')
                        }
                        //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                        //This will explode as soon as issues during the build arise as files will be left as root
                        sh "chown -R ${userId}:${groupId} ."
                    }
                }
            }
            lib_depot_utilities.pack_lib(lib_name, STASH_LIB_AARCH64_LINUX_LINARO)
        }
      }
    }]
}
return this

def test_x86_64_linux_ubuntu(lib_name) {
    return ['x86_64_linux_ubuntu': {
      node(env.NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()
            collect_deps()
            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                withEnv(['DOCKER_BUILDKIT=1']) {
                    def builderImg = docker.build(imgNameVer, '-f ./devops/docker/Dockerfile.build_env  --build-arg BUILDKIT_INLINE_CACHE=1 .')
                    builderImg.inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                        sshagent([env.sshJenkinsCredentials]) {
                            sh """
                            . devops/cicd/scripts/bash/helper_functions.sh
                            test_x86_64_linux_ubuntu
                            """
                        }
                        //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                        //This will explode as soon as issues during the build arise as files will be left as root and undeletable
                        sh "chown -R ${userId}:${groupId} ."
                    }
                }
            }
            lib_depot_utilities.pack_lib(lib_name, STASH_LIB_X86_64_LINUX_UBUNTU)
        }
      }
    }]
}

def deploy_docker() {
    return ['DOCKER_MPU': {
    if (env.BRANCH_NAME == 'master') {
      node(env.NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()
            collect_deps()
            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                withEnv(['DOCKER_BUILDKIT=1']) {
                    def builderImg = docker.build(imgNameVer, '-f ./devops/docker/Dockerfile.build_env  --build-arg BUILDKIT_INLINE_CACHE=1 .')
                    echo 'Publishing the docker image to artifactory'
                    sh"docker push ${imgNameVer}"
                    sh"docker tag ${imgNameVer} ${imgName}:latest"
                    sh"docker push ${imgName}:latest"
                    builderImg.inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                        echo 'Publishing the installed software report to artifactory'
                        sw_package_create()
                        }
                    }
                }
            }
        }
    }
    else{
          println 'Publishing the docker image to Artifactory is skipped. (Only commit build)'
      }
    }]
}
return this

def upload_artifacts(String target_path) {
    sh "tar czf ${target_path}.tar.gz bin_${target_path}/*"
    if (env.BRANCH_NAME == 'release') {
        def uploadSpec = """
          {
          "files": [
                {
                    "pattern": "*.tar.gz",
                    "target": "adasdai/releases/minerva_mpu/${SW_VERSION}/",
                    "recursive": "false"
                }
            ]
          }"""
          def server = Artifactory.server 'default-artifactory-server-id'
          server.credentialsId = registryCredentials
          echo 'Uploading SW to the artifactory'
          server.upload(uploadSpec)
        }
    else{
          println 'Publishing the Artifacts to Artifactory is skipped.'
          archiveArtifacts artifacts: "*.tar.gz", onlyIfSuccessful: true
      }
}
