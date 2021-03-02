import groovy.io.FileType
@Library('adas-jenkins-shared-lib@master') _

initGatekeeper()

// initialize source codes
def init_git() {
  deleteDir()
  retry(5) {
    try {
      timeout(time: 15, unit: 'MINUTES') {
        sshagent([env.sshJenkinsCredentials]) { 
            checkout scm
            sh 'git clean -xdff'
            sh 'git reset --hard'
            sh 'git submodule update --init --recursive'
            sh 'git submodule foreach --recursive git clean -ffxd'
            sh 'git submodule foreach --recursive git reset --hard'
        }
      }
    } catch (exc) {
      deleteDir()
      error "Failed to fetch source codes with ${exc}"
      sleep 2
    }
  }
}

def parallel_stage(stage_name, steps) {
    // Allow to pass an array of steps that will be executed in parallel in a stage
    new_map = [:]

    for (def step in steps) {
        new_map = new_map << step
    }

    stage(stage_name) {
      parallel new_map
    }
}

// pack libraries for later use
def pack_lib(name, libs, include_gcov_data = false) {
  sh returnStatus: true, script: """
set +e
echo "Packing ${libs} into ${name}"
for i in \$(echo ${libs} | sed -e 's/,/ /g'); do md5sum \$i; ls -lh \$i; done
return 0
"""
  stash includes: libs, name: name

  //if (include_gcov_data) {
  //  // Store GCNO files that are required for GCOV to operate during runtime
  //  sh "find . -name '*.gcno'"
  //  stash name: "${name}_gcov_data", includes: "**/*.gcno"
  //}
}

def assign_node_labels(args) {
  // This function allows to assign instance labels to the generalized placeholders.
  // This serves two purposes:
  // 1. Allow generalized placeholders (e.g. NODE_WINDOWS_CPU) in the job definition
  //    in order to abstract away the underlying node label. This allows to schedule a job
  //    onto a different node for testing or security reasons. This could be, for example,
  //    when you want to test a new set of slaves on separate labels or when a job should
  //    only be run on restricted slaves
  // 2. Restrict the allowed job types within a Jenkinsfile. For example, a UNIX-CPU-only
  //    Jenkinsfile should not allowed access to Windows or GPU instances. This prevents
  //    users from just copy&pasting something into an existing Jenkinsfile without
  //    knowing about the limitations.
  NODE_LINUX_CPU = args.linux_cpu
  NODE_LINUX_GPU_G3 = args.linux_gpu_g3
  NODE_LINUX_GPU_G4 = args.linux_gpu_g4
  NODE_WINDOWS_CPU = args.windows_cpu
  NODE_WINDOWS_GPU_G3 = args.windows_gpu_g3
  NODE_WINDOWS_GPU_G4 = args.windows_gpu_g4
  NODE_UTILITY = args.utility
}

def main_wrapper(args) {
  // Main Jenkinsfile pipeline wrapper handler that allows to wrap core logic into a format
  // that supports proper failure handling
  // args:
  // - core_logic: Jenkins pipeline containing core execution logic
  // - failure_handler: Failure handler

  // assign any caught errors here
  err = null
  try {
    args['core_logic']()

    // set build status to success at the end
    currentBuild.result = "SUCCESS"
  } catch (caughtError) {
    node(NODE_UTILITY) {
      echo "caught ${caughtError}"
      err = caughtError
      currentBuild.result = "FAILURE"
    }
  } finally {
    node(NODE_UTILITY) {
      // Call failure handler
      args['failure_handler']()

      // Clean workspace to reduce space requirements
      cleanWs()

      // Remember to rethrow so the build is marked as failing
      if (err) {
        throw err
      }
    }
  }
}
// ------------------------------

// stash libraries
stash_lib_x86_64_linux_ubuntu = '' //TODO: Fill in artifacts
stash_lib_aarch64_linux_ubuntu = '' //TODO: Fill in artifacts
stash_lib_aarch64_linux_linaro = '' //TODO: Fill in artifacts


def compile_x86_64_linux_ubuntu(lib_name) {
    return ['x86_64_linux_ubuntu': {
      node(NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()

            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
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

                    //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                    //This will explode as soon as issues during the build arise as files will be left as root and undeletable
                    sh "chown -R ${userId}:${groupId} ."
                }
            }

            pack_lib(lib_name, stash_lib_x86_64_linux_ubuntu, true)
        }
      }
    }]
}


