import sys
import random


if __name__ == "__main__":
  if len(sys.argv) != 6:
    print(f"Usage: python {sys.argv[0]} <file> <n> <m> <k> <l>")
    exit(1)
  
  file = sys.argv[1]
  n = int(sys.argv[2])
  m = int(sys.argv[3])
  k = int(sys.argv[4])
  l = int(sys.argv[5])

  with open("../data/input_sg.txt", 'w') as f:
    f.write(f"{k}\n")
    for i in range(k):
      for j in range(k - 1):
        f.write(f"{random.randint(0, 1)} ")
      f.write(f"{random.randint(0, 1)}\n")

    f.write(f"{n} {m}\n")
    for i in range(n):
      for j in range(m - 1):
        f.write(f"{random.randint(1, l)} ")
      f.write(f"{random.randint(1, l)}\n")
