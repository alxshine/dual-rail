import csv
import numpy as np

filename = 'traces.csv'
num_rows = 1460
num_cols = 25000

print("Opening {}".format(filename))
with open(filename, 'r') as csvfile:
    print("Creating reader")
    reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    #ignore the first row
    reader.__next__()

    data = np.zeros((num_rows, num_cols))

    i = 0
    for row in reader:
        print("Row {}\r".format(i+1), end='')
        data[i] = row[1:]
        i += 1
    print()
    print("Saving")
    np.save("reference.npy", data)
    print("Done!")
