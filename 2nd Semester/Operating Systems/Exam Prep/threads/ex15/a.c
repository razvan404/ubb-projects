#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define STR_MAX 256

typedef struct {
	int len;
	char* text;
} string;

int freq[3];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* f(void* a) {
	char* str = (char*)a;
	int i;
	for (i = 0; i < strlen(str); ++i) {
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
			pthread_mutex_lock(&mtx);
			freq[0]++;
			pthread_mutex_unlock(&mtx);
			continue;
		}
		if (str[i] >= '0' && str[i] <= '9') {
			pthread_mutex_lock(&mtx);
			freq[1]++;
			pthread_mutex_unlock(&mtx);
			continue;
		}
		pthread_mutex_lock(&mtx);
		freq[2]++;
		pthread_mutex_unlock(&mtx);
	}
	free(a);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Invalid syntax!\nUsage: %s string1 string2 ..\n", argv[0]);
		return EXIT_FAILURE;
	}
	int n = argc - 1, i;
	pthread_t thr[n];
	for (i = 0; i < n; ++i) {
		char* str = malloc(STR_MAX * sizeof(char));
		strcpy(str, argv[i + 1]);
		pthread_create(&thr[i], NULL, f, str);
	}

	for (i = 0; i < n; ++i) {
		pthread_join(thr[i], NULL);
	}

	printf("Total letters: %d\n", freq[0]);
	printf("Total digits: %d\n", freq[1]);
	printf("Total special characters: %d\n", freq[2]);

	return EXIT_SUCCESS;
}

