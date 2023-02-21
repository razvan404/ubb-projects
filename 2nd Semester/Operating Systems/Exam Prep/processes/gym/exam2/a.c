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
		exit(-1);
	}

	int f = fork();
	if (f == -1) {
		perror("fork(): ");
		exit(-1);
	}

	if (f == 0) {
		// CHILD CASE
		close(pip[1]);
		char c;
		read(pip[0], &c, sizeof(char));
		char s[320];

		do {
			int len;
			read(pip[0], &len, sizeof(int));
			read(pip[0], s, len * sizeof(int));
			s[len] = '\0';
			if (strcmp(s, "stop") != 0) {
				int i = 0;
				for (; i < len; ++i) {
					if (s[i] == c) {
						printf("[CHILD] Found the letter %c at position %d\n", c, i);
						break;
					}
				}
				if (i == len) {
					printf("[CHILD] Couldn't find the letter %c!\n", c);
				}
			}

		} while (strcmp(s, "stop") != 0);

		close(pip[0]);
		exit(0);
	}
	// PARENT CASE
	printf("[PARENT] Give a character: ");
	char c;
	scanf("%c", &c);
	close(pip[0]);
	write(pip[1], &c, sizeof(char));
	char s[320];

	do {
		printf("[PARENT] Give a string: ");
		scanf("%s", s);
		int len = strlen(s) + 1;
		write(pip[1], &len, sizeof(int));
		write(pip[1], s, len * sizeof(int));
		sleep(1);

	} while (strcmp(s, "stop") != 0);
	close(pip[1]);
	wait(0);

	return EXIT_SUCCESS;
}
