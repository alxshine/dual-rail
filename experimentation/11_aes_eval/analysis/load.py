# coding: utf-8
import numpy as np
import matplotlib.pyplot as plt
import csv

from boundaries import *
from uboundaries import *

def hamming_weight(v):
    ret = 0
    for i in range(32):
        ret += v&1
        v >>= 1
    return ret
hw = np.vectorize(hamming_weight)

t1 = np.load('reworked_001.npy')
t2 = np.load('reworked_002.npy')
h1 = hw(t1)
h2 = hw(t2)
diff = h1-h2

ut1 = np.load('u_reworked_001.npy')
ut2 = np.load('u_reworked_002.npy')
uh1 = hw(ut1)
uh2 = hw(ut2)
udiff = uh1-uh2

pc_trace = []
pc_file = open('pc.log')
for row in csv.reader(pc_file):
    pc_trace.append(int(row[0]))
pt = np.array(pc_trace)

upc_trace = []
upc_file = open('upc.log')
for row in csv.reader(upc_file):
    upc_trace.append(int(row[0]))
upt = np.array(upc_trace)
