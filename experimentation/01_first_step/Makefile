CROSS_COMPILE ?= arm-none-eabi

CPU = -mcpu=arm926ej-s
COPTS = -Wall -Werror -std=gnu99 -ggdb -O0

all: program.bin

%.bin: %.elf
	$(CROSS_COMPILE)-objcopy -O binary $< $@

%.elf: %.o startup.ld startup.o
	$(CROSS_COMPILE)-ld -T startup.ld $< startup.o -o $@

%.o: %.c
	$(CROSS_COMPILE)-gcc -c $(CPU) $(COPTS) $< -o $@
	$(CROSS_COMPILE)-gcc -c -S $(CPU) $(COPTS) $< -o $<.s

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

run: program.bin
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel program.bin

.PHONY: clean
clean:
	rm *.o *.bin *.elf trace*
