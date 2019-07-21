CROSS_COMPILE ?= arm-none-eabi
CLANGOPTS = -target arm-none-eabi -mcpu=arm926ej-s -O0

PLUGINS=$(wildcard ../../passes/build/*.so)
PASSES=-insert

C0=$$(( $$RANDOM % 256))
C1=$$(( $$RANDOM % 256))
C2=$$(( $$RANDOM % 256))
C3=$$(( $$RANDOM % 256))
C4=$$(( $$RANDOM % 256))
C5=$$(( $$RANDOM % 256))
C6=$$(( $$RANDOM % 256))
C7=$$(( $$RANDOM % 256))
C8=$$(( $$RANDOM % 256))
C9=$$(( $$RANDOM % 256))
C10=$$(( $$RANDOM % 256))
C11=$$(( $$RANDOM % 256))
C12=$$(( $$RANDOM % 256))
C13=$$(( $$RANDOM % 256))
C14=$$(( $$RANDOM % 256))
C15=$$(( $$RANDOM % 256))
DEFINES=-DC0=${C0} -DC1=${C1} -DC2=${C2} -DC3=${C3} -DC4=${C4} -DC5=${C5} -DC6=${C6} -DC7=${C7} -DC8=${C8} -DC9=${C9} -DC10=${C10} -DC11=${C11} -DC12=${C12} -DC13=${C13} -DC14=${C14} -DC15=${C15}

all: balanced unbalanced_target

balanced: balanced.elf

unbalanced_target: unbalanced.elf

optimized.S: tinyAES.ll rtlib.ll program.ll
	llvm-link tinyAES.ll rtlib.ll program.ll -S -o linked.ll
	opt -load="$(PLUGINS)" $(PASSES) linked.ll -S -o optimized.ll
	llc optimized.ll -o optimized.S

unbalanced.S: tinyAES.ll program.ll
	llvm-link tinyAES.ll program.ll -S -o u_linked.ll
	opt u_linked.ll -S -o u_optimized.ll
	llc u_optimized.ll -o unbalanced.S

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
