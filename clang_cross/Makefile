CROSS_COMPILE ?= arm-none-eabi

CPU = #-mcpu=arm926ej-s
COPTS = -Wall -Werror -std=gnu99 -ggdb -O0
#CLANGOPTS = -target armv7--none-eabi
CLANGOPTS = -target armv7a-linux-gnueabihf 

all: program.bin

%.bin: %.elf
	$(CROSS_COMPILE)-objcopy -O binary $< $@

%.elf: %.o startup.ld startup.o
	$(CROSS_COMPILE)-ld -T startup.ld $< startup.o -o $@

%.optll: %.ll
	opt $< -S -o $@

%.ll: %.c
	clang $(CLANGOPTS) -S -emit-llvm $<

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

%.llvmas: %.optll
	llc $< -o $@

%.o: %.llvmas
	$(CROSS_COMPILE)-as -ggdb $(CPU) $< -o $@

run: program.bin
	~/Projects/qemu-eval/arm-softmmu/qemu-system-arm -M versatilepb -m 128M -nographic -kernel program.bin

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.elf
