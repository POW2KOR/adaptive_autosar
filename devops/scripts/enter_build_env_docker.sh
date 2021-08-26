#!/bin/bash

# Please keep this file in sync with .devcontainer/devcontainer.json

current_path=`dirname $(cd -P -- "$(dirname -- "$0")" && printf '%s\n' "$(pwd -P)/$(basename -- "$0")")`
repo_root=$current_path/../..

echo "Repo root is $repo_root"

cd $repo_root/.devcontainer

set -x

docker build \
   --network=host \
   --build-arg HTTP_PROXY=$http_proxy \
   --build-arg http_proxy=$http_proxy \
   --build-arg HTTPS_PROXY=$https_proxy \
   --build-arg https_proxy=$https_proxy \
   --build-arg NO_PROXY=$no_proxy \
   --build-arg no_proxy=$no_proxy \
   -t minerva_mpu_build_env_image .

docker build \
   -t minerva_mpu_build_env_image_with_uid_mapping \
   --network=host \
   --build-arg HTTP_PROXY=$http_proxy \
   --build-arg http_proxy=$http_proxy \
   --build-arg HTTPS_PROXY=$https_proxy \
   --build-arg https_proxy=$https_proxy \
   --build-arg NO_PROXY=$no_proxy \
   --build-arg no_proxy=$no_proxy \
   --build-arg BASE_IMAGE=minerva_mpu_build_env_image \
   --build-arg REMOTE_USER=dev \
   --build-arg NEW_UID=$UID \
   --build-arg NEW_GID=`id -g $UID` \
   --build-arg IMAGE_USER=dev - <<"EOF"
# This Dockerfile is used by enter_build_env_docker.sh to remap the dev user to the main user's ID.
# VS Code does this automatically.

ARG BASE_IMAGE
FROM $BASE_IMAGE

USER root

ARG REMOTE_USER
ARG NEW_UID
ARG NEW_GID
SHELL ["/bin/sh", "-c"]
RUN eval $(sed -n "s/${REMOTE_USER}:[^:]*:\([^:]*\):\([^:]*\):[^:]*:\([^:]*\).*/OLD_UID=\1;OLD_GID=\2;HOME_FOLDER=\3/p" /etc/passwd); \
	eval $(sed -n "s/\([^:]*\):[^:]*:${NEW_UID}:.*/EXISTING_USER=\1/p" /etc/passwd); \
	eval $(sed -n "s/\([^:]*\):[^:]*:${NEW_GID}:.*/EXISTING_GROUP=\1/p" /etc/group); \
	if [ -z "$OLD_UID" ]; then \
		echo "Remote user not found in /etc/passwd ($REMOTE_USER)."; \
	elif [ "$OLD_UID" = "$NEW_UID" -a "$OLD_GID" = "$NEW_GID" ]; then \
		echo "UIDs and GIDs are the same ($NEW_UID:$NEW_GID)."; \
	elif [ "$OLD_UID" != "$NEW_UID" -a -n "$EXISTING_USER" ]; then \
		echo "User with UID exists ($EXISTING_USER=$NEW_UID)."; \
	elif [ "$OLD_GID" != "$NEW_GID" -a -n "$EXISTING_GROUP" ]; then \
		echo "Group with GID exists ($EXISTING_GROUP=$NEW_GID)."; \
	else \
		echo "Updating UID:GID from $OLD_UID:$OLD_GID to $NEW_UID:$NEW_GID."; \
		sed -i -e "s/\(${REMOTE_USER}:[^:]*:\)[^:]*:[^:]*/\1${NEW_UID}:${NEW_GID}/" /etc/passwd; \
		if [ "$OLD_GID" != "$NEW_GID" ]; then \
			sed -i -e "s/\([^:]*:[^:]*:\)${OLD_GID}:/\1${NEW_GID}:/" /etc/group; \
		fi; \
		chown -R $NEW_UID:$NEW_GID $HOME_FOLDER; \
	fi;

ARG IMAGE_USER
USER $IMAGE_USER
EOF

docker run -it \
   --privileged \
   --network=host \
   -e HTTP_PROXY=$http_proxy \
   -e http_proxy=$http_proxy \
   -e HTTPS_PROXY=$https_proxy \
   -e https_proxy=$https_proxy \
   -e NO_PROXY=$no_proxy \
   -e no_proxy=$no_proxy \
   -e force_color_prompt=yes \
   --mount type=bind,source=$HOME/.gitconfig,target=/host/.gitconfig \
   --mount type=bind,source=$HOME/.ssh/gsep,target=/host/.ssh/gsep \
   --mount type=bind,source=$repo_root/.devcontainer/.bazelrc,target=/etc/bazel.bazelrc \
   --mount type=volume,source=mbos_adaptive_build_env_command_history,target=/command_history \
   --mount type=volume,source=mbos_adaptive_build_env_bazel_cache,target=/bazel_cache \
   -v $repo_root:/workspaces/apricot_adaptive \
   -v /var/run/docker.sock:/var/run/docker.sock \
   --workdir /workspaces/apricot_adaptive \
   -t minerva_mpu_build_env_image_with_uid_mapping:latest \
   /bin/bash -c "/workspaces/apricot_adaptive/.devcontainer/post_start.sh $HOME; bash"
