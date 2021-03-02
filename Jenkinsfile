import groovy.io.FileType
@Library('adas-jenkins-shared-lib@ADASDAI-3128-refactor-jenkinsfile') _

initGatekeeper()
/*
def swf_load_script(script_path, use_assigned_utility_node = true) {
    // Chicken-egg-problem. Since this is called before assignment is done,
    // we sometimes have to hardcode the label to allow first initialization

    def target_node_label = ""

    if (use_assigned_utility_node) {
        target_node_label = NODE_UTILITY
    } else {
        target_node_label = "minerva_utility||pulse_ec2"
    }

    node(target_node_label) {
        init_git()
        return load(script_path)
    }
}

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
*/


// timeout in minutes
max_time = 60

assign_node_labels(
    linux_cpu: 'pulse_ec2', 
    linux_gpu_g3: 'minerva_linux_gpu_g3', 
    linux_gpu_g4: 'minerva_linux_gpu_g4', 
    windows_cpu: 'minerva_windows', 
    windows_gpu_g3: 'minerva_windows_gpu_g3', 
    windows_gpu_g4: 'minerva_windows_gpu_g4', 
    utility: 'pulse_ec2',
)


lib_jenkins_steps = swf_load_script("cicd/jenkins/jenkins_steps.groovy")
lib_code_formatting = swf_load_script("ci-depot/jenkins/codeFormattingStage.groovy")
lib_depot_utilities = swf_load_script("ci-depot-test/jenkins/utilities.groovy")


lib_depot_utilities.main_wrapper(
  core_logic: {
    lib_depot_utilities.parallel_stage('Initialize', [
        lib_jenkins_steps.initialize()
    ])
    

    // TODO: Move into ci-depot
    node(env.NODE_LINUX_CPU) {
        lib_code_formatting.runFormatting(rootDir)
    }

    lib_depot_utilities.parallel_stage('Builds', [
        lib_jenkins_steps.compile_x86_64_linux_ubuntu('x86_64_linux_ubuntu'),
        lib_jenkins_steps.compile_aarch64_linux_ubuntu('aarch64_linux_ubuntu'),
        lib_jenkins_steps.compile_aarch64_linux_linaro('aarch64_linux_linaro')
    ])
    
    lib_depot_utilities.parallel_stage('Tests', [
    ])
  }
,
failure_handler: {
  
}
)
