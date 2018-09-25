import matplotlib.pyplot as plt
import numpy as np
import time
import datetime

from picoscope import ps3000a

ps = ps3000a.PS3000a()
print(ps.getAllUnitInfo())
datestring = datetime.datetime.today().strftime("%Y-%m-%d")

print("Setting channel A to DC 5V")
ps.setChannel(channel="A", coupling="DC", VRange=5)
print("Setting channel B to DC 1V")
ps.setChannel(channel="B", coupling="DC", VRange=0.2, VOffset=0.1)
print("Setting trigger on channel A for 2V")
ps.setSimpleTrigger("A", threshold_V=2)
print()

num_plaintexts = 16
captures_per_plaintext = 100
n_captures = num_plaintexts * captures_per_plaintext
print("Capturing {} plaintexts {} times each, resulting in {} traces total".format(num_plaintexts, captures_per_plaintext, n_captures))
sample_interval = 100e-9
sample_duration = 15e-3
print("Sampling interval {}s, sample duration {}s".format(sample_interval, sample_duration))

actualSamplingInterval, nSamples, maxSamples = ps.setSamplingInterval(sample_interval, sample_duration)
print("Sampling interval: {}s".format(actualSamplingInterval))
print("Number of samples: {}".format(nSamples))
print("MaxSamples: {}".format(maxSamples))

data = np.empty((n_captures, nSamples))

print("Starting capture")
for i in range(n_captures):
    ps.runBlock()
    ps.waitReady()
    data[i] = ps.getDataV(channel='B')
print("Capture done")
ps.stop()
filename = "traces-{}_ptxts_{}.npy".format(num_plaintexts, datestring)
print("Saving to {}".format(filename))
np.save(filename, data)

print("Generating plaintext file")
plaintexts = np.arange(16)
plaintexts = np.tile(plaintexts, captures_per_plaintext)
np.save("plaintexts-{}_ptxts_{}.npy".format(num_plaintexts, datestring), plaintexts)
