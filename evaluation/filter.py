import numpy as np

import pathlib
import re
import sys


def load_files(log_dir):
    mnemonic_re = re.compile('(\d+)\s+(\w+)\s+(.*)$')

    path = pathlib.Path(log_dir)
    balanced_logs = list(path.glob("balanced_*.log"))

    num_logs = len(balanced_logs)
    output = []
    for i, log_name in enumerate(balanced_logs):
        with open(log_name, 'r') as log_file:
            skip = True
            j = 0
            iterator = iter(log_file)
            while True:
                # get line
                try:
                    line = next(iterator)
                except StopIteration:
                    print("File ended")
                    break

                # ignore the gdb preamble
                if skip:
                    if 'AES128_ECB_encrypt' in line:
                        skip = False
                        j = 0
                    continue

                # split mnemonic
                mnemonic_parts = mnemonic_re.search(line)
                # if its not a mnemonic, we entered a new function
                if mnemonic_parts == None:
                    continue
                mnemonic_parts = mnemonic_parts.groups()
                
                # get values
                value_line = next(iterator)
                values = [int(v,16) for v in value_line.split(',')]

                # add if i==0, fill in otherwise
                if i==0:
                    value_matrix = np.empty((len(balanced_logs),len(values)))
                    value_matrix[0] = np.array(values)

                    output.append({'mnemonic':mnemonic_parts,'values':value_matrix})
                else:
                    output[j]['values'][i] = np.array(values)
                j += 1


if __name__ == "__main__":
    load_files('evaluation')
