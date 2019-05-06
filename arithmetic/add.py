from multiop import *

m = MultiStepOperation([
    BinaryOperation(0,1,lambda x,y: x+y),#2
    UnaryOperation(2, lambda x: x + 0x00010000),#3
    UnaryOperation(3, lambda x: x & scheme1_filter) #4
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x+y)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize("ADD")
