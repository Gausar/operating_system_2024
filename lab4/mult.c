#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define COL 3
#define ROW 3

int a[ROW][COL] = {{1, 2, 1}, {3, 2, 1}, {2, 3, 1}};
int b[ROW][COL] = {{1, 1, 1}, {2, 1, 1}, {1, 2, 3}};
int c[ROW][COL] = {0}; /*
                |1 2 1|     |1 1 1|     |6 5 6|
                |3 2 1|  *  |2 1 1| =   |8 7 8|
                |2 3 1|     |1 2 3|     |9 7 8|
                */
struct matrix{
    int row;
    int col;
};

void *mult_matrix(void *t){
    struct matrix *params = (struct matrix *)t;
    int d = params->row;
    int e = params->col;

    for(int k = 0; k < COL; k++){
        c[d][e] += a[d][k] * b[k][e];
    }
    printf("c[%d][%d] = %d\n", d, e, c[d][e]);
    return NULL;
}

int main(){
    pthread_t id;

    struct matrix res;
    scanf("%d", &res.row);
    scanf("%d", &res.col);

    pthread_create(&id, NULL, mult_matrix, (void *)&res);
    pthread_join(id, NULL); 

    return 0;
}
