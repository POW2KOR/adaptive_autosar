import groovy.io.FileType
@Library('adas-jenkins-shared-lib@ADASDAI-3128-refactor-jenkinsfile') _

initGatekeeper()

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


lib_jenkins_steps = swf_load_script('cicd/jenkins/jenkins_steps.groovy')
lib_code_formatting = swf_load_script('ci-depot/jenkins/codeFormattingSteps.groovy')
lib_depot_utilities = swf_load_script('ci-depot/jenkins/utilities.groovy')

lib_depot_utilities.main_wrapper(
  core_logic: {
    lib_depot_utilities.parallel_stage('Initialize', [
        lib_jenkins_steps.initialize()
    ])

    lib_depot_utilities.parallel_stage('Sanity', [
        lib_code_formatting.code_formatting()
    ])

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
