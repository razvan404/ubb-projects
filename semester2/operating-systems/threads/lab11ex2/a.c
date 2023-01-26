#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_MAX 100000
#define BUF_MAX 100
#define THR_MAX 10

int arr[NUM_MAX];
int buf[BUF_MAX];
pthread_t cons[THR_MAX];
pthread_t prod[THR_MAX];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int flag = 0; // 0 = empty, 1 = full
int suma = 0;

void* pf(void* a) {
	int k = *((int*)a), i;
	free(a);
	printf("[PRODUCER %d]: I was born!\n", k);
	pthread_mutex_lock(&mtx);
	while (flag == 1) {
		printf("[PRODUCER %d]: Buffer is full! Waiting to become empty!\n", k);
		pthread_cond_wait(&cond, &mtx);
	}

	printf("[PRODUCER %d]: Buffer is empty! Starting production...\n", k);
	for (i = 0; i < BUF_MAX; ++i) {
		buf[i] = arr[k * BUF_MAX + i];
	}
	printf("!! [PRODUCER %d]: Done producing...\n", k);
	flag = 1;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	
	pthread_exit(NULL);
}

void* cf(void* a) {
	int k = *((int*)a), i;
	free(a);
	
	printf("[CONSUMER %d]: I was born!\n", k);
	pthread_mutex_lock(&mtx);
	while (flag == 0) {
		printf("[CONSUMER %d]: Buffer is empty! Waiting to become full!\n", k);
		pthread_cond_wait(&cond, &mtx);
	}

	printf("[CONSUMER %d]: Buffer is full! Starting consumption...\n", k);
	for (i = 0; i < BUF_MAX; ++i) {
		suma += buf[i];
	}
	printf("!!! [CONSUMER %d]: Done consuming...\n", k);
	flag = 0;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);

	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	int fd = open("random-file", 0600, O_RDONLY), i;
	for (i = 0; i < NUM_MAX; ++i) {
		read(fd, &arr[i], 2);
	}
	
	for (i = 0; i < THR_MAX; ++i) {
		int* k1 = malloc(sizeof(int));
		int* k2 = malloc(sizeof(int));
		*k1 = i;
		*k2 = i;
		pthread_create(&cons[i], NULL, pf, k1);
		pthread_create(&prod[i], NULL, cf, k2);
	}

	for (i = 0; i < THR_MAX; ++i) {
		pthread_join(cons[i], NULL);
		pthread_join(prod[i], NULL);
	}

	printf("[MAIN]: The sum is %d\n", suma);
	close(fd);
	return EXIT_SUCCESS;
}
