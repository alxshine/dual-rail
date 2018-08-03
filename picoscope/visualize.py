import numpy as np
import matplotlib.pyplot as plt
import sys

try:
    filename = sys.argv[1]
except IndexError:
    filename = "16_ptxts_2018-08-03.npy"

print("Loading {}".format(filename))
data = np.load(filename)
print("Data.shape: {}".format(data.shape))
for row in data:
    plt.plot(row)
plt.show()
