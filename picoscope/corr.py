import numpy as np
import matplotlib.pyplot as plt
import sys
from sbox import Sbox
from os.path import join
from multiprocessing import Pool


def popcount(x):
    ret = 0
    while x > 0:
        ret += x & 1
        x >>= 1
    return ret


try:
    folderName = sys.argv[1]
except IndexError:
    folderName = "reference"

try:
    print(f"Trying to load correlation file")
    corrs = np.load(join(folderName, "corrs.npy"))
    print("Success, using those values")
except IOError:
    print("Not found, generating one")
    try:
        print("Loading traces")
        traceFileName = join(folderName, "traces.npy")
        traces = np.load(traceFileName).transpose()
        num_samples = traces.shape[0]
    except IOError:
        print("Could not find file {}".format(traceFileName))
        sys.exit(1)

    try:
        print("Loading plaintexts")
        ptxtName = join(folderName, "plaintexts.npy")
        ptxts = np.load(ptxtName)
    except IOError:
        print("Could not find file {}".format(ptxtName))
        sys.exit(1)

    num_bytes = 4
    num_candidates = 255
    candidates = range(num_candidates)
    num_traces = traces.shape[0]

    try:
        print("Loading power consumptions")
        powconName = join(folderName, "hypoPowCons.npy")
        hypopowcons = np.load(powconName).transpose((1, 2, 0))
    except IOError:
        print("Could not find {}, generating".format(powconName))

        # hypothetical power consumptions of all traces per key candidate
        hypopowcons = np.empty((num_traces, num_bytes, num_candidates))
        for t in range(num_traces):
            for b in range(num_bytes):
                for c in candidates:
                    hypopowcons[t, b, c] = popcount(Sbox[c ^ int(ptxts[t, b])])
        print("...Done, saving at {}".format(powconName))
        np.save(powconName, hypopowcons)
        hypopowcons = hypopowcons.transpose((1, 2, 0))

    # calculate correlation between the hypopowcons for
    # a candidate with all points in the traces
    corrs = np.zeros((num_bytes, num_candidates, num_samples))
    for b in range(num_bytes):
        print("Byte {}".format(b))
        for c in candidates:
            for j in range(num_samples):
                corrs[b, c, j] = np.corrcoef(hypopowcons[b, c, :],
                                             traces[j])[0, 1]

    np.save(join(folderName, "corrs.npy"), corrs)

for b in range(num_bytes):
    print(f"Points of maximum correlation: {corrs.argmax(axis=1)}")
    print(f"Maximum correlation value: {corrs.max(axis=1)}")
