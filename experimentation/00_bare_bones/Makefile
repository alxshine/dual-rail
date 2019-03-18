CROSS_COMPILE ?= arm-none-eabi

CPU = -mcpu=arm926ej-s
COPTS = -Wall -Werror -std=gnu99 -ggdb

all: test.bin aes.bin

%.bin: %.elf
	$(CROSS_COMPILE)-objcopy -O binary $< $@

%.elf: %.o startup.ld startup.o tinyAES.o
	$(CROSS_COMPILE)-ld -T startup.ld $< startup.o tinyAES.o -o $@

%.o: %.c print.h
	$(CROSS_COMPILE)-gcc -c $(CPU) $(COPTS) $< -o $@

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

run: test.bin
	~/Projects/qemu/arm-softmmu/qemu-system-arm -M versatilepb -m 128M -nographic -kernel test.bin

.PHONY: clean
clean:
	rm -f *.o *.bin *.elf trace*
