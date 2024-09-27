#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FCFS(int *disk_request, int head_position, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int request_tsilindr = disk_request[i];
        sum += abs(request_tsilindr - head_position);
        head_position = request_tsilindr;
    }
    printf("FCFS : %d\n", sum);
}

void difference(int *request, int head, int diff[][2], int n) {
    for (int i = 0; i < n; i++) {
        diff[i][0] = abs(head - request[i]);
    }
}

int findMIN(int diff[][2], int n) {
    int index = -1;
    int minimum = 1e9;

    for (int i = 0; i < n; i++) {
        if (!diff[i][1] && minimum > diff[i][0]) {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

void SSTF(int *request, int head, int n) {
    if (n == 0) {
        return;
    }
    int (*diff)[2] = malloc(n * sizeof(*diff));

    int seekcount = 0;
    int *seeksequence = malloc((n + 1) * sizeof(*seeksequence));

    for (int i = 0; i < n; i++) {
        seeksequence[i] = head;
        difference(request, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1;
        seekcount += diff[index][0];
        head = request[index];
    }
    seeksequence[n] = head;
    printf("SSTF : %d\n", seekcount);
}

void SCAN(int *request, int head, int n) {
    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (request[j] > request[j + 1]) {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }
    int start_index = 0;
    while (start_index < n && request[start_index] < head) {
        start_index++;
    }

    int index = start_index;
    while (index < n) {
        sum += abs(request[index] - head);
        head = request[index];
        index++;
    }

    index = start_index - 1;
    if (index >= 0) {
        sum += abs(request[index + 1] - request[start_index - 1]);
    }
    while (index >= 0) {
        sum += abs(request[index] - head);
        head = request[index];
        index--;
    }

    printf("SCAN : %d\n", sum);
}


void CSCAN(int *request, int head, int n) {
    int *sorted_request = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        sorted_request[i] = request[i];
    }

    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted_request[j] > sorted_request[j + 1]) {
                int temp = sorted_request[j];
                sorted_request[j] = sorted_request[j + 1];
                sorted_request[j + 1] = temp;
            }
        }
    }

    int start_index = 0;
    int end_index = n - 1;
    while (start_index < n && sorted_request[start_index] < head) {
        start_index++;
    }
    int direction = 1;
    int idx = start_index;
    while (idx >= 0 && idx < n) {
        sum += abs(sorted_request[idx] - head);
        head = sorted_request[idx];
        idx += direction;
    }
    if (direction == 1) {
        sum += abs(sorted_request[end_index] - 5000);
        sum += 5000; 
        sum += sorted_request[0];
    } else {
        sum += abs(sorted_request[start_index] - 0);
        sum += 5000; 
        sum += abs(sorted_request[end_index] - sorted_request[n - 1]);
    }
    printf("CSCAN : %d\n", sum);

}

int main() {
    srand(time(NULL));
    int *disk_request = malloc(1000 * sizeof(int));

    for (int i = 0; i < 1000; i++) {
        disk_request[i] = rand() % 5000;
    }

    while (1) {
        int head_position;
        printf("Enter head position: ");
        scanf("%d", &head_position);

        FCFS(disk_request, head_position, 1000);
        SSTF(disk_request, head_position, 1000);
        SCAN(disk_request, head_position, 1000);
        CSCAN(disk_request, head_position, 1000);
    }

    free(disk_request);
    return 0;
}
