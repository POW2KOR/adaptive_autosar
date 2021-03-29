FROM artifact.swf.daimler.com/adasdai-docker/nvidia/drive/build_driveos_linux_pdk:common-5.2.3.0

ARG BUILD_USER="root"
ARG BUILD_DOCKER_GID

RUN  mkdir -p /usr/tools/bazel/
COPY configuration/docker-apt.key.pub /tmp/
COPY configuration/known_hosts /${BUILD_USER}/.ssh/
COPY ./tools/bazel/ /usr/tools/bazel/

USER root

RUN if [ -z $BUILD_DOCKER_GID ]; then echo "DOCKER GID will not set to system ones"; else groupadd -g $BUILD_DOCKER_GID docker ; fi && \
    echo "deb https://download.docker.com/linux/ubuntu/ bionic stable" >> /etc/apt/sources.list && \
    apt-key add /tmp/docker-apt.key.pub && \
    apt-get --assume-yes  update && \
    apt-get --assume-yes install zip \
    bash-completion \
    clang \
    clang-format-7 \
    clang-10 \
    clang-tools-10 \
    clang-tidy-10 \
    clangd-10 \
    curl \
    docker-ce \
    git-lfs \
    graphviz \
    iputils-arping \
    iputils-ping \
    lcov \
    openjdk-8-jdk \
    python3-pip \
    python3-dev \
    python3-git \
    python3-setuptools \
    python3-venv \
    python3-wheel \
    xdot \
    zlib1g-dev && \
    apt-get clean && \
    dpkg -i /usr/tools/bazel/bazel_4.0.0-linux-x86_64.deb && \
    rm /usr/tools/bazel/bazel_4.0.0-linux-x86_64.deb && \
    mv /usr/tools/bazel/buildifier /bin/buildifier && \
    mv /usr/tools/bazel/buildozer /bin/buildozer && \
    chmod +x /bin/buildifier /bin/buildozer && \
    python3 -m pip install -U pip && \
    pip3 install invoke cpplint docker-compose mypy autopep8 yapf gitlint robotframework pytest && \
    pip3 install --ignore-installed pre-commit==2.11.1 && \
    rm -r /tmp && \
    ln -s /usr/bin/clang-format-7 /usr/bin/clang-format

USER ${BUILD_USER}

ENTRYPOINT []
CMD ["/bin/bash"]
