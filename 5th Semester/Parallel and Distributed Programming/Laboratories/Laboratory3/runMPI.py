import sys
import subprocess


if __name__ == "__main__":
  if len(sys.argv) != 3:
    print(f"Usage: python {sys.argv[0]} <file_name> <num_processes>")
    exit(1)

  cpp_file = sys.argv[1]
  exe_file = cpp_file.split('.')[0]
  num_processes = sys.argv[2]
  subprocess.run(f"mpic++ -o {exe_file} {cpp_file}", shell=True, check=True)
  subprocess.run(f"mpirun -n {num_processes} {exe_file}", shell=True, check=True)
  subprocess.run(f"rm {exe_file}", shell=True, check=True)
