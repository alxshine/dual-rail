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
ps.setChannel(channel="B", coupling="DC", VRange=1)
print("Setting trigger on channel A for 2V")
ps.setSimpleTrigger("A", threshold_V=2)
print()

num_plaintexts = 16
captures_per_plaintext = 100
n_captures = num_plaintexts * captures_per_plaintext
print("Capturing {} plaintexts {} times each, resulting in {} traces total".format(num_plaintexts, captures_per_plaintext, n_captures))
sample_interval = 10e-9 #10ns sampling interval
sample_duration = 100e-6
print("Sampling interval {}ns, sample duration {}ms".format(sample_interval*1e9, sample_duration*1e6))

ps.setSamplingInterval(sample_interval, sample_duration)

samples_per_segment = ps.memorySegments(n_captures)
ps.setNoOfCaptures(n_captures)

print("Starting block capture")
ps.runBlock()
ps.waitReady()
print("Block capture done")
data, numSamplesReturned, _ = ps.getDataRawBulk(channel='B')
print("{} samples returned".format(numSamplesReturned))
print("Data.shape: {}".format(data.shape))
print("All voltage data equal: {}".format(np.all(data == data[0][0])))
ps.stop()
filename = "traces-{}_ptxts_{}.npy".format(num_plaintexts, datestring)
print("Saving to {}".format(filename))
np.save(filename, data)

print("Generating plaintext file")
plaintexts = np.arange(16)
plaintexts = np.tile(plaintexts, captures_per_plaintext)
np.save("plaintexts-{}_ptxts_{}.npy".format(num_plaintexts, datestring), plaintexts)
