#!/bin/bash

cat log_$1.txt | rg -v "[^\da-f,]" | tail -n +2 > filtered_$1.csv
#cat ulog_$1.txt | rg -v "[^\da-f,]" | tail -n +2 > u_filtered_$1.csv
