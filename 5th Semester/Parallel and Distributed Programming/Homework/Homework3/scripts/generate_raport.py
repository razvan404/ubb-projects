import sys
import subprocess
import csv


def compute_average(fun, runs):
    total = 0
    for _ in range(runs):
        total += float(fun())
    return total / runs


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <run counts>")
        exit(1)

    run_counts = int(sys.argv[1])
    programs = [("sendRecv.cpp", [5, 9, 21]), ("scatterGatter.cpp", [4, 8, 20])]
    tests = []

    for program_name, processes_counts in programs:
      for processes in processes_counts:
        total = compute_average(lambda: subprocess.check_output(["python", "runMPI.py", program_name, str(processes)])[:-1], run_counts)
        tests.append([program_name, processes, total])
        print(f"{program_name} - {processes} - {total}")

    with open("raport.csv", "w") as out:
      csv_out = csv.writer(out)
      csv_out.writerow(['name', 'processes', 'result'])
      for row in tests:
        csv_out.writerow(row)
