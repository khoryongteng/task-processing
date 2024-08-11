FROM ubuntu:22.04

ARG REQUIRED_PACKAGES=" \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
"

RUN apt-get update && apt-get install -y \
    $REQUIRED_PACKAGES \
    && rm -rf /var/lib/apt/lists/*