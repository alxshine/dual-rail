from multiop import *

m = MultiStepOperation([
    BinaryOperation(0,1,lambda x,y: x | cycle_right(y, wordsize)), #2
    UnaryOperation(2, lambda x: x | cycle_left(x, wordsize)), #3
    UnaryOperation(3, lambda x: x ^ cycle_left(x, 2*wordsize)), #4
    UnaryOperation(4, lambda x: scheme2_filter & cycle_right(x, wordsize)), #5
    UnaryOperation(5, lambda x: x | cycle_left(x, wordsize)), #6
    UnaryOperation(6, lambda x: x & scheme1_filter)
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x^y)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize()
