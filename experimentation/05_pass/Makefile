CROSS_COMPILE ?= arm-none-eabi
CLANGOPTS = -target arm-none-eabi -mcpu=arm926ej-s -O0

PLUGINS=$(wildcard ../../passes/build/*.so)
PASSES=-insert

all: program.bin

optimized.S: tinyAES.ll rtlib.ll program.ll
	llvm-link tinyAES.ll rtlib.ll program.ll -S -o linked.ll
	opt -load="$(PLUGINS)" $(PASSES) linked.ll -S -o optimized.ll
	llc optimized.ll -o optimized.S

optimized.o: optimized.S
	$(CROSS_COMPILE)-as -ggdb $(CPU) optimized.S -o optimized.o

%.ll: %.c
	clang $(CLANGOPTS) $< -S -emit-llvm -o $@

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

program.bin: program.elf
	$(CROSS_COMPILE)-objcopy -O binary $< $@

program.elf: startup.o startup.ld optimized.o
	$(CROSS_COMPILE)-ld -T startup.ld startup.o optimized.o -o program.elf

run: program.bin
	~/Projects/qemu-eval/arm-softmmu/qemu-system-arm -M versatilepb -m 128M -nographic -kernel program.bin

.PHONY: clean
clean:
	rm -f *.o *.bin *.elf *.ll optimized.S
test:
