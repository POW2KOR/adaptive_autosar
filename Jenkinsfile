import groovy.io.FileType
node('pulse_ec2') { 
    String registryUrl = "https://artifact.${env.SWF_DOMAIN}"
    String registryCredentials = 'adasdai-artifactory'
    String userId = sh (script: 'id -u', returnStdout: true).trim()
    String groupId = sh (script: 'id -g', returnStdout: true).trim()
    def imgNameVer = "artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:20201214084936"

    try{
        stage('Checkout') {
            checkout scm
        }
        stage('Code formatting') {
            docker.withRegistry(registryUrl, registryCredentials) {
                docker.image("${imgNameVer}").inside("--entrypoint=''") {
                    stage('C++ formatting check') {
                        sh './devops/scripts/clang-format-apply.sh True'
                    }
                    stage('Python formatting check'){
                        sh './devops/scripts/yapf-format-apply.sh True'
                    }
                    stage('Git message check'){
                        sh '''
                        export LC_ALL=C.UTF-8
                        export LANG=C.UTF-8
                        gitlint --config .gitlint
                        '''
                    }
                    stage('Buildifier check'){
                        sh '/bin/buildifier -r --mode=check .'
                    }
                } // docker
            } 
        }
        stage('Static code analysis') {
            // @Todo:space to add the code analyzer
        }
        stage('x86_64') {
            docker.withRegistry(registryUrl, registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint=''") {
                    stage('Build'){
                        sshagent(['adasdai-jenkins-ssh']) {
                            sh '''
                                # Workaround for circular dependency
                                bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy --config=x86_64_linux
                                bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_skeleton --config=x86_64_linux

                                # Actual build
                                bazel build //:minerva_mpu_adaptive_filesystem --config=x86_64_linux
                            '''
                        }
                    }
                    stage('Test'){
                        // bazel command to run tests execution for x86_64
                    }
                    sh "chown -R ${userId}:${groupId} ."
                }
            }
        }
        stage('aarch64'){
            docker.withRegistry(registryUrl, registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint=''") {
                    stage('Build'){
                        sshagent(['adasdai-jenkins-ssh']) {
                            sh '''
                                # Workaround for circular dependency
                                bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_proxy --config=aarch64_linux_ubuntu
                                bazel build @starter_kit_adaptive_xavier//:amsr_vector_fs_socal_for_skeleton --config=aarch64_linux_ubuntu

                                # Actual build
                                bazel build //:minerva_mpu_adaptive_filesystem --config=aarch64_linux_ubuntu
                            '''
                        }
                    }
                    stage('Test'){
                        // bazel command to run tests execution for aarch64
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
