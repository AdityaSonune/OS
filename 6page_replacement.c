#include <stdio.h>

int findOptimal(int pages[], int frames[], int n, int f, int index) {
    int pos = -1, farthest = index;
    for(int i = 0; i < f; i++) {
        int j;
        for(j = index; j < n; j++) {
            if(frames[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if(j == n)
            return i;
    }
    return (pos == -1) ? 0 : pos;
}

void FIFO(int pages[], int n, int f) {
    int frames[f], front = 0, faults = 0;
    for(int i = 0; i < f; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for(int i = 0; i < n; i++) {
        int hit = 0;
        for(int j = 0; j < f; j++)
            if(frames[j] == pages[i]) hit = 1;

        if(!hit) {
            frames[front] = pages[i];
            front = (front + 1) % f;
            faults++;
        }

        for(int j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

void LRU(int pages[], int n, int f) {
    int frames[f], used[f], faults = 0;
    for(int i = 0; i < f; i++) frames[i] = -1;

    printf("\nLRU Page Replacement:\n");
    for(int i = 0; i < n; i++) {
        int hit = 0;
        for(int j = 0; j < f; j++)
            if(frames[j] == pages[i]) {
                hit = 1;
                used[j] = i;
            }

        if(!hit) {
            int pos = 0, min = used[0];
            for(int j = 1; j < f; j++)
                if(used[j] < min) {
                    min = used[j];
                    pos = j;
                }
            frames[pos] = pages[i];
            used[pos] = i;
            faults++;
        }

        for(int j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

void Optimal(int pages[], int n, int f) {
    int frames[f], faults = 0;
    for(int i = 0; i < f; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for(int i = 0; i < n; i++) {
        int hit = 0;
        for(int j = 0; j < f; j++)
            if(frames[j] == pages[i]) hit = 1;

        if(!hit) {
            int pos = findOptimal(pages, frames, n, f, i + 1);
            frames[pos] = pages[i];
            faults++;
        }

        for(int j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", faults);
}

int main() {
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter page reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames (≥ 3): ");
    scanf("%d", &f);

    FIFO(pages, n, f);
    LRU(pages, n, f);
    Optimal(pages, n, f);

    return 0;
}
