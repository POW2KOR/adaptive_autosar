# Docker for Adaptive AUTOSAR
This layer is based on the NVIDIA provided docker image which is available in SWF Artifactory.

## Getting the docker image
There is a CI/CD pipeline in place, which will create the docker image and push it to Artifactory.
This docker image shall be used as development environment for the MPU.

**If further tools are needed please raise a merge request (MR) or create a Jira ticket and assign it to the ECU SW Integration team.**

```
# login to SWF Artifactory
docker login artifact.swf.daimler.com

# pull the latest docker image
docker pull artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:latest

# or you can pull a specific docker image based on the commit hash
docker pull artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:<commit-hash>
```

### Solutions to common problems

#### No docker credential store
When you run `docker login artifact.swf.daimler.com`, if you see the following message:
```
Error saving credentials: error storing credentials - err: exec: "docker-credential-secretservice": executable file not found in $PATH, out: ``
```

Install the credential helpers: `sudo apt install golang-docker-credential-helpers`

#### SIGSEGV when running docker login
When you run `docker login artifact.swf.daimler.com`, and you see the following error messages:
```
panic: runtime error: invalid memory address or nil pointer dereference
[signal SIGSEGV: segmentation violation code=0x1 addr=0x8 pc=0x55d4db285ce6]

goroutine 1 [running]:
github.com/docker/cli/cli/command.ConfigureAuth(0x55d4dcec6e40, 0xc00042b6c0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x55d4dce36200, 0xc0002c0b50, 0xc00058f968)
        /go/src/github.com/docker/cli/cli/command/registry.go:128 +0x46
github.com/docker/cli/cli/command/registry.runLogin(0x55d4dcec6e40, 0xc00042b6c0, 0x7ffedc8bb386, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, ...)
```

It can be solved by also passing `-u <your daimler login>` to `docker login`.

## Usage
You can try out the docker container by building the ```minerva_mpu_adaptive``` repository.

You can clone and prepare the repository on your host before running the docker container.
Running the latest docker container by mounting the ```minerva_mpu_adaptive``` folder:
```
# start the docker container (adapt your minerva_mpu_adaptive repository path)
docker run -it --name=minerva_mpu_dev --rm --privileged --network=host -e https_proxy=$https_proxy -e http_proxy=$http_proxy -e no_proxy=hksmirror.rd.corpintra.net,ubunturepo.rd.corpintra.net -v /lib/modules/$(uname -r):/lib/modules/$(uname -r) -v /dev/bus/usb:/dev/bus/usb -v /lhome/$USER/workspace/minerva/minerva_mpu_adaptive/:/root/workspace/minerva_mpu_adaptive --workdir /root/workspace artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:latest

# inside the docker
cd /root/workspace/minerva_mpu_adaptive/

# build application
bazel build :mbition_app_prototype --//:build-target="minerva-host"

# in case of a slow internet connection
bazel build :mbition_app_prototype --//:build-target="minerva-host" --experimental_scale_timeouts=10

# if needed you can copy your SSH private key (run the command outside the docker container)
docker cp /lhome/$USER/.ssh/id_rsa minerva_mpu_dev:/root/.ssh
```

If you encounter problems when cloning and the SSH credentials are valid, it can be due to some DNS issues.
These problems were solved by adding the following content in `/etc/docker/daemon.json`:
```
{ "dns": ["53.60.5.254", "53.60.7.254"] }
```

A docker service restart is needed to apply the settings:
```
sudo systemctl restart docker
```

If you need also docker support inside the docker image you need to add the `-v /var/run/docker.sock:/var/run/docker.sock` option to mount the docker socket.

## Building the image locally (not recommended, instead download it from Artifactory)
```
docker build -t minerva_mpu --network=host --build-arg https_proxy=$https_proxy --build-arg http_proxy=$http_proxy --build-arg no_proxy=hksmirror.rd.corpintra.net,ubunturepo.rd.corpintra.net .
```
If you want to have the same docker system group ID add to the docker build ``--build-arg BUILD_DOCKER_GID=`getent group docker | awk -F: '{printf "%d\n", $3}'` ``.

## Setting up SSH agent authentication inside docker
If you need to use your SSH keys from inside the container you can use `ssh-agent`.

Before running the docker please run the commands below in your terminal:
```
eval `ssh-agent`
ssh-add <path to ssh key(Usually ~/.ssh/)>id_rsa
<enter passphrase>
```
Now add the below option to the docker run command
```
docker run --volume $SSH_AUTH_SOCK:/ssh-agent --env SSH_AUTH_SOCK=/ssh-agent
```
