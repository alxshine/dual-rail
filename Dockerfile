FROM ubuntu:latest

RUN \
  adduser --disabled-password --gecos "" testuser
RUN apt-get update && \
  apt-get install -y \
  gcc-10-arm-linux-gnueabihf binutils-arm-linux-gnueabihf \
  qemu-system-arm gdb-multiarch\
  git cmake g++ llvm llvm-dev openssl clang expect

ENV QEMU_AUDIO_DRV none

USER testuser
ADD . /dual-rail/

WORKDIR /dual-rail/passes/build
RUN cmake .. && make

WORKDIR /dual-rail/experimentation/11_aes_eval

CMD bash ./evaluate.sh
