# coding: utf-8
import numpy as np
import matplotlib.pyplot as plt
import csv

def hamming_weight(v):
    ret = 0
    for i in range(32):
        ret += v&1
        v >>= 1
    return ret
hw = np.vectorize(hamming_weight)

t1 = np.load('reworked_001.npy')
t2 = np.load('reworked_002.npy')
#ut1 = np.load('u_reworked_001.npy')
#ut2 = np.load('u_reworked_002.npy')
#dm = t1 != t2
#hw1 = hw(t1)
#hw2 = hw(t2)
#diff = hw1-hw2
#hist,_ = np.histogram(diff, range(33))
#hist = hist.astype(float)
#hist /= hist.sum()

#udm = ut1 != ut2
#uhw1 = hw(ut1)
#uhw2 = hw(ut2)
#udiff = uhw1 -uhw2
#uhist,_ = np.histogram(udiff, range(33))
#uhist = uhist.astype(float)
#uhist /= uhist.sum()

pc_trace = []
pc_file = open('pc.log')
for row in csv.reader(pc_file):
    pc_trace.append(int(row[0]))
pt = np.array(pc_trace)

#upc_trace = []
#upc_file = open('upc.log')
#for row in csv.reader(upc_file):
#    upc_trace.append(int(row[0]))
#upt = np.array(upc_trace)
