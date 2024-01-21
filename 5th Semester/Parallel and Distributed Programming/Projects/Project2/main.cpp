#include <iostream>
#include <chrono>
#include <string>
#include <tuple>
#include <algorithm>

#include "./convolution.cuh"

#pragma warning(disable: 4996)

std::tuple<Matrix*, Matrix*> readMatrices(char* filePath) {
	FILE* fin = fopen(filePath, "r");
	if (fin == NULL) {
		perror("Cannot open input file:");
		exit(1);
	}
	Matrix* matrix = new Matrix(), *filter = new Matrix();
	fscanf(fin, "%d%d", &matrix->shape[0], &matrix->shape[1]);
	int matrixNumElems = matrix->shape[0] * matrix->shape[1];
	matrix->data = new int[matrixNumElems];
	for (int i = 0; i < matrixNumElems; ++i) {
		fscanf(fin, "%d", &matrix->data[i]);
	}
	fscanf(fin, "%d%d", &filter->shape[0], &filter->shape[1]);
	int filterNumElems = filter->shape[0] * filter->shape[1];
	filter->data = new int[filterNumElems];
	for (int i = 0; i < filterNumElems; ++i) {
		fscanf(fin, "%d", &filter->data[i]);
	}
	fclose(fin);
	return { matrix, filter };
}

void writeMatrix(Matrix* matrix, char* filePath) {
	int matrixDim0 = matrix->shape[0], matrixDim1 = matrix->shape[1];
	FILE* fout = fopen(filePath, "w");
	if (fout == NULL) {
		perror("Cannot open output file:");
		exit(1);
	}
	for (int i = 0; i < matrixDim0; ++i) {
		for (int j = 0; j < matrixDim1 - 1; ++j) {
			fprintf(fout, "%d ", matrix->data[i * matrixDim0 + j]);
		}
		fprintf(fout, "%d\n", matrix->data[i * matrixDim0 + matrixDim1 - 1]);
	}
	fclose(fout);
}

void runSequential(int testCaseIdx, Matrix* matrix, Matrix* filter) {
	auto start = std::chrono::high_resolution_clock::now();
	int matrixDim0 = matrix->shape[0], matrixDim1 = matrix->shape[1],
		filterDim0 = filter->shape[0], filterDim1 = filter->shape[1];
	int halfFilterDim0 = filter->shape[0] / 2, halfFilterDim1 = filter->shape[1] / 2;
 	int* output = new int[matrixDim0 * matrixDim1];
	for (int i = 0; i < matrixDim0; ++i) {
		for (int j = 0; j < matrixDim1; ++j) {
			int result = 0;
			for (int p = 0; p < filterDim0; ++p) {
				for (int q = 0; q < filterDim1; ++q) {
					int curRow = std::min(std::max(i - halfFilterDim0 + p, 0), matrixDim0 - 1);
					int curCol = std::min(std::max(j - halfFilterDim1 + q, 0), matrixDim1 - 1);

					result += matrix->data[curRow * matrixDim0 + curCol] * filter->data[p * filterDim0 + q];
				}
			}
			output[i * matrixDim0 + j] = result;
		}
	}
	delete[] matrix->data;
	matrix->data = output;
	auto end = std::chrono::high_resolution_clock::now();
	double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
	std::cout << elapsedTimeMs << std::endl;
	
	char filePath[250];
	sprintf(filePath, "outputs\\sequential%d.txt", testCaseIdx);
	writeMatrix(matrix, filePath);
}

void runCuda(int testCaseIdx, Matrix* matrix, Matrix* filter) {
	int blockSqrtSize;
	scanf("%d", &blockSqrtSize);
	auto start = std::chrono::high_resolution_clock::now();
	convolutionInline(matrix, filter, blockSqrtSize);
	auto end = std::chrono::high_resolution_clock::now();
	double elapsedTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
	std::cout << elapsedTimeMs << std::endl;

	char filePath[250];
	sprintf(filePath, "outputs\\cuda%d.txt", testCaseIdx);
	writeMatrix(matrix, filePath);
}

int main() {
	char runType[250];
	int testCaseIdx;

	scanf("%s%d", runType, &testCaseIdx);

	char filePath[200];
	sprintf(filePath, "inputs\\input%d.txt", testCaseIdx);
	Matrix* matrix, * filter;
	std::tie(matrix, filter) = readMatrices(filePath);

	if (strcmp(runType, "sequential") == 0) {
		runSequential(testCaseIdx, matrix, filter);
	}
	else if (strcmp(runType, "cuda") == 0) {
		runCuda(testCaseIdx, matrix, filter);
	}
	else {
		printf("Invalid run type!");
	}

	delete[] matrix->data;
	delete matrix;
	delete[] filter->data;
	delete filter;
}
