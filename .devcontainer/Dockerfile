FROM mcr.microsoft.com/devcontainers/base:jammy

RUN apt-get update && apt-get install -y \
  g++ \
  cmake \
  python3-venv \
  graphviz \
  && rm -rf /var/lib/apt/lists/*

RUN curl -fsSOL https://github.com/doxygen/doxygen/releases/download/Release_1_9_6/doxygen-1.9.6.linux.bin.tar.gz \
  && tar -zxvf doxygen-1.9.6.linux.bin.tar.gz \
  && (cd doxygen-1.9.6 && make install) \
  && rm -r doxygen-1.9.6.linux.bin.tar.gz doxygen-1.9.6

USER vscode
RUN python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)" \
  && $HOME/.platformio/penv/bin/pio system completion install bash \
  && echo "export PATH=$PATH:$HOME/.platformio/penv/bin" >> ~/.bashrc \
  && echo ". /home/vscode/.bash_completion" >> ~/.bashrc
