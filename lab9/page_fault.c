#include<stdio.h>

int fifo_page_fault(int string[20], int n, int size){
    printf("FIFO algorithm :");
    int frames[n];
    for(int i = 0; i < n; i++){
        frames[i] = -1;
    }
    int index = -1;
    int page_fault = 0;
    int page1[20], page2[20], page3[20];
    for(int i = 0; i < size; i++){
        int symbol = string[i];
        int flag = 0;
        for(int j = 0; j < n; j++){
            if(symbol == frames[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            printf("\n");
            for(int j = 0; j < n; j++){
                printf("%d\t", frames[j]);
            }
        }
        else{
            index = (index + 1) % n;
            frames[index] = symbol;
            page_fault += 1;
            printf("\n");
            for(int j = 0; j < n; j++){
                printf("%d\t", frames[j]);
            }
        }
    }
    printf("\nPage Fault = %d\n", page_fault);
}
void optimal_page_fault(int string[20], int n, int size){
    printf("Optimal algorithm :");

    int flag1, flag2, flag3, position, max, faults = 0;
    int i, j, k;
    int frames[n];
    int temp[n];

    for(i = 0; i < n; i++){
        frames[i] = -1;
    }

    for(i = 0; i < size; i++){
        flag1 = flag2 = 0;
        for(j = 0; j < n; j++){
            if(frames[j] == string[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }
        if(flag1 == 0){
            for(j = 0; j < n; j++){
                if(frames[j] == -1){
                    faults++;
                    frames[j] = string[i];
                    flag2 = 1;
                    break;
                }
            }    
        }
        if(flag2 == 0){
            flag3 =0;
            for(j = 0; j < n; j++){
                temp[j] = -1;

                for(k = i + 1; k < size; k++){
                    if(frames[j] == string[k]){
                        temp[j] = k;
                        break;
                    }
                }
            }
            for(j = 0; j < n; j++){
                if(temp[j] == -1){
                    position = j;
                    flag3 = 1;
                    break;
                }
            }
            if(flag3 ==0){
                max = temp[0];
                position = 0;

                for(j = 1; j < n; j++){
                    if(temp[j] > max){
                        max = temp[j];
                        position = j;
                    }
                }               
            }
            frames[position] = string[i];
            faults++;
        }
        printf("\n");

        for(j = 0; j < n; j++){
            printf("%d\t", frames[j]);
        }
    }
    printf("\nPage Faults = %d", faults);
}

int lru_page_fault(int pages[20], int n, int size){
    printf("\nLRU algorithm : \n");
    int m, p, position, k, l;
    int a = 0, b = 0, page_fault = 0;
    int frames[n];
    int temp[n];

    for(m = 0; m < n; m++){
            frames[m] = -1;
    }
    for(p = 0; p < size; p++){
            a = 0, b = 0;
            for(m = 0; m < n; m++){
                if(frames[m] == pages[p]){
                        a = 1;
                        b = 1;
                        break;
                }
            }
            if(a == 0){
                for(m = 0; m < n; m++){
                    if(frames[m] == -1)
                    {
                        frames[m] = pages[p];
                        b = 1;
                        page_fault++;
                        break;
                    }
                }
            }
            if(b == 0){
                for(m = 0; m < n; m++){
                    temp[m] = 0;
                }
                for(k = p - 1, l = 1; l <= n - 1; l++, k--){
                    for(m = 0; m < n; m++){
                        if(frames[m] == pages[k]){
                            temp[m] = 1;
                        }
                    }
                }
                for(m = 0; m < n; m++){
                    if(temp[m] == 0)
                        position = m;
                }
                frames[position] = pages[p];
                page_fault++;
            }
            for(m = 0; m < n; m++){
                printf("%d\t", frames[m]);
            }
            printf("\n");
    }
    printf("Page Faults = %d\n", page_fault);

}

int main(){
    int string[] = {1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2, 5, 6, 5};
    int frames = 4;
    int size = sizeof(string)/sizeof(int);
    fifo_page_fault(string, frames, size);
    optimal_page_fault(string, frames, size);
    lru_page_fault(string, frames, size);
    return 0;
}