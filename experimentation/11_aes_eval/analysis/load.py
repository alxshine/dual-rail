# coding: utf-8
import numpy as np
import matplotlib.pyplot as plt

def hamming_weight(v):
    ret = 0
    for i in range(32):
        ret += v&1
        v >>= 1
    return ret
hw = np.vectorize(hamming_weight)

t1 = np.load('reworked_001.npy')
t2 = np.load('reworked_002.npy')
ut1 = np.load('u_reworked_001.npy')
ut2 = np.load('u_reworked_002.npy')
dm = t1 != t2
s1 = t1[dm]
s2 = t2[dm]
hw1 = hw(s1)
hw2 = hw(s2)
diff = hw1-hw2

udm = ut1 != ut2
us1 = ut1[udm]
us2 = ut2[udm]
uhw1 = hw(us1)
uhw2 = hw(us2)
udiff = uhw1 -uhw2
