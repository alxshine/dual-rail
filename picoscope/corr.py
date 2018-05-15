import numpy as np
import matplotlib.pyplot as plt
import sys

try:
    filename = sys.argv[1]
except IndexError:
    filename = "reference.npy"

def popcount(x):
    return bin(x).count('1')

try:
    corrs = np.load('corrs.npy')
except IOError:
    try:
        traces = np.load(filename)
    except IOError:
        print("Could not find file {}".format(filename))
        sys.exit(1)

    plaintexts = np.repeat([0xf,0x1],(traces.shape[0]/2))
    candidates = range(1<<4)
    hypopowcons = np.zeros((len(plaintexts), len(candidates)))
    for i in range(len(plaintexts)):
        for j in range(len(candidates)):
            hypopowcons[i,j] = popcount(plaintexts[i]^candidates[j])

    corrs = np.zeros((len(candidates), traces.shape[1]))
    for i in candidates:
        print("candidate {}".format(i))
        for j in range(traces.shape[1]):
            print("row {}\r".format(j+1), end='')
            corrs[i,j]  = (np.corrcoef(traces[:,j], hypopowcons[:,i]))[0,1]
        print()

    np.save('corrs.npy', corrs)

print(corrs.shape)
plt.figure()
plt.plot(corrs[0])
plt.show()
