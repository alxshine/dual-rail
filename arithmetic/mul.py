from multiop import *

m = MultiStepOperation([
    Convert_1_2(1), #2
    BinaryOperation(0,2, lambda x,y: (x*y) & 0xffffffff),#3
    BinaryOperation(3,1, lambda x,y: x + (y << 16)), #4
    UnaryOperation(4, lambda x: x + 0x00ff0000), #5
    UnaryOperation(5, lambda x: x & 0x00ff00ff), #6
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: (x*y)&0xff)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize("MUL")
