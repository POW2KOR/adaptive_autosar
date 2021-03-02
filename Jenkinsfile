import groovy.io.FileType
@Library('adas-jenkins-shared-lib@master') _

initGatekeeper()

node('pulse_ec2') {
    String registryUrl = "https://artifact.${env.SWF_DOMAIN}"
    String registryCredentials = 'adasdai-artifactory'
    String userId = sh (script: 'id -u', returnStdout: true).trim()
    String groupId = sh (script: 'id -g', returnStdout: true).trim()
    def imgNameVer = "artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:9dbca8c0ac21aba4e85855923d761439c2df67d3"
    boolean isMaster = (env.BRANCH_NAME == 'master')
    String remoteUpload = "-e isMaster=${isMaster}"
    
    try{
        stage('Checkout') {
            checkout scm
        }

        def rootDir = pwd()
        def codeFormatting = load "${rootDir}/ci-depot/jenkins/codeFormattingStage.groovy"
        codeFormatting.runFormatting(rootDir)


        stage('Prepare') {
            String bazelrc  = "${env.WORKSPACE}/.bazelrc"
            DISK_CACHE = sh ( script: """sed -n 's/.*--disk_cache="\\(.*\\)"/\\1/p' ${bazelrc}""", returnStdout: true).trim()
            env.diskCache = "-v /home/efs_cache/mpu:${DISK_CACHE}"
        }
        stage('Static code analysis') {
            // @Todo:space to add the code analyzer
        }
        stage('x86_64_linux_ubuntu') {
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                    stage('Build'){
                        sshagent([env.sshJenkinsCredentials]) {
                            sh '''
                                # Workaround for circular dependency
                                bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                                bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                                bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

                                # Actual build
                                bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            '''
                        }
                    }
                    stage('Test'){
                        // bazel command to run tests execution for x86_64_linux_ubuntu
                    }
                    sh "chown -R ${userId}:${groupId} ."
                }
            }
        }
        stage('aarch64_linux_ubuntu'){
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                    stage('Build'){
                        sshagent([env.sshJenkinsCredentials]) {
                            sh '''
                                # Workaround for circular dependency
                                bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                                bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                                bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

                                # Actual build
                                bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            '''
                        }
                    }
                    stage('Test'){
                        // bazel command to run tests execution for aarch64_linux_ubuntu
                    }
                    sh "chown -R ${userId}:${groupId} ."
                } // docker
            }
        }
        stage('aarch64_linux_linaro'){
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
                    stage('Build'){
                        sshagent([env.sshJenkinsCredentials]) {
                            sh '''
                                # Workaround for circular dependency
                                bazel build //bsw:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                                bazel build //bsw:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                                bazel build //bsw:amsr_vector_fs_socal_for_software_update --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}

                                # Actual build
                                bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_linaro --config=use_efs_build_cache --remote_upload_local_results=${isMaster}
                            '''
                        }
                    }
                    stage('Test'){
                        // bazel command to run tests execution for aarch64_linux_linaro
                    }
                    sh "chown -R ${userId}:${groupId} ."
                } // docker
            }
        }
        stage('deploy') {
            // Add the code to push docker image to artifactoy.
        }
    }
    catch (e) {
        currentBuild.result = 'FAILURE'
        throw e
    }
    finally {
        stage('Cleanup') {
            step([$class: 'WsCleanup'])
        }
    }
 }
