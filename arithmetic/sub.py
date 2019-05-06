from multiop import *

m = MultiStepOperation([
    UnaryOperation(1, lambda x: cycle_left(x, 16)+1), #2
    BinaryOperation(0,2, lambda x,y: x+y), #3
    UnaryOperation(3, lambda x: x & scheme1_filter) #4
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x-y)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize("SUB")
