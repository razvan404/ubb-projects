#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int n, m;
int** matrix,* sums;

void* f(void* a) {
	int k = *((int*)a), j;
	free(a);
	sums[k] = 0;
	for (j = 0; j < m; ++j) {
		sums[k] += matrix[k][j];
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	freopen("matrix.txt", "r", stdin);
	int i, j;
	scanf("%d", &n);
	scanf("%d", &m);

	pthread_t thr[n];
	sums = (int*)malloc(n * sizeof(int));

	matrix = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; ++i) {
		matrix[i] = (int*)malloc(m * sizeof(int));
		for (j = 0; j < m; ++j) {
			scanf("%d", &matrix[i][j]);
		}
		int* k = malloc(sizeof(int));
		*k = i;

		pthread_create(&thr[i], NULL, f, k);
	}

	for (i = 0; i < n; ++i) {
		pthread_join(thr[i], NULL);
		printf("[THREAD %d]: %d\n", i, sums[i]);
		free(matrix[i]);
	}
	free(matrix);
	free(sums);

	fclose(stdin);
	return EXIT_SUCCESS;
}
