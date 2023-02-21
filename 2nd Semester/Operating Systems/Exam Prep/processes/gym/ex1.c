#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int f = fork();
	if (f == -1) {
		// FORK ERROR
		perror("fork()");
		exit(-1);
	}
	else if (f == 0) {
		// CHILD CASE
		printf("[CHILD %d -> PARENT %d]: Hello, I'm here!\n", getpid(), getppid());
		sleep(15);
		exit(0);
	}
	else {
		// PARENT CASE
		wait(0);
		printf("[PARENT %d -> CHILD %d]: Hello, I can hear you!\n", getpid(), getppid());
	}
	return EXIT_SUCCESS;
}
