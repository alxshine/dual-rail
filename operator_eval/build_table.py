import filter
import numpy as np

def accumulate_stat(data, func):
    """Applies func over all rows in data, summing up the results

    Arguments:
        data {list} -- list of tuples of mnemonics and value matrices
        func {callable} -- function with a single row as parameter, returning an int

    Returns:
        int -- summed statistic
    """
    acc = 0
    for row in data:
        acc += func(row)
    return acc

def _test_constant_hamming_weight(row):
    values = row['values']
    truth_matrix = [np.all(values[i] == values[0]) for i in range(values.shape[0])]
    return np.all(truth_matrix)

if __name__ == "__main__":
    balanced, unbalanced = filter.load_filtered()
    
    #no. instructions
    no_bal = len(balanced)
    no_unbal = len(unbalanced)

    # increase
    inc_bal = no_bal/no_unbal
    inc_unbal = 1

    # balanced operations
    print("Getting number of balanced instructions")
    balanced_ops_bal = accumulate_stat(balanced, _test_constant_hamming_weight)
    balanced_ops_unbal = accumulate_stat(unbalanced, _test_constant_hamming_weight)

    # unbalanced operations
    print("Getting number of unbalanced instructions")
    unbalanced_ops_bal = accumulate_stat(balanced, lambda r: 1 - _test_constant_hamming_weight(r))
    unbalanced_ops_unbal = accumulate_stat(unbalanced, lambda r: 1 - _test_constant_hamming_weight(r))

    # balancedness
    balancedness_bal = balanced_ops_bal / no_bal * 100
    balancedness_unbal = balanced_ops_unbal / no_unbal * 100

    print(f"{no_unbal=}")
    print(f"{inc_unbal=}")
    print(f"{balanced_ops_unbal=}")
    print(f"{unbalanced_ops_unbal=}")
    print(f"{balancedness_unbal=}%")
    print(f"sum of balanced and unbalanced: {balanced_ops_unbal + unbalanced_ops_unbal}\n")

    print(f"{no_bal=}")
    print(f"{inc_bal=}")
    print(f"{balanced_ops_bal=}")
    print(f"{unbalanced_ops_bal=}")
    print(f"{balancedness_bal=}%")
    print(f"sum of balanced and unbalanced: {balanced_ops_bal + unbalanced_ops_bal}\n")