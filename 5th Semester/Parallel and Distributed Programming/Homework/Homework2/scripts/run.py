import sys
import subprocess
import csv


def compute_average(fun, runs):
    total = 0
    for _ in range(runs):
        total += float(fun())
    return total / runs


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <java/c> <program name> <run counts>")
        exit(1)

    language = sys.argv[1]
    program_name = sys.argv[2]
    run_counts = int(sys.argv[3])

    run_script = ['java', program_name] if language == 'java' else [f'./{program_name}']

    types = ['sequential', 'lines']
    test_cases = [[10, 10, 3], [1000, 1000, 3], [10000, 10000, 3]]
    thread_counts = [[2], [2, 4, 8, 16], [2, 4, 8, 16]]
    tests = []

    for test_case, thread_count in zip(test_cases, thread_counts):
        n, m, k = test_case
        name = f'{types[0]}_{n}_{m}_{k}'
        total = compute_average(lambda: subprocess.check_output([*run_script, f'input{n}_{m}_{k}.txt', types[0]])[:-1], run_counts)
        tests.append([name, total])
        print(name, "done :D")

        for type in types[1:]:
            for p in thread_count:
                name = f'{type}_{n}_{m}_{k}_{p}'
                total = compute_average(lambda: subprocess.check_output([*run_script, f'input{n}_{m}_{k}.txt', type, str(p)])[:-1], run_counts)
                tests.append([name, total])
                print(name, "done :D")

    with open("raport.csv", "w") as out:
        csv_out = csv.writer(out)
        csv_out.writerow(['name', 'result'])
        for row in tests:
            csv_out.writerow(row)
