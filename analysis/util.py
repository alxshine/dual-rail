import numpy as np

wordsize = 8
word_max = 1<<8

def bit_not(n, numbits = wordsize):
    return (1 << numbits) - 1 - n

def hammingWeight(val):
    weight = 0
    while val != 0:
        weight += val & 1
        val >>= 1
    return weight

def cycle_left(x, i=1):
    for i in range(i):
        dropping_bit = x & (1<<wordsize-1)
        x <<= 1
        x |= dropping_bit >> wordsize-1
    filter = (2<<wordsize) -1
    x &= filter
    return x

def cycle_right(x, i=1):
    for i in range(i):
        dropping_bit = x & 1
        x >>= 1
        x |= dropping_bit << wordsize -1
    filter = (2<<wordsize) - 1
    x &= filter
    return x

def getWeightDistributionUnbalanced(operation):
    weights = np.zeros((wordsize+1))
    for v1 in range(1<<wordsize):
        for v2 in range(1<<wordsize):
            w = hammingWeight(operation(v1, v2))
            weights[w] += 1
        
    return weights

def getWeightDistributionBalanced(operation):
    weights = np.zeros((2*wordsize + 2))
    for v1 in range(1<<wordsize):
        x1 = v1 << 3*wordsize | bit_not(v1)
        for v2 in range(1<<wordsize):
            x2 = v2 << 3*wordsize | bit_not(v2)
            w = hammingWeight(operation(x1, x2))
            weights[w] += 1
    return weights
