import numpy as np
import csv

numTraces = 1466
numBytes = 16
numTracePoints = 17500

# extract traces
print("Extracting traces")
traces = np.empty((numTraces, numTracePoints))
with open('traces.csv') as tracesFile:
    tracesReader = csv.reader(tracesFile, delimiter=',')
    i = -2
    for row in tracesReader:
        i += 1
        print(f"Row {i}\r", end='')
        if i < 0:
            continue
        converted = list(map(lambda x: int(x), row[1:]))
        traces[i] = np.array((converted))

np.save("traces.npy", traces)
print("\nDone")

print("Extracting plaintexts")
plaintexts = np.empty((numTraces, numBytes))
with open('plaintexts.csv') as ptxtFile:
    ptxtReader = csv.reader(ptxtFile, delimiter=',')
    i = -2
    for row in ptxtReader:
        i += 1
        print(f"Row {i}\r", end='')
        if i < 0:
            continue
        converted = list(map(lambda x: int(x), row[1:]))
        plaintexts[i] = np.array((converted))

np.save("plaintexts.npy", plaintexts)
print("\nDone")
