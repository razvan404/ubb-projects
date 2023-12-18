import subprocess
import pandas as pd

from tqdm import trange


def compute_average(fun, runs, desc: str = "Iteration", val: callable = None):
  total = 0
  for _ in trange(runs, desc=desc):
    total += float(fun())
    if val:
      val()
  return total / runs


def validate_equal_outputs():
  output = subprocess.check_output([
    "python",
    "scripts/check_outputs.py",
    "outputs"
  ]).strip()
  if output != b"All files are equal!":
    raise Exception(output)


if __name__ == "__main__":
  writers_counts = [4, 6, 8, 16]
  readers_counts = [1, 2]
  raport = []
  runs_count = 20

  sequential_time = compute_average(
    lambda: subprocess.check_output([
        "python",
        "scripts/run_program.py",
        "sequential.cpp"
      ]).strip(),
    runs_count,
    desc="Sequential"
  )
  raport.append({"Type": "Sequential", "Read Threads": "-", "Worker Threads": "-", "Time": sequential_time})

  for readers_count in readers_counts:
    for writers_count in writers_counts:
      threads_time = compute_average(
        lambda: subprocess.check_output([
            "python",
            "scripts/run_program.py",
            "threads.cpp",
            str(readers_count),
            str(writers_count)
          ]).strip(),
        runs_count,
        desc=f"{readers_count} readers, {writers_count} writers",
        val=validate_equal_outputs
      )
      raport.append({"Type": "Threads", "Read Threads": readers_count, "Worker Threads": writers_count, "Time": threads_time})

  pd.DataFrame(raport).to_csv("raport.csv", index=False)
