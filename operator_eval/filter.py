import numpy as np
import pickle
import argparse
import copy

import parse


def get_changes(output):
    """Filter an output list for changes, replacing values identical with the previous iteration with 0s.

    Arguments:
        output {list} -- list of tuples of mnemonics and values

    Returns:
        new_output -- filtered list of tuples with values reduced to changes
    """
    new_output = []
    for i, line_dict in enumerate(output):
        if i == 0:
            new_output.append(copy.deepcopy(line_dict))
            continue

        mnemonic = copy.deepcopy(line_dict['mnemonic'])
        current_values = line_dict['values']
        diffs = current_values != output[i-1]['values']
        filtered_values = current_values * diffs

        new_output.append({'mnemonic': mnemonic, 'values': filtered_values})

    return new_output


def apply_func(output, func):
    """Apply func to every instruction in output.

    Arguments:
        output {list} -- list of tuples of mnemonics and values
        func {callable} -- function to apply to elements in output

    Returns:
        new_output -- new list with func applied to every value matrix
    """
    new_output = []
    for dict in output:
        mnemonic = copy.deepcopy(dict['mnemonic'])
        values = dict['values']
        new_values = func(values)
        new_output.append({'mnemonic': mnemonic, 'values': new_values})
    return new_output


def _hamming_weight(var):
    return bin(var).count("1")


hamming_weight = np.vectorize(_hamming_weight)


def filter_output(output):
    """Apply all filters to output.

    Arguments:
        output {list} -- list of tuples of mnemonics and values
    """
    print("Filtering for new")
    new_only = get_changes(output)
    print("Applying Hamming Weight function")
    balanced_hamming = apply_func(new_only, hamming_weight)
    # filter lines where multiple values change
    print("Filtering out pops")
    balanced_hamming = list(
        filter(lambda x: 'pop' not in x['mnemonic'], balanced_hamming))
    return balanced_hamming


def load_filtered():
    try:
        print("Trying to load previously filtered data")
        with open('filtered_balanced.pkl', 'rb') as balanced_file, open('filtered_unbalanced.pkl', 'rb') as unbalanced_file:
            balanced_filtered = pickle.load(balanced_file)
            unbalanced_filtered = pickle.load(unbalanced_file)
        print("Success!")
    except FileNotFoundError:
        print("Not found, generating")
        balanced_output, unbalanced_output = parse.load_parsed()
        balanced_filtered = filter_output(balanced_output)
        unbalanced_filtered = filter_output(unbalanced_output)

        with open('filtered_balanced.pkl', 'wb+') as balanced_file, open('filtered_unbalanced.pkl', 'wb+') as unbalanced_file:
            b_pickler = pickle.Pickler(balanced_file)
            b_pickler.dump(balanced_filtered)

            ub_pickler = pickle.Pickler(unbalanced_file)
            ub_pickler.dump(unbalanced_filtered)
        print("Done!\n")

    return balanced_filtered, unbalanced_filtered


if __name__ == "__main__":
    load_filtered()
