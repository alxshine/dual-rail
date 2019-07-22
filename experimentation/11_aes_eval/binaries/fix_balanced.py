import numpy as np
import csv

exec_file = open('exec_logs.csv')
e = [r for r in csv.reader(exec_file)]
[len(r) for r in e]
for r in e:
    if len(r) == 2395959:
        del(r[43])
execs = np.array(e)[:,:-1]
execs.shape
np.save('execs_balanced.npy', execs)

trace_file = open('traces.csv')
t = [r for r in csv.reader(trace_file)]
for r in t:
   if len(r) == 2395958:
      del(r[43])
traces = np.array(t).astype(np.int)
np.save('traces_balanced.npy', traces)
