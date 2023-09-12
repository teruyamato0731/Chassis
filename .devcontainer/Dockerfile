FROM mcr.microsoft.com/devcontainers/base:jammy

RUN apt-get update && apt-get install -y \
  g++ \
  cmake \
  python3-pip \
  python3-venv \
  graphviz \
  bash-completion \
  && rm -rf /var/lib/apt/lists/*

RUN curl -fsSOL https://github.com/doxygen/doxygen/releases/download/Release_1_9_6/doxygen-1.9.6.linux.bin.tar.gz \
  && tar -zxvf doxygen-1.9.6.linux.bin.tar.gz \
  && (cd doxygen-1.9.6 && make install) \
  && rm -r doxygen-1.9.6.linux.bin.tar.gz doxygen-1.9.6

RUN python3 -m pip install --no-cache-dir -U \
  platformio
RUN pio system completion install bash
