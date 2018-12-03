CROSS_COMPILE ?= arm-none-eabi

CPU = -mcpu=arm926ej-s
COPTS = -Wall -Werror -std=gnu99 -ggdb

all: test.bin

%.bin: %.elf
	$(CROSS_COMPILE)-objcopy -O binary $< $@

%.elf: %.o startup.ld startup.o
	$(CROSS_COMPILE)-ld -T startup.ld $< startup.o -o $@

%.o: %.c print.h
	$(CROSS_COMPILE)-gcc -c $(CPU) $(COPTS) $< -o $@

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

run: test.bin
	qemu-system-arm -S -M versatilepb -m 128M -nographic -kernel test.bin

.PHONY: clean
clean:
	rm *.o *.bin *.elf trace*
