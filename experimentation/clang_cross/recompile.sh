#!/bin/sh

arm-none-eabi-gcc -c -mcpu=arm926ej-s -Wall -Werror -std=gnu99 -ggdb program.c -o program.o
arm-none-eabi-ld -T startup.ld program.o startup.o -o program.elf
arm-none-eabi-objcopy -O binary program.elf program.bin 
