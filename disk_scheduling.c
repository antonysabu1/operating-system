#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int range, req, requests[50], head;

void fcfs();
void scan();
void cscan();
void sort(int *arr, int size, int mode);
void seektimeFinder(int *arr, int max);

int main() {
    printf("\nEnter the max range of the disk: ");
    scanf("%d", &range);

    printf("\nEnter the number of requests: ");
    scanf("%d", &req);

    printf("\nEnter the disk positions to be read\n");
    for (int i = 1; i <= req; i++) {
        scanf("%d", &requests[i]);
    }

    printf("\nEnter the initial head position: ");
    scanf("%d", &head);

    int choice = 0;
    while (choice != 4) {
        printf("\n1. FCFS\n2. SCAN\n3. C-SCAN\n4. Exit\nEnter a choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fcfs();
                break;
            case 2:
                scan();
                break;
            case 3:
                cscan();
                break;
            case 4:
                break;
            default:
                printf("\nInvalid choice...");
        }
    }
    return 0;
}

void seektimeFinder(int *arr, int max) {
    int seek = 0, diff = 0;
    for (int i = 0; i < max - 1; i++) {
        diff = abs(arr[i + 1] - arr[i]);
        seek += diff;
        printf("\nDisk head moves from %d to %d with seek time %d", arr[i], arr[i + 1], diff);
    }
    printf("\n\nTotal seek time: %d", seek);
}

// First Come First Serve
void fcfs() {
    requests[0] = head;
    seektimeFinder(requests, req + 1);
}

// SCAN (Elevator Algorithm)
void scan() {
    int q1[20], q2[20], k1 = 0, k2 = 0, queue[50], t1 = 0;

    for (int i = 1; i <= req; i++) {
        if (requests[i] > head) {
            q2[k2++] = requests[i];
        } else {
            q1[k1++] = requests[i];
        }
    }

    sort(q2, k2, 1); // Ascending
    sort(q1, k1, 2); // Descending

    queue[t1++] = head;
    for (int i = 0; i < k2; i++)
        queue[t1++] = q2[i];
    
    queue[t1++] = range; // Go to the end
    for (int i = 0; i < k1; i++)
        queue[t1++] = q1[i];

    seektimeFinder(queue, t1);
}

// C-SCAN (Circular SCAN)
void cscan() {
    int q1[20], q2[20], k1 = 0, k2 = 0, queue[50], t1 = 0;

    for (int i = 1; i <= req; i++) {
        if (requests[i] > head) {
            q2[k2++] = requests[i];
        } else {
            q1[k1++] = requests[i];
        }
    }

    sort(q2, k2, 1); // Ascending
    sort(q1, k1, 1); // Ascending

    queue[t1++] = head;
    for (int i = 0; i < k2; i++)
        queue[t1++] = q2[i];

    queue[t1++] = range; // Go to end
    queue[t1++] = 0;     // Jump to start

    for (int i = 0; i < k1; i++)
        queue[t1++] = q1[i];

    seektimeFinder(queue, t1);
}

// Bubble Sort based on mode (1 = ascending, 2 = descending)
void sort(int *arr, int size, int mode) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (mode == 1 ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
