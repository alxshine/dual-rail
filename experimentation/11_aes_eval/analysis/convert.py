# coding: utf-8
import numpy as np
import csv

for i in range(3,4):
    print('working on {:03}'.format(i))
    f = open('filtered_{:03}.csv'.format(i))
    trace = []
    last_row = None
    for r in csv.reader(f):
        current_vals = np.array([int(v, 16) for v in r])
        if last_row is not None:
            diffs = current_vals != last_row
            if diffs.sum() == 1:
                trace.append(current_vals[diffs][0])
            else:
                trace.append(0)
        last_row = current_vals

    np_trace = np.array(trace)
    np.save('reworked_{:03}.npy'.format(i), np_trace)

"""    uf = open('u_filtered_{:03}.csv'.format(i))
    trace = []
    last_row = None
    for r in csv.reader(uf):
        current_vals = np.array([int(v, 16) for v in r])
        if last_row is not None:
            diffs = current_vals != last_row
            if diffs.sum() == 1:
                trace.append(current_vals[diffs][0])
            else:
                trace.append(0)
        last_row = current_vals

    np_trace = np.array(trace)
    np.save('u_reworked_{:03}.npy'.format(i), np_trace)
    """
