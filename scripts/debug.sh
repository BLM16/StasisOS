#!/bin/sh

set -e

this_dir="${0%/*}"
proj_root_dir="$(cd $this_dir/..; pwd)"

# Build the project
sh $this_dir/build.sh

# Run the qemu emulator and gdb in a subshell
# Set the subshell directory to the project root
(
    cd $proj_root_dir &&
    qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso -s -S &
    gdb --quiet -ex "target remote localhost:1234" -ex "set disassembly-flavor intel" \
        -ex "symbol-file dist/x86_64/kernel.bin"
)
