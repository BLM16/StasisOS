CFLAGS  = -c -g -ffreestanding -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fstack-protector -mgeneral-regs-only -fPIC -mcmodel=large -Wall -Wextra
ASFLAGS = -g -F dwarf
LDFLAGS = -n

kernel_cpp_src := $(shell find src/kernel -name *.cpp)
kernel_cpp_obj := $(patsubst src/kernel/%.cpp, build/kernel/%.o, $(kernel_cpp_src))

x86_64_asm_src := $(shell find src/x86_64 -name *.asm)
x86_64_asm_obj := $(patsubst src/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_src))
x86_64_cpp_src := $(shell find src/x86_64 -name *.cpp)
x86_64_cpp_obj := $(patsubst src/x86_64/%.cpp, build/x86_64/%.o, $(x86_64_cpp_src))

kernel_obj := $(kernel_cpp_obj)
x86_64_obj := $(x86_64_asm_obj) $(x86_64_cpp_obj)

##################################################
# Kernel object files
##################################################
$(kernel_cpp_obj): build/kernel/%.o : src/kernel/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -I src/intf -I src/x86_64/boot/intf $(CFLAGS) $(patsubst build/kernel/%.o, src/kernel/%.cpp, $@) -o $@



##################################################
# x86_64 object files
##################################################
$(x86_64_asm_obj): build/x86_64/%.o : src/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm $(ASFLAGS) -f elf64 $(patsubst build/x86_64/%.o, src/x86_64/%.asm, $@) -o $@

$(x86_64_cpp_obj): build/x86_64/%.o : src/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -I src/intf -I src/x86_64/boot/intf $(CFLAGS) $(patsubst build/x86_64/%.o, src/x86_64/%.cpp, $@) -o $@



##################################################
# PHONY
##################################################
.PHONY: build-x86_64
build-x86_64: $(kernel_obj) $(x86_64_obj)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -T targets/x86_64/linker.ld $(LDFLAGS) -o dist/x86_64/kernel.bin $(kernel_obj) $(x86_64_obj) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin &&\
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

.PHONY: clean
clean:
	rm -rf build/
	rm -rf dist/
	rm -f targets/x86_64/iso/boot/kernel.bin
