import numpy as np

execs = np.genfromtxt('exec_logs.csv', delimiter=',')[:,:-1]
np.save('execs_unbalanced.npy', execs)
traces = np.genfromtxt('traces.csv', delimiter=',').astype(np.int)
np.save('traces_unbalanced.npy', traces)
