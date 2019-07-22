import numpy as np
import matplotlib.pyplot as plt

traces_balanced = np.load('traces_balanced.npy')
execs_balanced = np.load('execs_balanced.npy')

traces_unbalanced = np.load('traces_unbalanced.npy')
execs_unbalanced = np.load('execs_unbalanced.npy')

# coding: utf-8
a = traces_balanced[0]
b = traces_balanced[1]
ea = execs_balanced[0]
eb = execs_balanced[1]
