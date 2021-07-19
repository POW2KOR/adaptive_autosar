set -ex

test_x86_64_linux_ubuntu()
{
    bazel test //devops/cicd/scripts/python/test/... --sandbox_writable_path=$(bazel info workspace)/devops/cicd/scripts/python/test/resources
}
