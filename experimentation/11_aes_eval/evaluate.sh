#!/bin/bash

# test if output directory exists
# if ! [ -d /results ]; then
# 	echo "/results not found, cannot save results"
# 	exit 1
# fi

for i in {1..10}; do
	echo `printf "Compiling binary number %03d" $i`
	make clean
	make

	echo "Evaluating balanced"
	mv balanced.elf program.elf
	./script.exp &
	sleep 1
	gdb-multiarch --batch -q -x balanced.gdb program.elf > `printf "balanced_%03d.log" $i`
	wait

	echo "Evaluating unbalanced"
	mv unbalanced.elf program.elf
	./script.exp &
	sleep 1
	gdb-multiarch --batch -q -x unbalanced.gdb program.elf > `printf "unbalanced_%03d.log" $i`
	wait
done

tar czf /dual-rail/output.tar.gz plaintexts.txt *.log