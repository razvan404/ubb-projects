#include <algorithm>

struct Matrix {
	int* data;
	int shape[2];
};
void convolutionInline(Matrix* matrix, Matrix* filter, int blockSqrtSize);
