FROM ubuntu:latest

ENV TZ America/New_York

RUN \
  adduser --disabled-password --gecos "" testuser
RUN apt-get update && \
  apt-get install -y \
  gcc-10-arm-linux-gnueabihf binutils-arm-linux-gnueabihf \
  git cmake g++ llvm llvm-dev openssl clang

USER testuser
ADD . /dual-rail/

WORKDIR /dual-rail/passes/build
RUN cmake .. && make

WORKDIR /dual-rail/experimentation/11_aes_eval
RUN make

CMD ["bash"]
