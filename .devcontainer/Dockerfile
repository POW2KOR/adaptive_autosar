FROM ubuntu:18.04

# The default UID and GID will be changed by VS Code devcontainers to match the current user
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV SHELL /bin/bash

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y git gpgconf \
    # Add sudo support
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Allow bash history to be persisted betwen sessions. The path at `/commandhistory` is expected to be persisted across sessions
RUN SNIPPET="export PROMPT_COMMAND='history -a' && export HISTFILE=/commandhistory/.bash_history" \
    && mkdir /commandhistory \
    && touch /commandhistory/.bash_history \
    && echo $SNIPPET >> "/home/$USERNAME/.bashrc"

# Set the default user
USER $USERNAME
