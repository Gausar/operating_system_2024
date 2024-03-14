#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

void *prime_numbers(void *t) {
    int *num = (int *)t;
    int n = *num;
    int prime = 1;
    int k = floor(sqrt(n)); 
    for (int j = 2; j <= k; j++) {
        if (n % j == 0) {
            prime = 0;
            //printf("%d zohiomol too\n", n);
            break;
        }
    }
    if (prime) {
        printf("%d ", n);
    }
    pthread_exit(NULL);
}

int main() {
    int thread_num = 100;
    pthread_t tid[thread_num];

    for (int count = 2; count <= thread_num; count++) {
        int *arg = malloc(sizeof(*arg));
        *arg = count; 
        pthread_create(&tid[count], NULL, prime_numbers, arg);
        pthread_join(tid[count], NULL);
        free(arg);
    }
    printf("\n");
    return 0;
}
