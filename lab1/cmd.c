#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>

void direct(const char *command) {
    DIR* dirp = NULL;
    size_t path_len;
    struct dirent *direntp = NULL;
    char datestring[256];
    struct stat filestat;

    if(strcmp(command, "dir") == 0){
        dirp = opendir(".");
        if(dirp == NULL){
            perror("Aldaa garlaa");
            exit(0);
        }
        while ((direntp = readdir(dirp)) != NULL){
            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", ".", direntp->d_name);
            if (stat(fullpath, &filestat) == -1) {
                perror("Aldaa 2");
                exit(EXIT_FAILURE);
            }
            strftime(datestring, sizeof(datestring), "%m/%d/%Y %I:%M:%p", localtime(&filestat.st_mtime));
                
            printf("%s\t<DIR>\t\t%s\n", datestring, direntp->d_name);
        }
    }
    closedir(dirp);
}

void create_file(const char *command, const char *file_name){
    if(strcmp(command, "create") == 0){
        FILE *file = fopen(file_name, "w");
        printf("File amjilttai uuslee\n");
        fclose(file);
    }
    if(strcmp(command, "del") == 0){
        if(remove(file_name) == 0){
            printf("Amjilttai ustgalaa\n");
        }
        else{
            printf("file ustgaj chadsangui\n");
        }
    }
    if(strcmp(command, "cd") == 0){
        const char *path = file_name;
        if (chdir(path) == 0) {
            printf("Directory amjilttai soligdloo.\n");
        } 
        else {
            perror("path solih bolomjgui\n");
            exit(EXIT_FAILURE);
        }
    }
}
void rename_file(const char *command, const char *old_name, const char * new_name){
    if(rename(old_name, new_name) == 0){
        printf("Ner ni amjilttai soligdloo\n");
    }
    else{
        printf("%s ner ni soligdoh bolomjgui\n", old_name);
    }
}
void input_file(const char *file_name, char *sentence[]){
    FILE *file = fopen(file_name, "a");
    if (file == NULL) {
        perror("aldaa 5");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (sentence[i] != NULL) {
        fprintf(file, "%s ", sentence[i]);
        i++;
    }
    printf("Amjilttai bichlee\n");
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr,"aldaa", argv[0]);
        exit(EXIT_FAILURE);
    }
    if(argc == 2){
        direct(argv[1]);
    }
    if(argc == 3){
        create_file(argv[1],argv[2]);
    }
    if(argc >= 4){
        char text[1000];
        char *command = argv[1];
        
        if(strcmp(command, "rename") == 0){
            rename_file(argv[1], argv[2], argv[3]);
        }
        if(strcmp(command, "input") == 0){
            input_file(argv[2], &argv[3]);
        }
    }

    return 0;
}
