import numpy as np
import csv

from picoscope import ps3000a

ps = ps3000a.PS3000a()
print(ps.getAllUnitInfo())

print("Setting channel A to DC 5V")
aRange = ps.setChannel(channel="A", coupling="DC", VRange=5)
print("Range of channel A: {}".format(aRange))
print("Setting channel B to DC 1V")
bRange = ps.setChannel(
    channel='B', coupling='DC', VRange=0.2, VOffset=-0.1, enabled=True)
print("Range of channel B: {}".format(bRange))
print("Setting trigger on channel A for 2V")
ps.setSimpleTrigger("A", threshold_V=2)
print()

sample_interval = 6e-9
sample_duration = 10e-3
print("Sampling interval {}s, sample duration {}s".format(
    sample_interval, sample_duration))

actualSamplingInterval, nSamples, maxSamples = ps.setSamplingInterval(
    sample_interval, sample_duration)
print("Sampling interval: {}s".format(actualSamplingInterval))
print("Number of samples: {}".format(nSamples))
print("MaxSamples: {}".format(maxSamples))

print("Starting capture")
ps.runBlock()
ps.waitReady()
print("Capture done")
data = ps.getDataV(channel='B')
print("Data.shape: {}".format(data.shape))
print("All voltage data equal: {}".format(np.all(data == data[0])))
print("Number of unique voltage values: {}".format(len(np.unique(data))))
ps.stop()
ps.close()

with open("data_python.csv", "w+") as csvFile:
    writer = csv.writer(
        csvFile, delimiter=",", quotechar="'", quoting=csv.QUOTE_MINIMAL)
    writer.writerow(data)
