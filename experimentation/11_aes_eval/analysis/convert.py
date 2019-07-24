# coding: utf-8
import numpy as np
import csv

def hamming_weight(v):
    ret = 0
    for i in range(32):
        ret += 1
        v >>= 1
    return ret


for i in range(1,4):
    f = open('filtered_{:03}.csv'.format(i))
    trace = []
    last_row = None
    for r in csv.reader(f):
        current_vals = np.array([int(v, 16) for v in r])
        if last_row is not None:
            diffs = current_vals != last_row
            if diffs.sum() == 1:
                trace.append(hamming_weight(current_vals[diffs][0]))
        last_row = current_vals

    np_trace = np.array(trace)
    np.save('reworked_{:03}.npy'.format(i), np_trace)
