#!/bin/bash

for i in {1..3}; do
	echo `printf "Compiling binary number %03d" $i`
	make clean
	make

	mv balanced.elf program.elf
	./script.exp &
	sleep 1
	gdb-multiarch --batch -q -x debug.gdb program.elf > `printf "balanced_%03d.log" $i`
	wait

	mv unbalanced.elf program.elf
	./script.exp &
	sleep 1
	gdb-multiarch --batch -q -x debug.gdb program.elf > `printf "unbalanced_%03d.log" $i`
	wait
done

tar czf plaintexts.txt *.log /output.tar.gz