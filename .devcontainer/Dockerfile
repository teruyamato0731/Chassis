FROM mcr.microsoft.com/devcontainers/base:jammy

RUN apt-get update && apt-get install -y \
  g++ \
  cmake \
  python3-pip \
  python3-venv \
  graphviz \
  bash-completion \
  && rm -rf /var/lib/apt/lists/*

ARG VERSION="1.9.8"
RUN curl -fsSOL https://www.doxygen.nl/files/doxygen-${VERSION}.linux.bin.tar.gz \
  && tar -zxvf doxygen-${VERSION}.linux.bin.tar.gz \
  && (cd doxygen-${VERSION} && make install) \
  && rm -r doxygen-${VERSION}.linux.bin.tar.gz doxygen-${VERSION}

RUN python3 -m pip install --no-cache-dir -U \
  platformio
RUN pio system completion install bash --path /etc/bash_completion.d/platformio
