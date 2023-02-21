#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int PID;

void f(int sgn) {
	if (PID != 0) {
		kill(PID, SIGUSR1);
		wait(0);
	}
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
	signal(SIGUSR1, f);

	PID = fork();
	
	if (PID == -1) {
		perror("fork(): ");
		exit(EXIT_FAILURE);
	}
	
	while (1) {
		if (PID == 0) {
			printf("[CHILD %d]: working...\n", getpid());
			sleep(3);
		}
		else {
			printf("[PARENT %d]: working...\n", getpid());
			sleep(3);
		}
	}

	return EXIT_SUCCESS;
}

