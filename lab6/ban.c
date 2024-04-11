#include<stdio.h>
#include<stdlib.h>

void deadlockCheck(int n, int m, int allocation[][m], int max[][m], int available[], int need[][m]) {
    int f[n], answer[n], ind = 0;
    int k;
    for(k = 0; k < n; k++) {
        f[k] = 0;
    }
    for(k = 0; k < 5; k++) {
        for(int i = 0; i < n; i++) {
            if(f[i] == 0) {
                int flag = 0;
                for(int j = 0; j < m; j++) {
                    if(need[i][j] > available[j]){
                        flag = 1;
                        break;
                    }
                }
 
                if(flag == 0) {
                    answer[ind++] = i;
                    for(int y = 0; y < m; y++){
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
            printf("deadlock uusne\n");
            break;
        }
    }
    if(flag == 1){
        printf("Safe daraalal :\n");
        for(int i = 0; i < n - 1; i++){
            printf(" P%d ->", answer[i]);
        }
        printf(" P%d\n", answer[n - 1]);
    }
    printf("\n");
}

int main() {
    int n, m, i, j;
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
 
    int available[4] = { 1, 5, 2, 0}; // Available Resources

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

    deadlockCheck(n, m, allocation, max, available, need);

    printf(" P1 process Need(0,4,2,0) bol : \n");

    need[1][0] = 0;
    need[1][1] = 4;
    need[1][2] = 2;
    need[1][3] = 0;

    deadlockCheck(n, m, allocation, max, available, need);
    
    return (0);
} 
