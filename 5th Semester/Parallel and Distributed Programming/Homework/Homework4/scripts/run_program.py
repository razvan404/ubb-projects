import sys
import subprocess

if __name__ == "__main__":
  if len(sys.argv) < 2:
    print(f"Invalid syntax!\nUsage: python {sys.argv[0]} <cpp_file> <args...>")
  
  cpp_file = sys.argv[1]
  args = sys.argv[2:]
  common_files = []

  subprocess.run(f"g++ -std=c++2b {' '.join(common_files)} {cpp_file}", shell=True, check=True)
  subprocess.run(f"./a.out {' '.join(args)}", shell=True, check=True)
  subprocess.run("rm a.out", shell=True, check=True)
