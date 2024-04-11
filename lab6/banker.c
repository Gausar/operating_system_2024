#include<stdio.h>
#include<stdlib.h>

int main()
{
     /*Process name	Allocation	    Max	    Available
        Instances	A, B, C, D	A, B, C, D	A, B, C, D
        P0	        0, 0, 1, 2	0, 0, 1, 2	1, 5, 2, 0
        P1	        1, 0, 0, 0	1, 7, 5, 0	 
        P2	        1, 3, 5, 4	2, 3, 5 ,6	 
        P3	        0, 6, 3, 2 	0, 6, 5, 2	 
        P4	        0, 0, 1, 4	0, 6 ,5, 6	 */
 
    int n, m, i, j, k;
    n = 5; // Number of processes
    m = 4; // Number of resources

    // Allocation Matrix
    int allocation[5][4] = { { 0, 0, 1, 2 }, // P0    
                        { 1, 0, 0, 0 }, // P1
                        { 1, 3, 5, 4 }, // P2
                        { 0, 6, 3, 2 }, // P3
                        { 0, 0, 1, 4 } }; // P4

    // MAX Matrix
    int max[5][4] = { { 0, 0, 1, 2 }, // P0    
                      { 1, 7, 5, 0 }, // P1
                      { 2, 3, 5, 6 }, // P2
                      { 0, 6, 5, 2 }, // P3
                      { 0, 5, 5, 6 } }; // P4
 
    int available[4] = { 1, 5, 2, 0}; // Available Resource
 
    int f[n], answer[n], ind = 0;
    for(k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
    printf("Need matrix : \n");
    printf("----------------------\n");
    printf("|    | A | B | C | D |\n");
    printf("----------------------\n");
    for(i = 0; i < n; i++){
        printf("| P%d |", i);
        for(j = 0; j < m; j++){
            printf(" %d |", need[i][j]);
        }
        printf("\n");
        printf("----------------------\n");
    }
    // need[1][0] = 0;
    // need[1][1] = 4;
    // need[1][2] = 2;
    // need[1][3] = 0;
    int y = 0;
    for(k = 0; k < 5; k++) {
        for(i = 0; i < n; i++) {
            if(f[i] == 0) {
 
                int flag = 0;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > available[j]){
                        flag = 1;
                        break;
                    }
                }
 
                if(flag == 0) {
                    answer[ind++] = i;
                    for(y = 0; y < m; y++){
                        available[y] += allocation[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }
   
    int flag = 1;
    for(int i = 0; i < n; i++){
        if(f[i] == 0){
            flag = 0;
            printf("deadlock uusne");
            break;
        }
    }
    if(flag == 1){
        printf("Safe daraalal :\n");
        for(i = 0; i < n - 1; i++){
            printf(" P%d ->", answer[i]);
        }
        printf(" P%d", answer[n - 1]);
    }
    printf("\n");
    return (0);
}