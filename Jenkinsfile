import groovy.io.FileType
@Library('adas-jenkins-shared-lib@master') _

initGatekeeper()

// timeout in minutes
max_time = 60

assign_node_labels()


lib_jenkins_steps = swf_load_script('devops/cicd/jenkins/jenkins_steps.groovy')
lib_code_gatekeeper = swf_load_script('devops/ci-depot/jenkins/gatekeeper.groovy')
lib_depot_utilities = swf_load_script('devops/ci-depot/jenkins/utilities.groovy')

lib_depot_utilities.main_wrapper(
  core_logic: {
    lib_depot_utilities.parallel_stage('Initialize', [
        lib_jenkins_steps.initialize()
    ])

    lib_depot_utilities.parallel_stage('Sanity', [
        lib_code_gatekeeper.inspect()
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
