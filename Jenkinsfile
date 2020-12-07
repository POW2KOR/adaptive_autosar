import groovy.io.FileType
node('pulse_ec2')
{ 
    String registryUrl = "https://artifact.${env.SWF_DOMAIN}"
    String registryCredentials = 'adas-artifactory'
    def imgNameVer = "artifact.swf.daimler.com/adas-docker/minerva_mpu_docker/tmp/feature/update-nvidia-5-2-0-0/minerva_mpu:20201201144342"
    try{
        stage('checkout') {
            checkout scm
        }
        stage('code formatter') {
            docker.withRegistry(registryUrl, registryCredentials) {
                docker.image("${imgNameVer}").inside("--entrypoint=''") {
                    stage('C++ code formatter - clang') {
                        sh './devops/scripts/clang-format-apply.sh True'
                    }
                    stage('python code formatter - yapf'){
                        sh './devops/scripts/yapf-format-apply.sh True'
                    }
                    stage('Git message check - gitlint'){
                        sh '''
                        export LC_ALL=C.UTF-8
                        export LANG=C.UTF-8
                        gitlint --config .gitlint
                        '''
                    }
                } // docker
            } 
        }
        stage('static code analysis') {
            // @Todo:space to add the code analyzer
        }
        stage('build vector_sip_aa') {
            String userId = sh (script: 'id -u', returnStdout: true).trim()
            String groupId = sh (script: 'id -g', returnStdout: true).trim()
            docker.withRegistry(registryUrl, registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint=''") {
                    sshagent(['adas-jenkins-ssh']) {
                        sh '''
                           bazel --version
                           bazel build @vector_sip_aa//:amsr-vector-fs-sec-cryptostack --config=x86_64_linux
                        '''
                    }
                    sh "chown -R ${userId}:${groupId} ."
                }
            }
        }
        stage('x86_64'){
            docker.image("${imgNameVer}").inside("--entrypoint=''") {
                stage('setup env'){
                   // Add code to setup environment for x86_64               
                }
                stage('build stack'){
                   // bazel command to build x86_64
                }
                stage('test stack'){
                    // bazel command to run tests execution for x86_64
                }
            } // docker
        }
        stage('aarch64'){
             docker.image("${imgNameVer}").inside("--entrypoint=''") {
                 stage('setup env'){
                   // Add code to setup environment for aarch64
                 }
                 stage('build stack'){
                    // bazel command to build aarch64
                 }
            } // docker
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
