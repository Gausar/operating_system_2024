#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LEFT 0
#define RIGHT 1
#define LOWER_CYLINDER 0
#define UPPER_CYLINDER 4999


void FCFS(int *requests, int initialPos, int n) {
    int position = initialPos;
    int movement = 0;

    for (int i = 0; i < n; ++i) {
        movement += abs(position - requests[i]);
        position = requests[i];
    }
    printf("FCFS = %d\n", movement);
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int SSTF(int *requests, int initialPos, int n) {
    int *localRequests = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        localRequests[i] = requests[i];
    }

    int position = initialPos;
    int movement = 0;
    int remaining = n;

    while (remaining > 0) {
        int closestIndex = -1;
        int minDistance = 1e9;
        for (int i = 0; i < n; ++i) {
            if (localRequests[i] != -1 && abs(position - localRequests[i]) < minDistance) {
                minDistance = abs(position - localRequests[i]);
                closestIndex = i;
            }
        }
        if (closestIndex != -1) {
            movement += abs(position - localRequests[closestIndex]);
            position = localRequests[closestIndex];
            localRequests[closestIndex] = -1;
            remaining--;
        }
    }
    free(localRequests);
    printf("SSTF = %d\n", movement);
}

int SCAN(int *requests, int n, int initialPos, int direction) {
    int *localRequests = malloc((n + 2) * sizeof(int));
    for (int i = 0; i < n; ++i) {
        localRequests[i] = requests[i];
    }
    localRequests[n] = UPPER_CYLINDER;
    localRequests[n + 1] = LOWER_CYLINDER;
    qsort(localRequests, n + 2, sizeof(int), compare);

    int position = initialPos;
    int movement = 0;
    int index = 0;
    while (index < n + 2 && localRequests[index] < position) {
        index++;
    }

    if (direction == RIGHT) {
        for (int i = index; i < n + 2; ++i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
        for (int i = index - 1; i >= 0; --i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
    } else {
        for (int i = index - 1; i >= 0; --i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
        for (int i = index; i < n + 2; ++i) {
            movement += abs(position - localRequests[i]);
            position = localRequests[i];
        }
    }
    free(localRequests);
    printf("SCAN = %d\n", movement);
}

int C_SCAN(int *requests, int initialPos, int n) {
    int *localRequests = malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; ++i) {
        localRequests[i] = requests[i];
    }
    localRequests[n] = UPPER_CYLINDER;
    qsort(localRequests, n + 1, sizeof(int), compare);

    int position = initialPos;
    int movement = 0;
    int index = 0;
    while (index < n + 1 && localRequests[index] < position) {
        index++;
    }

    for (int i = index; i < n + 1; ++i) {
        movement += abs(position - localRequests[i]);
        position = localRequests[i];
    }
    movement += abs(UPPER_CYLINDER - LOWER_CYLINDER);
    position = LOWER_CYLINDER;
    for (int i = 0; i < index; ++i) {
        movement += abs(position - localRequests[i]);
        position = localRequests[i];
    }
    free(localRequests);
    printf("C-SCAN = %d\n", movement);
}

int main() {
    // srand(time(0));
    // for (int i = 0; i < 1000; ++i) {
    //     requests[i] = rand() % 5000;
    // }
    int requests[10] = {2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681};
    int head_position;
    /*while (1) {
        printf("Enter initial position: ");
        scanf("%d", &head_position);

        FCFS(requests, head_position, 1000);
        SSTF(requests, head_position, 1000);
        SCAN(requests, 1000, head_position, RIGHT);
        C_SCAN(requests, head_position, 1000);
    }*/
    head_position = 2150;
    C_SCAN(requests, head_position, 10);
    SCAN(requests, 10, head_position, RIGHT);
    FCFS(requests, head_position, 10);
    SSTF(requests, head_position, 10);
    return 0;
}
