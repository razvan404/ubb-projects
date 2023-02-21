#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THR_MAX 10
pthread_t thr[THR_MAX];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int n;

void* f(void* a) {
	int k = *((int*) a);
	int i;
	for (i = 0; i < n; ++i) {
		printf("[THREAD %d]: %d!\n", k, i);
	}
	return NULL;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Invalid syntax!\nUsage: %s n\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	n = atoi(argv[1]);
	int i;	
	for (i = 0; i < THR_MAX; ++i) {
		int* p = malloc(sizeof(int));
		*p = i;
		pthread_create(&thr[i], NULL, f, p);
	}

	for (i = 0; i < THR_MAX; ++i) {
		pthread_join(thr[i], NULL);
	}
	return EXIT_SUCCESS;
}

