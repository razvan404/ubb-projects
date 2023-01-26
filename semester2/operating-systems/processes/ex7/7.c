/*
 * Write a C program that creates two child processes. The two child processes will 
 * alternate sending random integers between 1 and 10(inclusively) to one another 
 * until one of them sends the number 10. Print messages as the numbers are sent.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    int p_to_c[2], c_to_p[2];
    if(-1 == pipe(p_to_c)) {
        perror("Error on first pipe");
        exit(1);
    }
    if(-1 == pipe(c_to_p)) {
        perror("Error on second pipe");
        exit(1);
    }
    int f = fork();
    if(-1 == f) {
        perror("Eroare on fork");
    } else if (0 == f) {
        close(p_to_c[1]);
        close(c_to_p[0]);
        int n;
        srandom(getpid());
        if(0 > read(p_to_c[0], &n, sizeof(int))) {
            perror("Error on read number from pipe from parent");
        }
        printf("Child process read %d\n", n);
        while(n != 10) {
            n = random() % 10 + 1;
            if(0 > write(c_to_p[1], &n, sizeof(int))) {
                perror("Error on write in pipe to parent");
            }
            if(n == 10) {
                break;
            }
            if(0 > read(p_to_c[0], &n, sizeof(int))) {
                perror("Error on read number from pipe from parent");
            }
            printf("Child process read %d\n", n);
        }
        close(p_to_c[0]);
        close(c_to_p[1]);
        exit(0);
    } else {
        close(p_to_c[0]);
        close(c_to_p[1]);
        int n = 0;
        srandom(getpid());
        while(n != 10) {
            n = random() % 10 + 1;
            if(0 > write(p_to_c[1], &n, sizeof(int))) {
                perror("Error on write in pipe to child");
            }
            if(n == 10) {
                break;
            }
            if(0 > read(c_to_p[0], &n, sizeof(int))) {
                perror("Error on read from pipe from child");
            }
            printf("Parent process read %d\n", n);
        }
        wait(0);
        close(p_to_c[1]);
        close(c_to_p[0]);
    }

    return 0;
}
