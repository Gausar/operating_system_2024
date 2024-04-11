#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

void *fork_file(void *t) {
    int a = *((int*)t);
    printf("%d\n", a+1);
    return NULL;
}

int main() {
    pid_t pid;
    int res = 1;
    pid = fork();
    if (pid == 0) {
        //fork();
        //printf("amjilt\n");
        pthread_t id;
        pthread_create(&id, NULL, fork_file, (void *)&res);
        pthread_join(id, NULL); 
    }
    fork();
    return 0;
}
