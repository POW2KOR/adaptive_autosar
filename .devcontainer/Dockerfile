FROM artifact.swf.daimler.com/adasdai-docker/minerva_mpu_docker/minerva_mpu:bdcc935587335d4ccff41d0945384396e0014ab7

# The default UID and GID will be changed by VS Code devcontainers to match the current user
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG DEBIAN_FRONTEND=noninteractive

ENV SHELL /bin/bash

# These should be moved to minerva_mpu_docker once proposal is discussed with
# workstream
RUN curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | bash \
    && apt update \
    && apt install -y \
    # Install latest git LFS to avoid OAuth token issues
    git-lfs \
    # Needed for kernel building
    flex bison libssl-dev \
    # Needed for QEMU execution
    qemu-system-arm libguestfs-tools qemu-efi cloud-image-utils \
    # Install for sudo support
    sudo \
    # Needed for libguestfs to work
    linux-image-generic \
    && chmod +r /boot/vmlinuz-* \
    && rm -rf /var/lib/{apt,dpkg,cache,log}/

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    # Add sudo support
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Allow bash history to be persisted betwen sessions. The path at `/command_history` is expected to be persisted across sessions
RUN SNIPPET="export PROMPT_COMMAND='history -a' && export HISTFILE=/command_history/.bash_history" \
    && mkdir /command_history \
    && touch /command_history/.bash_history \
    && echo $SNIPPET >> "/home/$USERNAME/.bashrc"

# Set the default user
USER $USERNAME

RUN git lfs install
