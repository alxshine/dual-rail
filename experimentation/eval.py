import argparse
import csv
import json
import matplotlib.pyplot as plt
plt.style.use('uibk')

import numpy as np
import matplotlib2tikz

parser = argparse.ArgumentParser(description='Visualize eval.json files')
parser.add_argument('files', metavar='eval.json', type=str, nargs='+', help='a json file to visualize')
parser.add_argument('--target', dest='target', metavar='output', type=str, help='the basename for the target')

args = parser.parse_args()
files = args.files
target = args.target

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

# save to csv file
with open('{}.csv'.format(target), 'w+') as target_file:
    writer = csv.writer(target_file)
    #header
    writer.writerow(['i', 'unbalanced-total', 'balanced-total', 'unbalanced-scaled', 'balanced-scaled'])
    unbalanced_sum = data[0].sum()
    balanced_sum = data[1].sum()
    for i in range(data.shape[1]):
        unbalanced_val = data[0,i]
        balanced_val = data[1,i]
        writer.writerow([i, unbalanced_val, balanced_val, unbalanced_val/unbalanced_sum, balanced_val/balanced_sum])

        
#total unbalanced
plt.figure()
plt.grid()
plt.bar(range(32), data[0])
plt.xticks(range(0,33,8))

# plt.show()
# matplotlib2tikz.save('{}_unbalanced.tex'.format(target))

#total balanced
plt.figure()
plt.grid()
plt.bar(range(32), data[1])
plt.xticks(range(0,33,8))

# matplotlib2tikz.save('{}_balanced.tex'.format(target))
# plt.show()

#comparison plot
plt.figure()
plt.grid()
plt.plot(data[0]/data[0].sum(), label='Unbalanced')
plt.plot(data[1]/data[1].sum(), label='Balanced')
plt.legend()

# matplotlib2tikz.save('{}_comparison.tex'.format(target))
# plt.show()
