#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	// pipe[0] - read, pipe[1] - write
	int pip1[2], pip2[2];

	if (pipe(pip1) == -1) {
		perror("pipe(): ");
		exit(-1);
	}
	if (pipe(pip2) == -1) {
		perror("pipe(): ");
		exit(-1);
	}
	int f = fork();
	
	srand(getpid());

	if (f == -1) {
		// ERROR CASE
		perror("fork(): ");
		exit(-1);
	}

	if (f == 0) {
		// CHILD CASE
		close(pip1[0]);
		close(pip2[1]);

		int n = 0;
		while (n != 10) {
			n = rand() % 10 + 1;
			printf("[CHILD %d]: Sending the number %d\n", getpid(), n);
			if (write(pip1[1], &n, sizeof(int)) < 0) {
				perror("write(): ");
				exit(-1);
			}

			if (n == 10) {
				break;
			}

			if (read(pip2[0], &n, sizeof(int)) < 0) {
				perror("read(): ");
				exit(-1);
			}
			printf("[CHILD %d]: Got the number %d\n", getpid(), n);
		}
		close(pip1[1]);
		close(pip2[0]);
		exit(0);
	}
	
	// PARENT CASE
	close(pip1[1]);
	close(pip2[0]);

	int n = 0;
	while (n != 10) {
		if (read(pip1[0], &n, sizeof(int)) < 0) {
			perror("read(): ");
			exit(-1);
		}

		printf("[PARENT %d]: Got the number %d\n", getpid(), n);
		
		if (n == 10) {
			break;
		}

		n = rand() % 10 + 1;

		printf("[PARENT %d]: Sending the number %d\n", getpid(), n);

		if (write(pip2[1], &n, sizeof(int)) < 0) {
			perror("write(): ");
			exit(-1);
		}
	}

	wait(0);
	close(pip1[0]);
	close(pip2[1]);

	return EXIT_SUCCESS;
}
