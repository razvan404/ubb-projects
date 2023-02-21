#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THR_NUM 60

pthread_mutex_t a, b;
int n = 0;

void* fa(void* p) {
    pthread_mutex_lock(&a);
    n++;
    pthread_mutex_unlock(&a);
    pthread_exit(EXIT_SUCCESS);
}

void* fb(void* p) {
    pthread_mutex_lock(&b);
    n++;
    pthread_mutex_unlock(&b);
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    pthread_t thr[THR_NUM];
    int i;
    
    pthread_mutex_init(&a, NULL);
    pthread_mutex_init(&b, NULL);

    for (i = 0; i < THR_NUM / 2; ++i) {
        pthread_create(&thr[2 * i], NULL, fa, NULL);
        pthread_create(&thr[2 * i + 1], NULL, fb, NULL);
    }

    for (i = 0; i < THR_NUM; ++i) {
        pthread_join(thr[i], NULL);
    }

    printf("Value of n: %d\n", n);

    pthread_mutex_destroy(&a);
    pthread_mutex_destroy(&b);

    return EXIT_SUCCESS;
}
