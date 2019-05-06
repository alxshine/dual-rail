import numpy as np

wordsize = 8
word_max = 1<<wordsize
word_filter = word_max - 1
full_filter = (1<<4*wordsize) - 1
scheme1_filter = 0x00ff00ff
scheme2_filter = 0xff0000ff

def bit_not(n, numbits = wordsize):
    return (1 << numbits) - 1 - n

def hammingWeight(val):
    weight = 0
    for i in range(4*wordsize):
        mask = 1<<i
        current_bit = val & mask
        weight += current_bit >> i
    return weight

vHW = np.vectorize(hammingWeight)

def cycle_left(x, i=1, total_size = 4*wordsize):
    for i in range(i):
        dropping_bit = x & (1<<total_size-1)
        dropping_bit >>= total_size - 1
        x <<= 1
        x |= dropping_bit
    bit_filter = (1<<total_size) - 1
    x &= bit_filter
    return x

def cycle_right(x, i=1, total_size = 4*wordsize):
    for i in range(i):
        dropping_bit = x & 1
        x >>= 1
        x |= dropping_bit << total_size -1
    filter = (1<<total_size) - 1
    x &= filter
    return x

def bit_sub(x, y):
    r = x + bit_not(y) + 1
    return r & full_filter

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

def unbalanceScheme1(x):
    return x & word_filter

vUS1 = np.vectorize(unbalanceScheme1)
