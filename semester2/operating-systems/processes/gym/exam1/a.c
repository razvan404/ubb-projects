#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int pip[2]; // pip[0] - read, pip[1] - write
	if (pipe(pip) == -1) {
		perror("pipe(): ");
		return EXIT_FAILURE;
	}

	int f = fork();

	if (f == -1) {
		// ERROR CASE
		perror("fork(): ");
		return EXIT_FAILURE;
	}

	if (f == 0) {
		// CHILD CASE
		close(pip[1]);
		int p;
		read(pip[0], &p, sizeof(int));

		char s[200];

		while (strcmp(s, "stop") != 0) {
			int len;
			read(pip[0], &len, sizeof(int));
			read(pip[0], s, len * sizeof(char));
			s[len] = '\0';

			if (strcmp(s, "stop") != 0) {
				if (p < len) {
					s[p] = 'X';
				}
				printf("[CHILD]: %s\n", s);
			}
		}
		close(pip[0]);
		exit(0);
	}
	
	// PARENT CASE
	int p;
	printf("[PARENT]: Give p (0..10): ");
	scanf("%d", &p);
	if (p < 0 || p > 10) {
		perror("Invalid number!");
		return EXIT_FAILURE;
	}
	close(pip[0]);
	write(pip[1], &p, sizeof(int));

	char s[200];

	while (strcmp(s, "stop") != 0) {
		printf("[PARENT]: Give a word: ");
		scanf("%s", s);
		
		int len = strlen(s) + 1;
		write(pip[1], &len, sizeof(int));
		write(pip[1], s, len * sizeof(char));
		sleep(1);
	}

	close(pip[1]);
	wait(0);

	return EXIT_SUCCESS;
}
