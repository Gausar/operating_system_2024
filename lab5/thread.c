#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
  
pthread_t tid[2]; 
int counter;
pthread_mutex_t lock;
  
void* thread_func(void *arg) 
{ 
    pthread_mutex_lock(&lock);
    unsigned long i = 0; 
    counter += 1; 
    printf("Thread %d has started\n", counter); 
  
    for(i=0; i<(0xFFFFFFFF);i++); 
    printf("Thread %d has finished\n", counter); 
    pthread_mutex_unlock(&lock);
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
    int k;
    k = pthread_mutex_init(&lock, NULL);
    if(k != 0){
        printf("\nmutex init failed\n");
        return 1;
    }
    while(i < 2) 
    { 
        error = pthread_create(&(tid[i]), NULL, &thread_func, NULL); 
        if (error != 0) 
            printf("\nThread can't be created : [%s]", strerror(error)); 
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_mutex_destroy(&lock);
  
    return 0; 
}