#!/bin/zsh

for i in {1..10}; do
	echo `printf "Compiling binary number %03d" $i`
	make clean
	make
	b_name=`printf "binaries/balanced_%03d.elf" $i`
	mv "balanced.elf" ${b_name}
	u_name=`printf "binaries/unbalanced_%03d.elf" $i`
	mv "unbalanced.elf" ${u_name}
done
