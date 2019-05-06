from multiop import *

m = MultiStepOperation([
    Convert_1_2(0),
    Convert_2_1(2)
])
m.execute()
incorrectResults = m.testCorrectness(lambda x,y: x)
print(f"Number of incorrect results: {len(incorrectResults.keys())}")
m.visualize("ORR")
