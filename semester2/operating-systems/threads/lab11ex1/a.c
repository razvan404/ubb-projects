#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define NUM_MAX 1000
#define THR_MAX 10
int arr[NUM_MAX], tot_max = INT_MIN, buf[THR_MAX];
pthread_t thr[THR_MAX];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;

void* f(void* a) {
	int k = *((int*) a), i;
	
	for (i = k * 100; i < (k + 1) * 100; ++i) {
		if (arr[i] > buf[k]) {
			buf[k] = arr[i];
		}
	}

	pthread_mutex_lock(&mtx);
	if (buf[k] > tot_max) {
		tot_max = buf[k];
	}
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&bar);
	
	int tot_max = INT_MIN;
	int tot_min = INT_MAX;
	
	for (i = 0; i < THR_MAX; ++i) {
		if (buf[i] > tot_max) {
			tot_max = buf[i];
		}
		if (buf[i] < tot_min) {
			tot_min = buf[i];
		}
	}

	printf("[THREAD %d]: The maximum value I found is %d, the maximum difference is %d\n", k, buf[k], tot_max - buf[k] > buf[k] - tot_min ? tot_max - buf[k] : buf[k] - tot_min);

	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	pthread_barrier_init(&bar, NULL, 10);
	int fd = open("random-file", 0600, O_RDONLY);
	
	int i;
	for (i = 0; i < NUM_MAX; ++i) {
		read(fd, &arr[i], 2);
	}

	for (i = 0; i < THR_MAX; ++i) {
		int* k = malloc(sizeof(int));
		*k = i;
		pthread_create(&thr[i], NULL, f, k);
	}

	for (i = 0; i < THR_MAX; ++i) {
		pthread_join(thr[i], NULL);
	}

	pthread_barrier_destroy(&bar);

	return EXIT_SUCCESS;
}

