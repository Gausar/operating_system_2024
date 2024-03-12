#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

void *prime_numbers(void *t){
    int s = *((int*)t);
    int n = s + 100/100 - 1;
    if(s == 0){
        s = 2;
    }
    for(int i = s; i <= n; i++){
        bool prime = true;
        int k = floor(sqrt(i));
        if(i == 1){
            prime = false;
        }
        for(int j = 2; j <= k; j++){
            if(i % j == 0){
                prime = false;
                break;
            }
        }
        if(prime){
            printf("%d ", i);
        }
    }
    
    pthread_exit(NULL);
}
int main(){
    pthread_t threads[100];
    int thread_args[100];
    for(int i = 0; i < 100; i++){
        thread_args[i] = i; //*(100/100);
        pthread_create(&threads[i], NULL, prime_numbers, &thread_args[i]);
    }
    for(int i = 0; i < 100; i++){
        pthread_join(threads[i], NULL);
    }
    return 0;
}

//compile hiihdee gcc prime_num.c -o a -lm
//sqrt ni libm sand bna