#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int freq[10];

void* f(void* a) {
	int k = *((int*)a);
	free(a);

	while (k) {
		int c = k % 10;
		k = k / 10;
		pthread_mutex_lock(&mtx);
		freq[c]++;
		pthread_mutex_unlock(&mtx);
	}

	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Invalid syntax!\nUsage: %s num1 num2 ..\n", argv[0]);
		return EXIT_FAILURE;
	}

	int n = argc - 1, i;
	pthread_t thr[n];

	for (i = 0; i < n; ++i) {
		int* k = malloc(sizeof(int));
		*k = atoi(argv[i + 1]);
		
		pthread_create(&thr[i], NULL, f, k);
	}

	for (i = 0; i < n; ++i) {
		pthread_join(thr[i], NULL);
	}

	for (i = 0; i < 10; ++i) {
		printf("Occurences for the digit %d: %d.\n", i, freq[i]);
	}

	return EXIT_SUCCESS;
}
