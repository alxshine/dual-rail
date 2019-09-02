from multiop import (MultiStepOperation, BinaryOperation, UnaryOperation,
                     Convert_2_1, wordsize, scheme2_filter)

m = MultiStepOperation([
    BinaryOperation(0, 1, lambda x, y: x | y),  # 2
    BinaryOperation(0, 1, lambda x, y: x & y),  # 3
    BinaryOperation(2, 3, lambda x, y: x | (y << wordsize)),  # 4
    UnaryOperation(4, lambda x: x & scheme2_filter),  # 5
    Convert_2_1(5)  # 6
])
m.execute()
incorrect_results = m.testCorrectness(lambda x, y: x | y)
print(f"Number of incorrect results: {len(incorrect_results.keys())}")
m.visualize("")
