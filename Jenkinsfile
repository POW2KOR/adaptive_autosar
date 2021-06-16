/**
* This executes a pipeline based on Pipeliner.
* The pipeline can be found in the mbient-pipeliner-depot at
* https://git.swf.daimler.com/mbient/mbient-pipeliner-depot
*
* For more information about Pipeliner and pipelines, refer to the documentation
* in https://github.com/Daimler/pipeliner
*
* See documentation for input parameters of all pipelines:
* https://artifact.swf.daimler.com/mbient/docs/mbient-pipeliner-depot/release-latest/groovydoc/index.html
*/

// Specify the manifest and branch
// Change these if your repo is not part of the main QNX build
env.PIP_MANIFEST_URL = "ssh://git@git.swf.daimler.com:7999/apricot/adaptive_autosar_manifest.git"
env.PIP_MANIFEST_BRANCH = "master"
env.PIP_MANIFEST_FILE="default.xml"

// This enables checkout for the component
// This must be specified unless you want to run with default manifest file
env.PIP_COMPONENT_DIR = "adaptive_autosar"

env.PIP_DOCKERIMAGE="artifact.swf.daimler.com/apricot-docker/xpf/xpf_adaptive_build_image:latest"

env.PIP_BUILD_CMD = "./build.sh"

// Archive
env.PIP_ARCHIVE = "true"
env.PIP_ARCHIVE_IMAGE_FOLDERS = "artifacts/"

@Library('mbient-pipeliner-depot@release-latest') _
execQnxPipeline()
