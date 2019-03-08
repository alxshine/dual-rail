from multiop import *

m = MultiStepOperation([
    UnaryOperation(1, lambda x: x+0x00000100), #2
    UnaryOperation(2, lambda x: bit_not(x)), #3
    UnaryOperation(3, lambda x: x+0x01000000), #4
    UnaryOperation(4, lambda x: x & scheme1_filter), #5
    BinaryOperation(0, 5, lambda x,y: x+y), #6
    UnaryOperation(6, lambda x: x & scheme1_filter)

    # BinaryOperation(0, 1, lambda x,y: bit_sub(x,y)), #2
    # BinaryOperation(0, 1, lambda x,y: x + cycle_right(y, 2*wordsize)), #3
    # BinaryOperation(2, 3, lambda x,y: x | (y>>wordsize)), #4
    # UnaryOperation(4, lambda x: x & scheme2_filter), #5
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x-y)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize("SUB")
