import pathlib
import re
import sys

def validate_files(log_dir):
    path = pathlib.Path(log_dir)
    balanced_log_files = path.glob('balanced_*.log')
    filtered_balanced = filter_files(balanced_log_files)

    mnemonic_re = re.compile('(\d+\s*)(.*$)')

    all_equal = True
    for lines in zip(*filtered_balanced):
        mnemonics = [mnemonic_re.search(l)[2] for l in lines if mnemonic_re.match(l)]

        if any(m != mnemonics[0] for m in mnemonics[1:]):
            print("ERROR: not all execution paths are equal.\nOffending lines:\n", file=sys.stderr)
            all_equal = False
            for l in lines:
                print(l, file=sys.stderr)

    if all_equal:
        print("All control flows are equal!")

def filter_files(balanced_log_files):
    filtered_logs = []
    for f in balanced_log_files:
        reg_dump = re.compile('([\da-f]{8},){12}[\da-f]{8}')
        with open(f, 'r') as log:
            filtered_log = [line for line in log if not reg_dump.match(line)]
            filtered_logs.append(filtered_log)

    return filtered_logs


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} log_dir")
        sys.exit(1)

    log_dir = sys.argv[1]
    validate_files(log_dir)
