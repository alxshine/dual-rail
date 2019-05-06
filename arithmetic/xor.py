from multiop import *

m = MultiStepOperation([
    UnaryOperation(0,lambda x: x | x<<wordsize),#2
    UnaryOperation(1,lambda x: x | cycle_right(x, wordsize)), #3
    BinaryOperation(2,3,lambda x,y: x & y), #4
    UnaryOperation(4,lambda x: x | cycle_right(x, 2*wordsize)), #5
    UnaryOperation(5,lambda x: cycle_right(x, wordsize)), #6
    UnaryOperation(6,lambda x: scheme2_filter & x), #7
    Convert_2_1(7), #7
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x^y)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize("XOR")
