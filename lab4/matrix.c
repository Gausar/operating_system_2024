#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct matrix{
    int row;
    int col;
    int (*a)[3];
    int (*b)[3];
    int (*res)[3];
};

void *mult_matrix(void *t){
    struct matrix *data = (struct matrix *)t;
    int sum = 0;
    for(int k = 0; k < 3; k++){
        sum += data->a[data->row][k] * data->b[k][data->col];
    }
    data->res[data->row][data->col] = sum;
    pthread_exit(NULL);
}

int main(){
    int a[3][3] = {{1, 2, 1},
                   {3, 2, 1},
                   {2, 3, 1}};
    int b[3][3] = {{1, 1, 1},
                   {2, 1, 1},
                   {1, 2, 3}};
    int c[3][3];
    /*
    |1 2 1|     |1 1 1|     |6 5 6|
    |3 2 1|  *  |2 1 1| =   |8 7 8|
    |2 3 1|     |1 2 3|     |9 7 8|
    */

    pthread_t threads[9];
    struct matrix mat_arr[9];
    int thread_idx = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mat_arr[thread_idx].row = i;
            mat_arr[thread_idx].col = j;
            mat_arr[thread_idx].a = a;
            mat_arr[thread_idx].b = b;
            mat_arr[thread_idx].res = c;

            pthread_create(&threads[thread_idx], NULL, mult_matrix, (void *)&mat_arr[thread_idx]);
            thread_idx++;
        }
    }

    for(int i = 0; i < 9; i++){
        pthread_join(threads[i], NULL);
    }
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}