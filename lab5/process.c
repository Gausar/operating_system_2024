#include<stdio.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        fork();
        printf("Amjilt ");
    }
    fork();
}