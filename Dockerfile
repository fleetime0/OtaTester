FROM ubuntu:bionic

ENV DEBIAN_FRONTEND=noninteractive

ENV TZ=Asia/Shanghai

RUN apt-get update && apt-get install -y \
    vim \
    git \
    curl \
    wget \
    python3 \
    iputils-ping \
    openjdk-17-jdk \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

RUN CMAKE_VERSION=3.29.6 && \
    ARCH=$(uname -m) && \
    case "$ARCH" in \
        x86_64) ARCH_NAME="x86_64" ;; \
        aarch64) ARCH_NAME="aarch64" ;; \
        *) echo "Unsupported architecture: $ARCH" && exit 1 ;; \
    esac && \
    curl -L https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-${ARCH_NAME}.sh \
        -o /tmp/cmake.sh && \
    sh /tmp/cmake.sh --prefix=/usr/local --skip-license && \
    rm /tmp/cmake.sh

WORKDIR /workspace

CMD ["sleep", "infinity"]
