# coding: utf-8
import numpy as np
ts = [np.load('reworked_{:03}.npy'.format(i)) for i in range(1,4)]

min_len = min([t.shape[0] for t in ts])
d1 = ts[0][:min_len] - ts[1][:min_len]
d2 = ts[0][:min_len] - ts[2][:min_len]
