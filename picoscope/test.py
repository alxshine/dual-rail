import numpy as np
import matplotlib.pyplot as plt
import sys

try:
    filename = sys.arv[1]
except Exception:
    filename = "run_01.npy"

data = np.load(filename)

evens = data[::2]
odds = data[1::2]

plt.figure()
plt.plot(evens.mean(axis=0) - odds.mean(axis=0))
plt.show()
