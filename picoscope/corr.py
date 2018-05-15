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
    print("Trying to load correlation file")
    corrs = np.load("corr_{}".format(filename))
except IOError:
    print("Not found, generating one")
    try:
        print("Loading traces")
        traces = np.load(filename)
    except IOError:
        print("Could not find file {}".format(filename))
        sys.exit(1)

    pt_range = range(1<<8)
    plaintexts = np.repeat(pt_range,(traces.shape[0]/len(pt_range)+1))[:traces.shape[0]]
    print(plaintexts.shape)
    candidates = range(1<<8)
    hypopowcons = np.zeros((len(plaintexts), len(candidates)))
    print("Generating hypothetical power consumptions")
    for i in range(len(plaintexts)):
        for j in range(len(candidates)):
            hypopowcons[i,j] = popcount(plaintexts[i]^candidates[j])

    corrs = np.zeros((len(candidates), traces.shape[1]))
    print("Generating correlation coefficients")
    for i in candidates:
        print("candidate {}".format(i))
        for j in range(traces.shape[1]):
            print("row {}\r".format(j+1), end='')
            corrs[i,j]  = (np.corrcoef(traces[:,j], hypopowcons[:,i]))[0,1]
        print()

    np.save("corr_{}".format(filename), corrs)

print(corrs.shape)
peaks = corrs.max(axis=1)
print(peaks.shape)
print("Most probable key: {}".format(peaks.argmax()))
plt.figure()
plt.plot(peaks)
plt.show()
