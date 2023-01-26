#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int F = fork();
	if (F == -1) {
		perror("fork(): ");
		exit(EXIT_FAILURE);
	}
	else if (F == 0) {
		printf("[CHILD %d]: I become zombie!", getpid());
		exit(EXIT_SUCCESS);
	}
	else {
		printf("[PARENT %d]: Hello world!", getpid());
		while(1);
		wait(0);
	}
	return EXIT_SUCCESS;
}
