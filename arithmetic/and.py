from multiop import *

m = MultiStepOperation([
    BinaryOperation(0,1,lambda x,y: x&y), #2
    BinaryOperation(0,1,lambda x,y: x|y), #3
    BinaryOperation(2,3, lambda x,y: x|(y<<wordsize)), #4
    UnaryOperation(4, lambda x: x & scheme2_filter), #5
    Convert_2_1(5) #6
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x&y)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize("AND")
