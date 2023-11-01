import sys
import os


if __name__ == "__main__":
  if (len(sys.argv) != 4):
    print(f"Usage: {sys.argv[0]} <script name> <program name> <run counts>")
    exit(1)
  script_name = sys.argv[1]
  program_name = sys.argv[2]
  run_counts = sys.argv[3]


  types = ['block']
  test_cases = [[10, 10, 3], [1000, 1000, 5], [10, 10000, 5], [10000, 10, 5]]
  thread_counts = [[4], [2, 4, 8, 16], [2, 4, 8, 16], [2, 4, 8, 16]]

  for test_case, thread_count in zip(test_cases, thread_counts):
    n, m, k = test_case
    just_script_with_file = f'powershell.exe .\\{script_name} {program_name} input{n}_{m}_{k}.txt'

    for threads in thread_count:
      cmd = f'{just_script_with_file},{types[0]},{threads} {run_counts}'
      print(cmd)
      os.system(cmd)