#include "cuda_runtime.h"
#include "./convolution.cuh"
#include "device_launch_parameters.h"

__global__
void convolutionKernel(
	int* matrix, int* filter, int* output,
	int matrixDim0, int matrixDim1, int filterDim0, int filterDim1
) {
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	int j = blockIdx.y * blockDim.y + threadIdx.y;

	if (i >= matrixDim0 || j >= matrixDim1) {
		return;
	}

	int result = 0;
	int halfFilterDim0 = filterDim0 / 2,
		halfFilterDim1 = filterDim1 / 2;
	for (int p = 0; p < filterDim0; ++p) {
		for (int q = 0; q < filterDim1; ++q) {

			int curRow = i - halfFilterDim0 + p;
			if (curRow < 0) {
				curRow = 0;
			}
			else if (curRow >= matrixDim0) {
				curRow = matrixDim0 - 1;
			}
			int curCol = j - halfFilterDim1 + q;
			if (curCol < 0) {
				curCol = 0;
			}
			else if (curCol >= matrixDim1) {
				curCol = matrixDim1 - 1;
			}

			result += matrix[curRow * matrixDim0 + curCol] * filter[p * filterDim0 + q];
		}
	}
	output[i * matrixDim0 + j] = result;
}

void convolutionInline(Matrix* matrix, Matrix* filter, int blockSqrtSize) {
	int matrixBytes = matrix->shape[0] * matrix->shape[1] * sizeof(int),
		filterBytes = filter->shape[0] * filter->shape[1] * sizeof(int);
	
	// Initialize the flatten matrices to CUDA
	int* dMatrix, * dFilter, * dOutput;
	cudaMalloc((void **)&dMatrix, matrixBytes);
	cudaMalloc((void **)&dFilter, filterBytes);
	cudaMalloc((void **)&dOutput, matrixBytes);

	// Copy the data to the initialized matrices on CUDA
	cudaMemcpy(dMatrix, matrix->data, matrixBytes, cudaMemcpyHostToDevice);
	cudaMemcpy(dFilter, filter->data, filterBytes, cudaMemcpyHostToDevice);

	// Init the blockSize and the gridSize
	dim3 blockSize(blockSqrtSize, blockSqrtSize);
	dim3 gridSize(
		(matrix->shape[0] + blockSize.x - 1) / blockSize.x,
		(matrix->shape[1] + blockSize.y - 1) / blockSize.y
	);

	// Apply the convolution kernel
	convolutionKernel << <gridSize, blockSize >> > (
		dMatrix, dFilter, dOutput,
		matrix->shape[0], matrix->shape[1], filter->shape[0], filter->shape[1]
	);

	// Copy the data from the device to the matrix
	cudaMemcpy(matrix->data, dOutput, matrixBytes, cudaMemcpyDeviceToHost);

	// Free device memory
	cudaFree(dMatrix);
	cudaFree(dFilter);
	cudaFree(dOutput);
}