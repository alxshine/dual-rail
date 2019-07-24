set logging on
set log file trace_debug.csv

target remote localhost:1234
break balanced_c_entry 
c

while (1)
printf "%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x\n", $r0, $r1, $r2, $r3, $r4, $r5, $r6, $r7, $r8, $r9, $r10, $r11, $r12
step
end