def compile_aarch64_linux_ubuntu(lib_name) {
    return ['aarch64_linux_ubuntu': {
      node(NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()

            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
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

                    //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                    //This will explode as soon as issues during the build arise as files will be left as root
                    sh "chown -R ${userId}:${groupId} ."
                }
            }

            pack_lib(lib_name, stash_lib_aarch64_linux_ubuntu, true)
        }
      }
    }]
}



def compile_aarch64_linux_linaro(lib_name) {
    return ['aarch64_linux_linaro': {
      node(NODE_LINUX_CPU) {
        timeout(time: max_time, unit: 'MINUTES') {
            init_git()

            // TODO move docker and ssh agent boilerplate into library function
            docker.withRegistry(env.registryUrl, env.registryCredentials) {
                docker.image("${imgNameVer}").inside("-u 0:0 --entrypoint='' ${env.diskCache} ${remoteUpload}") {
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

                    //TODO: Don't invoke Docker with 0:0 but fix the permissions properly than doing this hack
                    //This will explode as soon as issues during the build arise as files will be left as root
                    sh "chown -R ${userId}:${groupId} ."
                }
            }

            pack_lib(lib_name, stash_lib_aarch64_linux_linaro, true)
        }
      }
    }]
}


// -----------------------------


// timeout in minutes
max_time = 240

assign_node_labels(
    linux_cpu: 'pulse_ec2', 
    linux_gpu_g3: 'minerva_linux_gpu_g3', 
    linux_gpu_g4: 'minerva_linux_gpu_g4', 
    windows_cpu: 'minerva_windows', 
    windows_gpu_g3: 'minerva_windows_gpu_g3', 
    windows_gpu_g4: 'minerva_windows_gpu_g4', 
    utility: 'pulse_ec2',
)

main_wrapper(
  core_logic: {
    node(NODE_UTILITY) {
        init_git()
        rootDir = pwd()
        codeFormattingLib = load "${rootDir}/ci-depot/jenkins/codeFormattingStage.groovy"

        registryUrl = "https://artifact.${env.SWF_DOMAIN}"
        registryCredentials = 'adasdai-artifactory'
        userId = sh (script: 'id -u', returnStdout: true).trim()
        groupId = sh (script: 'id -g', returnStdout: true).trim()
        imgNameVer = "artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:20210216120747"
        boolean isMaster = (env.BRANCH_NAME == 'master')
        remoteUpload = "-e isMaster=${isMaster}"

        String bazelrc  = "${env.WORKSPACE}/.bazelrc"
        DISK_CACHE = sh ( script: """sed -n 's/.*--disk_cache="\\(.*\\)"/\\1/p' ${bazelrc}""", returnStdout: true).trim()
        env.diskCache = "-v /home/efs_cache/mpu:${DISK_CACHE}"
    }

    // TODO: Move into ci-depot
    node(NODE_LINUX_CPU) {
        codeFormattingLib.runFormatting(rootDir)
    }

    parallel_stage('Builds', [
        compile_x86_64_linux_ubuntu('x86_64_linux_ubuntu'),
        compile_aarch64_linux_ubuntu('aarch64_linux_ubuntu'),
        compile_aarch64_linux_linaro('aarch64_linux_linaro')
    ])

    
    //parallel_stage('Tests', [
    //])
  }
,
failure_handler: {
  
}
)

/*
node('pulse_ec2') {
    String registryUrl = "https://artifact.${env.SWF_DOMAIN}"
    String registryCredentials = 'adasdai-artifactory'
    String userId = sh (script: 'id -u', returnStdout: true).trim()
    String groupId = sh (script: 'id -g', returnStdout: true).trim()
    def imgNameVer = "artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:20210216120747"
    boolean isMaster = (env.BRANCH_NAME == 'master')
    String remoteUpload = "-e isMaster=${isMaster}"
    
    try{
        stage('Prepare') {
            String bazelrc  = "${env.WORKSPACE}/.bazelrc"
            DISK_CACHE = sh ( script: """sed -n 's/.*--disk_cache="\\(.*\\)"/\\1/p' ${bazelrc}""", returnStdout: true).trim()
            env.diskCache = "-v /home/efs_cache/mpu:${DISK_CACHE}"
        }
        stage('Static code analysis') {
            // @Todo:space to add the code analyzer
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
*/