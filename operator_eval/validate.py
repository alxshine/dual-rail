import pathlib
import re
import sys


def validate_files(log_dir):
    path = pathlib.Path(log_dir)

    print("Checking balanced logs")
    balanced_log_files = list(path.glob('balanced_*.log'))
    filtered_balanced = filter_files(balanced_log_files)
    errors = check_equality(filtered_balanced)
    if errors is not None:
        print("There were errors during validation")
        print(f"Offending files: {[balanced_log_files[i] for i in errors]}")
        raise EnvironmentError

    print("Checking unbalanced logs")
    unbalanced_log_files = list(path.glob('unbalanced_*.log'))
    filtered_unbalanced = filter_files(unbalanced_log_files)
    errors = check_equality(filtered_unbalanced)
    if errors is not None:
        print("There were errors during validation")
        print(f"Offending files: {[unbalanced_log_files[i] for i in errors]}")
        raise EnvironmentError
    return True


def check_equality(filtered_logs):
    mnemonic_re = re.compile('(\d+\s*)(.*$)')

    all_errors = set()
    for lines in zip(*filtered_logs):
        mnemonics = [mnemonic_re.search(l)[2]
                     for l in lines if mnemonic_re.match(l)]

        errors = [m != mnemonics[0] for m in mnemonics[1:]]
        if any(errors):
            for i, e in enumerate(errors):
                if e:
                    all_errors.add(i)
            print(
                "ERROR: not all execution paths are equal.\nOffending lines:\n", file=sys.stderr)
            for i, l in enumerate(lines):
                print(f"{i}: {l}", file=sys.stderr)

    if len(all_errors) == 0:
        print("All control flows are equal!\n")
        return None
    else:
        return all_errors


def filter_files(balanced_log_files):
    filtered_logs = []
    for f in balanced_log_files:
        reg_dump = re.compile('([\da-f]{8},){12}[\da-f]{8}')
        with open(f, 'r') as log:
            filtered_log = [line for line in log if not reg_dump.match(line)]
            filtered_logs.append(filtered_log)

    return filtered_logs


if __name__ == "__main__":
    validate_files('logs')
