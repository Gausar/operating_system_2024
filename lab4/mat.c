#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define COL 3
#define ROW 3
#define THREAD_NUM 9
int step = 0;

int a[ROW][COL] = {{1, 2, 1}, {3, 2, 1}, {2, 3, 1}};;
int b[ROW][COL] = {{1, 1, 1}, {2, 1, 1}, {1, 2, 3}};
int c[ROW][COL]; /*
                |1 2 1|     |1 1 1|     |6 5 6|
                |3 2 1|  *  |2 1 1| =   |8 7 8|
                |2 3 1|     |1 2 3|     |9 7 8|
                */

void *mult_matrix(void *t){
    int i = step++;
    for(int j = 0; j < ROW; j++){
        for(int k = 0; k < COL; k++){
            c[i][j] += a[i][k] * b[k][j];
        }
    }
}

int main(){
    printf("matrix a: \n");
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("matrix b: \n");
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    int d, e;
    scanf("%d %d", &d, &e);

    pthread_t threads[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++){
        int *p;
        pthread_create(&threads[i], NULL, mult_matrix, (void *)(p));
    }
    
    for(int i = 0; i < THREAD_NUM; i++){
        pthread_join(threads[i], NULL);
    }
    printf("c[%d][%d] = %d\n",d, e, c[d][e]);
    return 0;
}