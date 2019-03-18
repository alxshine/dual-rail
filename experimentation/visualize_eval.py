#!/usr/bin/python

import argparse
import json
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='Visualize eval.json files')
parser.add_argument('files', metavar='eval.json', type=str, nargs='+', help='a json file to visualize')

files = parser.parse_args().files

num_files = len(files)
num_cols = max(1, num_files//3)
num_rows = min(3, num_files)

data = []
for file in files:
    with open(file, 'r') as jsonFile:
        tmp_data = json.load(jsonFile)
        data.append(tmp_data['hamming_weights'])

max_count = 0
for d in data:
    max_count = max(max_count, max(d))

plt.figure()
i = 0
for i in range(len(files)):
    plt.subplot(num_rows, num_cols, i+1)
    plt.title(files[i])
    plt.bar(range(32), data[i])
    plt.ylim([0, max_count+10])
    plt.xticks(range(33))
plt.show()
