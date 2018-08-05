import numpy as np
import sys
import matplotlib.pyplot as plt

specialLut = (
    0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F,
    0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF
)

tracefile = sys.argv[1]
ptxtfile = sys.argv[2]

traces = np.load(tracefile)
ptxts = np.load(ptxtfile)

key = 1
start_sample = 200
end_sample = 3000

print(traces[0])
traces = traces[:, start_sample:end_sample]
plt.scatter(range(end_sample-start_sample), traces[1])
plt.show()
