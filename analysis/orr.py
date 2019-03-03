from multiop import *

m = MultiStepOperation([
    BinaryOperation(0,1,lambda x,y: x|y), #2
    BinaryOperation(0,1,lambda x,y: x&y), #3
    BinaryOperation(2,3, lambda x,y: x|(y>>wordsize)), #4
    UnaryOperation(4, lambda x: x & scheme2_filter), #5
    BinaryOperation(5,5, lambda x,y: x|cycle_left(y, wordsize)), #6
    UnaryOperation(6, lambda x: x & scheme1_filter) #7
])
m.execute()
m.visualize()
