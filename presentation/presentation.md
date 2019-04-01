<!--# Status Talk-->
## Towards Balancing Arbitrary Code

---

## Overview
- Power Analysis Attacks
- Power Analysis Defenses
- Project
- Current Status
- Next Steps

---

## Power Analysis Attacks

NOTE: Who was in Infosec2 or Network Security

----

![](./images/poweranalysis.png)
<span style="font-size:12pt;">Network Security: Slideset 2, Devices</span>

----

![](./images/trace.png)
<span style="font-size:12pt;">Network Security Homework</span>

----

## Statistical Attacks

----

### Requirements
- Power consumption has connection to data
- Data has known link to secret

---

## Power Analysis Defenses

- Masking
- Dual-Rail Logic

----

### Dual-Rail Logic
- Calculate inverse as well
- Power consumption is constant

----

![](./images/dual.png)

---

## Project

----

### Outline
- Find balanced operation alternatives
- Transform in LLVM compiler
- Evaluate Using QEMU

---

### Balanced Arithmetic

----

`0 | 0 | 0 | x`

----

`0 | ~x | 0 | x`

----

#### X ORR Y

```
        0 |        ~X |       0 |       X
        0 |        ~Y |       0 |       Y
        0 | ~X ORR ~Y |       0 | X ORR Y
        0 | ~X AND ~Y |       0 | X AND Y
~X AND ~Y | ~X ORR ~Y | X AND Y | X ORR Y
~X AND ~Y |         0 |       0 | X ORR Y
```

---

## LLVM PASS

----

### LLVM
![](./images/llvm.png)

----

```
clang -target arm-none-eabi -mcpu=arm926ej-s -O0 -S -emit-llvm program.c -o program.ll
clang -target arm-none-eabi -mcpu=arm926ej-s -O0 -S -emit-llvm tinyAES.c -o tinyAES.ll
arm-none-eabi-as -ggdb  startup.s -o startup.o
clang -target arm-none-eabi -mcpu=arm926ej-s -O0 rtlib.c -S -emit-llvm -o rtlib.ll
llc rtlib.ll -o rtlib.S
opt -load="../../passes/build/libPasses.so" -insert tinyAES.ll -S -o aes_optimized.ll
opt -load="../../passes/build/libPasses.so" -insert program.ll -S -o optimized.ll
arm-none-eabi-as -ggdb  rtlib.S -o rtlib.o
llc aes_optimized.ll -o aes_optimized.S
llc optimized.ll -o optimized.S
arm-none-eabi-as -ggdb  optimized.S -o program.o
arm-none-eabi-as -ggdb  aes_optimized.S -o tinyAES.o
arm-none-eabi-ld -T startup.ld program.o tinyAES.o startup.o rtlib.o -o program.elf
arm-none-eabi-objcopy -O binary program.elf program.bin
```

---

## Evaluation

---

## Current Status

----

#### What is done?
- 8bit arithmetic
- QEMU evaluation
- LLVM toolchain

----

#### Preliminary evaluation

![](./images/eval.png)

---

## Next steps
- Actual balancing pass for 8bit arithmetic
- Extend arithmetic to arbitrary size
- Better performance for multiply, divide, ...
- Think about floats, possibly?
