#!/usr/bin/python2

import numpy as np
import sys
import matplotlib.pyplot as plt

path = "run_{:02}.npy"
start_index = 25
end_index = 75

try:
    index = int(sys.arv[1])
except Exception:
    index = 0

data = np.load(path.format(index))

evens = data[start_index:end_index:2]
odds = data[start_index+1:end_index:2]

evens_mean = evens.mean(axis=0)
odds_mean = odds.mean(axis=0)

plt.figure()
plt.subplot(211)
plt.plot(evens_mean)
plt.plot(odds_mean)

plt.subplot(212)
plt.plot(evens_mean - odds_mean)

plt.show()
