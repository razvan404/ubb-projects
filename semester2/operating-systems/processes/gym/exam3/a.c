#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Invalid format!\n");
		printf(" Usage: ./a n\n");
		exit(-1);
	}
	int n = atoi(argv[1]);
	int p1[2], p2[2]; // pipe[0] - read, pipe[1] - write
	if (pipe(p1) == -1 || pipe(p2) == -1) {
		perror("pipe(): ");
		exit(-1);
	}
	int f1 = fork();

	if (f1 == -1) {
		perror("fork(): ");
		exit(-1);
	}

	if (f1 == 0) {
		// FIRST CHILD CASE
		close(p1[0]);
		srand(time(NULL));
		int freq[10], i = 0;
		for (i = 0; i < 10; ++i) {
			freq[i] = 0;
		}
		for (i = 0; i < n; ++i) {
			int x = rand() % 899 + 100;
			while (x) {
				freq[x % 10]++;
				x /= 10;
			}
		}
		for (i = 0; i < 10; ++i) {
			write(p1[1], &freq[i], sizeof(int));
		}
		close(p1[1]);
		exit(0);
	}
	
	int f2 = fork();
	
	if (f2 == -1) {
		perror("fork(): ");
		exit(-1);
	}

	if (f2 == 0) {
		// SECOND CHILD CASE
		close(p2[0]);
		srand(time(NULL));
		int freq[10], i = 0;
		for (i = 0; i < 10; ++i) {
			freq[i] = 0;
		}
		for (i = 0; i < n; ++i) {
			int x = rand() % 899 + 100;
			while (x) {
				freq[x % 10]++;
				x /= 10;
			}
		}
		
		for (i = 0; i < 10; ++i) {
			write(p2[1], &freq[i], sizeof(int));
		}
		close(p2[1]);
		exit(0);

	}

	// PARENT CASE
	
	wait(0);
	wait(0);
	close(p1[1]);
	close(p2[1]);
	int freq1[10], freq2[10], i = 0;
	for (; i < 10; ++i) {
		read(p1[0], &freq1[i], sizeof(int));
		read(p2[0], &freq2[i], sizeof(int));
		if (freq1[i] > freq2[i]) {
			printf("[CHILD %d] GOT THE MOST AT THE DIGIT %d (%d)\n", f1, i, freq1[i]);
		}
		else {
			printf("[CHILD %d] GOT THE MOST AT THE DIGIT %d (%d)\n", f2, i, freq2[i]);
		}
	}
	close(p1[0]);
	close(p2[0]);

	return EXIT_SUCCESS;
}
