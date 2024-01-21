import os
import sys
import subprocess
import pandas as pd

from tqdm import trange
from consts import *


def compute_average(fun: callable, runs: int, desc: str = "Iteration", val: callable = None) -> float:
    total = 0
    for _ in trange(runs, desc=desc):
        total += float(fun())
        if val:
            val()
    return total / runs


def check_files_the_same(path1: str, path2: str) -> bool:
    with open(path1, "r") as f1, open(path2, "r") as f2:
        for line1, line2 in zip(f1, f2):
            if line1 != line2:
                return False
    return True


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python generate_raport.py <exe file>")
        sys.exit(1)
    executable_file = sys.argv[1]
    runs_count = 10
    raport = []
    cuda_block_sqrt_sizes = [2**2, 2**3, 2**4, 2**5]
    for idx in range(1, len(TEST_CASES_SHAPES) + 1):
        matrix_size = TEST_CASES_SHAPES[idx - 1][0]
        filter_size = TEST_CASES_SHAPES[idx - 1][1]
        sequential_time = compute_average(
            lambda: subprocess.check_output(
                [executable_file], input=f"sequential {idx}", text=True
            ).strip(),
            runs=runs_count,
            desc=f"Sequential {idx}",
        )
        print(sequential_time)
        raport.append({"Type": "Sequential", "Block Dim": "-", "Matrix Size": matrix_size, "Filter Size": filter_size, "Time": sequential_time})
        for cuda_block_sqrt_size in cuda_block_sqrt_sizes:
            cuda_time = compute_average(
                lambda: subprocess.check_output(
                    [executable_file], input=f"cuda {idx} {cuda_block_sqrt_size}", text=True
                ).strip(),
                runs=runs_count,
                desc=f"CUDA {idx}, Block Dim: {cuda_block_sqrt_size**2}",
                val=lambda: check_files_the_same(
                    os.path.join(OUTPUTS_DIR, f"sequential{idx}.txt"),
                    os.path.join(OUTPUTS_DIR, f"cuda{idx}.txt"),
                ),
            )
            print(cuda_time)
            raport.append({"Type": "CUDA", "Block Dim": cuda_block_sqrt_size**2, "Matrix Size": matrix_size, "Filter Size": filter_size, "Time": cuda_time})

    pd.DataFrame(raport).to_csv("raport.csv", index=False)
