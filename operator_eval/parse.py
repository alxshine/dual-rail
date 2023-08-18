import pathlib
import re

import numpy as np
import pickle

import validate


def load_parsed():
    """Load parsed pickle or generate one if none exist.

    Returns:
        balanced_output, unbalanced_output -- the parsed outputs
    """
    try:
        print("Trying to load previously parsed data")
        with open('balanced.pkl', 'rb') as balanced_file, open('unbalanced.pkl', 'rb') as unbalanced_file:
            balanced_output = pickle.load(balanced_file)
            unbalanced_output = pickle.load(unbalanced_file)
        print("Success!")
    except FileNotFoundError:
        print("Not found, generating")
        print("Validating files are equal")
        validate.validate_files('logs')
        balanced_output, unbalanced_output = parse_dir('logs')
        with open('balanced.pkl', 'wb+') as balanced_file, open('unbalanced.pkl', 'wb+') as unbalanced_file:
            b_pickler = pickle.Pickler(balanced_file)
            b_pickler.dump(balanced_output)

            ub_pickler = pickle.Pickler(unbalanced_file)
            ub_pickler.dump(unbalanced_output)
        print("Done!\n")

    return balanced_output, unbalanced_output


def parse_dir(log_dir):
    path = pathlib.Path(log_dir)

    balanced_logs = list(path.glob("balanced_*.log"))
    balanced_output = parse_files(balanced_logs)

    unbalanced_logs = list(path.glob("unbalanced_*.log"))
    unbalanced_output = parse_files(unbalanced_logs)

    return balanced_output, unbalanced_output


def parse_files(file_paths):
    output = []
    for i, log_name in enumerate(file_paths):
        with open(log_name, 'r') as log_file:
            print(f"Parsing {log_name}")
            parse_file(log_file, i, output, (len(file_paths), 13))

    return output


def parse_file(log_file, file_index, output, value_shape):
    mnemonic_re = re.compile(r'(\d+)\s+(\w+)\s+(.*)$')
    skip = True
    j = 0
    iterator = iter(log_file)
    while True:
        # get line
        try:
            line = next(iterator)
        except StopIteration:
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
        if mnemonic_parts is None:
            continue
        mnemonic_parts = mnemonic_parts.groups()

        # get values
        value_line = next(iterator)
        values = [int(v, 16) for v in value_line.split(',')]

        if file_index == 0:
            # add line to output if first file
            value_matrix = np.empty(value_shape, dtype=np.int)
            output.append({'mnemonic': mnemonic_parts, 'values': value_matrix})

        if j > 0:
            output[j-1]['values'][file_index] = np.array(values)

        j += 1


if __name__ == "__main__":
    load_parsed()
