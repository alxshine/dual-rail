import numpy as np
import sys

try:
    filename = sys.argv[1]
except IndexError:
    filename = "unbalanced.npy"

def popcount(x):
    return bin(x).count('1')

try:
    traces = np.load(filename)
except IOError:
    print("Could not find file {}".format(filename))

plaintexts = np.array([0xf,0x1]*(traces.shape[0]/2))
candidates = range(1<<4)
hypopowcons = np.zeros((len(plaintexts), len(candidates)))
for i in range(len(plaintexts)):
    for j in range(len(candidates)):
        hypopowcons[i,j] = popcount(plaintexts[i]^candidates[j])

print(hypopowcons.shape)
