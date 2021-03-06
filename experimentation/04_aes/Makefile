CROSS_COMPILE ?= arm-none-eabi
CLANGOPTS = -target arm-none-eabi -mcpu=arm926ej-s -O0

PLUGINS=$(wildcard ../../passes/build/**/*.so)
PASSES= 

all: program.bin

tinyAES.o: tinyAES_raw.c
	clang $(CLANGOPTS) -S -emit-llvm tinyAES_raw.c -o tinyAES.ll
	opt -load="$(PLUGINS)" $(PASSES) tinyAES.ll -S -o aes_optimized.ll
	llc aes_optimized.ll -o aes_optimized.S
	$(CROSS_COMPILE)-as -ggdb $(CPU) aes_optimized.S -o tinyAES.o

program.o: program.c
	clang $(CLANGOPTS) -S -emit-llvm program.c -o program.ll
	opt -load="$(PLUGINS)" $(PASSES) program.ll -S -o optimized.ll
	llc optimized.ll -o optimized.S
	$(CROSS_COMPILE)-as -ggdb $(CPU) optimized.S -o program.o

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

program.bin: program.elf
	$(CROSS_COMPILE)-objcopy -O binary $< $@

program.elf: program.o startup.ld tinyAES.o startup.o
	$(CROSS_COMPILE)-ld -T startup.ld program.o tinyAES.o startup.o -o program.elf

run: program.bin
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel program.bin

.PHONY: clean
clean:
	rm -f *.o *.bin *.elf *.ll optimized.S
test:
