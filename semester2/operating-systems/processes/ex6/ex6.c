#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int N;
	int fd[2]; // file descriptors, fd[0] - read, fd[1] - write
	int F; // proc
	
	if (pipe(fd) == -1) {
		perror("pipe(): ");
		exit(EXIT_FAILURE);
	}

	printf("Give N: ");
	scanf("%d", &N);
	
	int a[N], i;
	for (i = 0; i < N; ++i) {
		a[i] = rand();
	}

	F = fork();

	if (F == -1) {
		perror("fork(): ");
		exit(EXIT_FAILURE);
	}
	if (F == 0) {
		close(fd[0]);
		double avg = 0;
		for (i = 0; i < N; ++i) {
			avg += a[i];
		}
		write(fd[0]);
	}

	return EXIT_SUCCESS; 
}
