CROSS_COMPILE ?= arm-none-eabi
CLANGOPTS = -target arm-none-eabi -mcpu=arm926ej-s -O0

PLUGINS=$(wildcard ../../passes/build/**/*.so)
PASSES= -hello

all: program.bin

program.bin: program.elf
	$(CROSS_COMPILE)-objcopy -O binary $< $@

program.elf: optimized.o startup.ld startup.o
	$(CROSS_COMPILE)-ld -T startup.ld $< startup.o -o $@

optimized.o: optimized.S
	$(CROSS_COMPILE)-as -ggdb $(CPU) $< -o $@

optimized.S: optimized.ll
	llc -O0 $< -o $@

optimized.ll: manual.LL
	opt -O0 -load="$(PLUGINS)" $(PASSES) $< -S -o $@

program.ll: program.c
	clang $(CLANGOPTS) -S -emit-llvm $<

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

run: program.bin
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel program.bin

.PHONY: clean
clean:
	rm -f *.o *.bin *.elf *.ll optimized.S
test:
