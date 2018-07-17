import matplotlib.pyplot as plt
import numpy as np
import time

from picoscope import ps3000a

ps = ps3000a.PS3000a()

# now = time.strftime("%Y%m%d_%H%M%S")
# filename = "sweep_" + now + ".swp"
# output_file = open(filename, "wb")

c = 3e8

# rapid block mode

ps.setChannel(channel="A", coupling="DC", VRange=1)
ps.setChannel(channel="B", coupling="DC", VRange=0.5)

n_captures = 1000
sample_interval = 10e-9 #10ns sampling interval
sample_duration = 50e-6

ps.setSamplingInterval(sample_interval, sample_duration)
ps.setSimpleTrigger("A", threshold_V=0.2)

samples_per_segment = ps.memorySegments(n_captures)
ps.setNoOfCaptures(n_captures)

ps.runBlock()
ps.waitReady()
data, _, _ = ps.getDataRawBulk(channel='B')
print(data.shape)
for row in data:
    plt.plot(row)
plt.show()

# num_captures = 10
# num_samples = 1000
# data = np.zeros((num_captures, num_samples))
# for i in range(num_captures):
    # ps.runBlock()
    # ps.waitReady()

    # data[i] = ps.getDataV('B', numSamples=num_samples)
    # plt.plot(data[i])

# for i in range(n_captures):
#     ps._lowLevelSetDataBuffer(ps.CHANNELS["A"],
#         data[i, :], 0, i)

# # t2 = time.time()
# nsamples = c_int32(ps.noSamples)
# from_segment_index = 0
# to_segment_index = n_captures - 1
# downsample_ratio = 0
# downsample_mode = 0
# overflow = np.zeros(n_captures, dtype=np.int16)
# overflow_ptr = overflow.ctypes.data_as(POINTER(c_int16))

# m = ps.lib.ps3000aGetValuesBulk(c_int16(ps.handle),
#         byref(nsamples),
#         c_int16(from_segment_index),
#         c_int16(to_segment_index),
#         c_int32(downsample_ratio),
#         c_int16(downsample_mode),
#         overflow_ptr)
# print m

# ps.checkResult(m)

# output_file.write(data)
# t4 = time.time()
# print "Time to write data to disk: ", str(t4 - t3)
# output_file.close()

plt.show()

ps.close()

