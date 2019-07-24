#!/bin/bash

cat log_$1.txt | rg -v "[^\da-f,]" > filtered_$1.csv
