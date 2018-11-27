CROSS_COMPILE ?= arm-none-eabi

CPU = -mcpu=arm926ej-s
COPTS = -Wall -Werror -std=gnu99

all: test.bin

test.bin: test.elf
	$(CROSS_COMPILE)-objcopy -O binary test.elf test.bin

test.elf: test.o test.ld startup.o
	$(CROSS_COMPILE)-ld -T test.ld test.o startup.o -o test.elf

test.o: test.c
	$(CROSS_COMPILE)-gcc -c $(CPU) $(COPTS) test.c -o test.o

startup.o: startup.s
	$(CROSS_COMPILE)-as $(CPU) startup.s -o startup.o

run: test.bin
	qemu-system-arm -M versatilepb -m 128M -nographic -kernel test.bin
