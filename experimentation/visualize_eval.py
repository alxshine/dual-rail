import argparse
import json
import matplotlib.pyplot as plt
import numpy as np
import matplotlib2tikz

parser = argparse.ArgumentParser(description='Visualize eval.json files')
parser.add_argument('files', metavar='eval.json', type=str, nargs='+', help='a json file to visualize')

files = parser.parse_args().files

num_files = len(files)
num_plots = num_files + 1
num_cols = (num_plots//3)+1
num_rows = min(3, num_plots)

data = []
for file in files:
    with open(file, 'r') as jsonFile:
        tmp_data = json.load(jsonFile)
        data.append(tmp_data['hamming_weights'])

data = np.array(data).astype('float64')
for i in range(data.shape[0]):
    row_sum = data[i].sum()
    data[i] = data[i]/row_sum

plt.figure()
i = 0
for i in range(len(files)):
    plt.subplot(num_rows, num_cols, i+1)
    plt.title(files[i].replace('_', ' '))
    plt.bar(range(32), data[i])
    plt.xticks(range(33))

#comparison plot
plt.subplot(num_rows, num_cols, len(files)+1)
for i in range(len(files)):
    plt.plot(data[i], label=files[i].replace('_', ' '))
plt.legend()

plt.show()
# matplotlib2tikz.save('tikz_plot.tex')
