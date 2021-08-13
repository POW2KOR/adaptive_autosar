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

@Library('mbient-pipeliner-depot@release-latest') _
import com.daimler.pipeliner.Logger
import com.daimler.pipeliner.ScriptUtils

node("CloudYocto") {

    ScriptUtils utils = new ScriptUtils(this, env.getEnvironment())

    // Specify the manifest and branch
    // Change these if your repo is not part of the main QNX build
    env.PIP_MANIFEST_URL = "ssh://git@git.swf.daimler.com:7999/apricot/adaptive_autosar_manifest.git"
    env.PIP_MANIFEST_BRANCH = "master"
    env.PIP_MANIFEST_FILE="default.xml"

    // Temporarily downgrading the SDP version
    env.PIP_QNX_SDP_VERSION = "SDP700_EXP_Gen3_Patchset_HQX0_2_ES_5_1_20210211_Updated"

    // This enables checkout for the component
    // This must be specified unless you want to run with default manifest file
    env.PIP_COMPONENT_DIR = "adaptive_autosar"

    env.PIP_DOCKERIMAGE="artifact.swf.daimler.com/apricot-docker/xpf/xpf_adaptive_build_image:latest"

    env.PIP_BUILD_CMD = "./build.sh"

    // Archive
    env.PIP_ARCHIVE = "true"
    env.PIP_ARCHIVE_IMAGE_FOLDERS = "artifacts/"

    // Execute the generalised QNX pipeline
    execQnxPipeline()

    // Publish images to git only during manual execution but not oncommit jobs
    if (env.JOB_NAME.contains("component.adaptive-autosar.master.manual")) {
        stage("Publish Images") {

            String package_to_release = "apricot_adaptive_filesystem_aarch64_qnx.tar"

            if(env.RELEASE_LABEL != null && !env.RELEASE_LABEL.isEmpty()) {
                // Copy the file archived by the QNX pipeline
                utils.downloadFromArtifactory("apricotbscqal/build/component.adaptive-autosar.master.manual/${env.BUILD_NUMBER}/${package_to_release}", "./", true)

                // Publish the package to Artifactory
                utils.uploadToArtifactory("${package_to_release}","apricot-bin-delivery/xpf/adaptive-autosar/${env.RELEASE_LABEL}/",true)
                utils.uploadToArtifactory("${package_to_release}","apricot-bin-delivery/xpf/adaptive-autosar/latest/",true)
            }
        }

        stage("Cleanup") {
            step([$class: 'WsCleanup'])
        }
    }
}
