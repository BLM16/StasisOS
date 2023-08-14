FROM randomdude/gcc-cross-x86_64-elf

RUN echo "deb http://archive.debian.org/debian stretch main contrib non-free" > /etc/apt/sources.list
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y nasm xorriso grub-pc-bin grub-common

WORKDIR /root/env
ENTRYPOINT [ "/bin/sh" ]
