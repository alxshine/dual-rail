import numpy as np
import matplotlib.pyplot as plt
from util import *

class Operation:
    def __init__(self, v1, v2, function):
        self.v1 = v1
        self.v2 = v2
        self.function = function

class MultiStepOperation:
    """
    This will store intermediate results computed by the different ops.
    By convention the inputs will be stored in results[0] and results[1], and filled with all possible values.
    """
    
    def __init__(self, ops):
        self.ops = ops
        self.results = np.zeros((len(ops)+2, word_max**2), dtype=int)
        for i in range(word_max):
            v = i << 3*wordsize | bit_not(i)
            self.results[0, i] = v
            self.results[1, i] = v

    def numOps(self):
        return len(self.ops)

    def execute(self):
        for opIndex in range(len(self.ops)):
            op = self.ops[opIndex]
            resultIndex = opIndex + 2
            for i in range(word_max):
                for j in range(word_max):
                    if(op.v1) == 0:
                        lhs = self.results[0, i]
                    elif(op.v1) == 1:
                        lhs = self.results[1, j]
                    else:
                        lhs = self.results[op.v1, i*word_max+j]

                    if(op.v2) == 0:
                        rhs = self.results[0, i]
                    elif(op.v2) == 1:
                        rhs = self.results[1, j]
                    else:
                        rhs = self.results[op.v2, i*word_max+j]

                    self.results[resultIndex, i*word_max+j] = op.function(lhs, rhs)

    def getFinalResults(self):
        return self.results[-1]

vHW = np.vectorize(hammingWeight)

o = Operation(0,1,lambda x,y: x|y)
m = MultiStepOperation([o])
m.execute()
weights = vHW(m.getFinalResults())
plt.hist(weights, bins=range(2*wordsize+2))
plt.show()
