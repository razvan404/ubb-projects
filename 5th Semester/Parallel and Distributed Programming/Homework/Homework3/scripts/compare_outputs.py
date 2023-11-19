import sys


if __name__ == "__main__":
  if len(sys.argv) != 3:
    print(f"Usage: python {sys.argv[0]} <file1> <file2>")
    exit(1)

  file1 = sys.argv[1]
  file2 = sys.argv[2]

  idxs = []

  with open(file1, 'r') as f1:
    with open(file2, 'r') as f2:
      for idx, line1 in enumerate(f1.readlines()):
        line2 = f2.readline()
        if line1 != line2:
          idxs.append(idx + 1)
  if len(idxs) > 0:
    print("Files are different")
    print(idxs)
  else:
    print("Files are the same")
