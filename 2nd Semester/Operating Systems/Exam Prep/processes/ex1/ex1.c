#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int n;
	printf("Number of processes: ");
	scanf("%d", &n);
	
	int f, i;
	int KIDS[n];

	for (i = 0; i < n; ++i) {
		f = fork();
		if (f == -1) {
			// FORK ERROR
			perror("fork()");
			exit(-1);
		}
		else if (f == 0) {
			// CHILD CASE
			printf("CHILD %d from PARENT %d\n", getpid(), getppid());
			exit(0);
		}
		else {
			KIDS[i] = f;
		}
	}
	for (i = 0; i < n; ++i) {
		wait(0);
	}
	
    printf("PARENT %d had the KIDS: ", getpid());
    for (i = 0; i < n - 1; ++i) {
		printf("%d, ", KIDS[i]);
	}
    printf("%d\n", KIDS[n - 1]);

	return EXIT_SUCCESS;
}
