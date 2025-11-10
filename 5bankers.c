#include <stdio.h>

int main() {
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int alloc[p][r], max[p][r], need[p][r], available[r];
    int finish[p], safeSeq[p], count = 0;

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Maximum Requirement Matrix:\n");
    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < r; i++)
        scanf("%d", &available[i]);

    for(int i = 0; i < p; i++)
        finish[i] = 0;

    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    while(count < p) {
        int found = 0;
        for(int i = 0; i < p; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < r; j++)
                    if(need[i][j] > available[j])
                        break;
                if(j == r) {
                    for(int k = 0; k < r; k++)
                        available[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found) {
            printf("\nSystem is in DEADLOCK state. No Safe Sequence.\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE STATE.\nSafe Sequence: ");
    for(int i = 0; i < p; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
