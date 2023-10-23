#!/bin/sh

set -e

sh build.sh
qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso -s -S &
gdb --quiet -ex "target remote localhost:1234" -ex "set disassembly-flavor intel" \
    -ex "symbol-file dist/x86_64/kernel.bin"
