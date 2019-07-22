# coding: utf-8
import numpy as np
import csv

exec_file = open('exec_logs.csv')
execs = [r for r in csv.reader(exec_file)]
execs = np.array([r[-(min_len-50):-1] for r in execs])

trace_file = open('traces.csv')
t = [r for r in csv.reader(trace_file)]
traces = np.array([r[-e.shape[1]:] for r in t]).astype(np.int)
a = traces[0]
b = traces[1]
diff = a-b
ea = execs[0]
eb = execs[1]
