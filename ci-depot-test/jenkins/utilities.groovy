// -*- mode: groovy -*-


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

return this