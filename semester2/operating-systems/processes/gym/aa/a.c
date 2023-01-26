#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
    fork();
    wait(0);
    fork();
    wait(0);
    fork();

    sleep(5);

    return 0;
}
