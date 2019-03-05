from multiop import *

m = MultiStepOperation([
    BinaryOperation(0, 1, lambda x,y: bit_sub(x,y)), #2
    BinaryOperation(0, 1, lambda x,y: x + cycle_right(y, 2*wordsize)), #3
    BinaryOperation(2, 3, lambda x,y: x | (y>>wordsize)), #4
    UnaryOperation(4, lambda x: x & scheme2_filter), #5
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x-y)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize()
