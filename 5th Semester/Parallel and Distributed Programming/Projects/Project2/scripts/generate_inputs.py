import os
import random

from consts import *


def write_random_matrix(file, shape: int, limits: (int, int)):
	file.write(f"{shape} {shape}\n")
	for i in range(shape):
		for j in range(shape - 1):
			file.write(f"{random.randint(*limits)} ")
		file.write(f"{random.randint(*limits)}\n")
	


if __name__ == "__main__":
	if not os.path.exists(INPUTS_DIR):
		os.mkdir(INPUTS_DIR)
	matrix_limits = (0, 255)
	filter_limits = (0, 1)
	for idx, test_case_shape in enumerate(TEST_CASES_SHAPES, start=1):
		matrix_size, filter_size = test_case_shape
		
		with open(os.path.join(INPUTS_DIR, f"input{idx}.txt"), "w") as f:
			write_random_matrix(f, matrix_size, matrix_limits)
			write_random_matrix(f, filter_size, filter_limits)
