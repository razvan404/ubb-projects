import os
import sys


if __name__ == "__main__":
  if len(sys.argv) != 2:
    print(f"Invalid syntax!\nUsage: python {sys.argv[0]} <outputs dir>")
    exit(1)

  outputs_dir = sys.argv[1]
  files = list(os.listdir(outputs_dir))
  if len(files) < 2:
    print("There should be at least 2 files in the specified directory!")
    exit(1)

  differences = False

  with open(os.path.join(outputs_dir, files[0]), 'r') as f:
    first_file_content = f.read()

  for file in files[1:]:
    with open(os.path.join(outputs_dir, file), 'r') as f:
      if f.read() != first_file_content:
        print(f"Files {files[0]} and {file} differ!")
        differences = True
    
  if not differences:
    print("All files are equal!")
  