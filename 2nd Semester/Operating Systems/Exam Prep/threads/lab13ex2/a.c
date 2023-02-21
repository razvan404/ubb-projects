#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_MAX 200000
int val[NUM_MAX];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;

int total = 0;

int is_prime(int x) {
	int d;
	if (x < 2) {
		return 0;
	}
	for (d = 2; d * d <= x; ++d) {
		if (x % d == 0) {
			return 0;
		}
	}

	return 1;
}

void* f(void* a) {
	int k = *((int*)a), i, ocr = 0;
	free(a);

	for (i = 0; i < NUM_MAX; ++i) {
		if (val[i] == k) {
			ocr++;
			pthread_mutex_lock(&mtx);
			total++;
			pthread_mutex_unlock(&mtx);
		}
	}

	pthread_barrier_wait(&bar);

	printf("Numarul %d are un numar mediu de aparitii de %.2f%c.\n", k, ocr * 100.0 / total, '%');

	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	int fd = open("random-file", 0600, O_RDONLY);

	int i, num_prim = 0;
	for (i = 0; i < NUM_MAX; ++i) {
		read(fd, &val[i], 2);
	}
	
	for (i = 0; i < 101; ++i) {
		if (is_prime(i)) {
			num_prim++;
		}
	}

	int q = 0;
	pthread_t thr[num_prim];
	pthread_barrier_init(&bar, NULL, num_prim);

	for (i = 0; i < 101; ++i) {
		if (is_prime(i)) {
			int* k = malloc(sizeof(int));
			*k = i;
			
			pthread_create(&thr[q], NULL, f, k);
			q++;		
		}
	}

	for (i = 0; i < num_prim; ++i) {
		pthread_join(thr[i], NULL);
	}

	pthread_barrier_destroy(&bar);
	return EXIT_SUCCESS;
}
