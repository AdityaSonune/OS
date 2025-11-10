#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int a[], int n) {
    int i, j, temp;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void SSTF(int req[], int n, int head) {
    int completed[n];
    int count = 0, pos = head, i, total = 0;
    for(i = 0; i < n; i++)
        completed[i] = 0;

    printf("\nSSTF order: ");
    while(count < n) {
        int min = 9999, index = -1;
        for(i = 0; i < n; i++) {
            if(!completed[i] && abs(req[i] - pos) < min) {
                min = abs(req[i] - pos);
                index = i;
            }
        }
        total += abs(req[index] - pos);
        pos = req[index];
        completed[index] = 1;
        count++;
        printf("%d ", pos);
    }
    printf("\nTotal head movement (SSTF): %d\n", total);
}

void SCAN(int req[], int n, int head, int disk_size) {
    int arr[n+1], i, pos = head, total = 0, idx = 0;

    // Copy requests
    for(i = 0; i < n; i++) arr[i] = req[i];
    arr[n] = head;
    sort(arr, n+1);

    // Find head index
    for(i = 0; i < n+1; i++) if(arr[i] == head) { idx = i; break; }

    printf("\nSCAN order: ");
    // Moving towards higher tracks
    for(i = idx; i < n+1; i++) {
        printf("%d ", arr[i]);
        if(i > idx) total += abs(arr[i] - arr[i-1]);
    }
    // Go to disk end
    total += abs((disk_size - 1) - arr[n]);
    printf("%d ", disk_size - 1);

    // Move backward
    for(i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
        if(i < n - 1) total += abs(arr[i] - arr[i+1]);
    }

    printf("\nTotal head movement (SCAN): %d\n", total);
}

void CLOOK(int req[], int n, int head) {
    int arr[n+1], i, idx = 0, total = 0;

    for(i = 0; i < n; i++) arr[i] = req[i];
    arr[n] = head;
    sort(arr, n+1);

    for(i = 0; i < n+1; i++) if(arr[i] == head) { idx = i; break; }

    printf("\nC-LOOK order: ");
    // Move towards higher tracks
    for(i = idx; i < n+1; i++)
        printf("%d ", arr[i]);

    // Jump to lowest request
    total += abs(arr[n] - arr[0]);

    for(i = 0; i < idx; i++)
        printf("%d ", arr[i]);

    // Calculate total movement
    // Distance from head to highest + highest to lowest + lowest to second-last
    total += abs(arr[idx] - arr[n]);

    printf("\nTotal head movement (C-LOOK): %d\n", total);
}

int main() {
    int n, i, head, disk_size;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter the request sequence: ");
    for(i = 0; i < n; i++) scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    SSTF(req, n, head);
    SCAN(req, n, head, disk_size);
    CLOOK(req, n, head);

    return 0;
}
