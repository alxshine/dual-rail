CROSS_COMPILE ?= arm-none-eabi
CLANGOPTS = -target arm-none-eabi -mcpu=arm926ej-s -O0

PLUGINS=$(wildcard ../../passes/build/*.so)
PASSES=-insert

C0=$(shell echo $$(($$RANDOM % 128 + 128)))
C1=$(shell echo $$(($$RANDOM % 128 + 128)))
C2=$(shell echo $$(($$RANDOM % 128 + 128)))
C3=$(shell echo $$(($$RANDOM % 128 + 128)))
C4=$(shell echo $$(($$RANDOM % 128 + 128)))
C5=$(shell echo $$(($$RANDOM % 128 + 128)))
C6=$(shell echo $$(($$RANDOM % 128 + 128)))
C7=$(shell echo $$(($$RANDOM % 128 + 128)))
C8=$(shell echo $$(($$RANDOM % 128 + 128)))
C9=$(shell echo $$(($$RANDOM % 128 + 128)))
C10=$(shell echo $$(($$RANDOM % 128 + 128)))
C11=$(shell echo $$(($$RANDOM % 128 + 128)))
C12=$(shell echo $$(($$RANDOM % 128 + 128)))
C13=$(shell echo $$(($$RANDOM % 128 + 128)))
C14=$(shell echo $$(($$RANDOM % 128 + 128)))
C15=$(shell echo $$(($$RANDOM % 128 + 128)))
DEFINES=-DC0=${C0} -DC1=${C1} -DC2=${C2} -DC3=${C3} -DC4=${C4} -DC5=${C5} -DC6=${C6} -DC7=${C7} -DC8=${C8} -DC9=${C9} -DC10=${C10} -DC11=${C11} -DC12=${C12} -DC13=${C13} -DC14=${C14} -DC15=${C15}

all: balanced unbalanced_target dump_plaintext

balanced: balanced.elf

unbalanced_target: unbalanced.elf

dump_plaintext:
	echo ${C0},${C1},${C2},${C3},${C4},${C5},${C6},${C7},${C8},${C9},${C10},${C11},${C12},${C13},${C14},${C15} >> plaintexts.txt

optimized.S: tinyAES.ll rtlib.ll program.ll
	llvm-link tinyAES.ll rtlib.ll program.ll -S -o linked.ll
	opt -load="$(PLUGINS)" $(PASSES) -debug-pass=Arguments linked.ll -S -o optimized.ll
	llc -O0 optimized.ll -o optimized.S

unbalanced.S: tinyAES.ll program.ll
	llvm-link tinyAES.ll program.ll -S -o u_linked.ll
	opt u_linked.ll -S -o u_optimized.ll
	llc -O0 u_optimized.ll -o unbalanced.S

optimized.o: optimized.S
	$(CROSS_COMPILE)-as -ggdb $(CPU) optimized.S -o optimized.o

unbalanced.o: unbalanced.S
	$(CROSS_COMPILE)-as -ggdb $(CPU) unbalanced.S -o unbalanced.o

%.ll: %.c
	clang $(CLANGOPTS) $< -S -emit-llvm ${DEFINES} -o $@

startup.o: startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) startup.s -o startup.o

u_startup.o: u_startup.s
	$(CROSS_COMPILE)-as -ggdb $(CPU) u_startup.s -o u_startup.o

unbalanced.elf: u_startup.o u_startup.ld unbalanced.o
	$(CROSS_COMPILE)-ld -T u_startup.ld u_startup.o unbalanced.o -o unbalanced.elf

balanced.elf: startup.o startup.ld optimized.o
	$(CROSS_COMPILE)-ld -T startup.ld startup.o optimized.o -o balanced.elf

.PHONY: clean
clean:
	rm -f *.o *.bin *.elf *.ll optimized.S
test:
