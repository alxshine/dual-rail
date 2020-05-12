#!/bin/bash

if [ -z $1 ]; then
	echo "Usage: $0 binary"
fi

qemu-system-arm -M versatilepb -m 256 -cpu arm1176 -nographic -S -s -kernel $1
