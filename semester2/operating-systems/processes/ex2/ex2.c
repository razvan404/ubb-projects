#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int n, i, PID;
	printf("Give n: ");
	scanf("%d", &n);

	for (i = 0; i < n; ++i) {
		PID = fork();
		if (-1 == PID) {
			// ERROR ON FORK
			perror("fork()");
			exit(-1);
		}
		else if (0 == PID) {
			// CHILD CASE
			printf("CHILD %d FROM PARENT %d\n", getpid(), getppid());
		}
		else {
			wait(0);
			exit(0);
		}
	}
	return EXIT_SUCCESS;
}
