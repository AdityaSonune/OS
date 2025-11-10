#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n];
    for(int i=0; i<n; i++) {
        pid[i] = i+1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int tat[n], wt[n];
    float total_tat = 0, total_wt = 0;

    while(completed != n) {
        int done_cycle = 1;
        for(int i=0;i<n;i++) {
            if(at[i] <= time && rt[i] > 0) {
                done_cycle = 0;
                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    tat[i] = time - at[i];
                    wt[i] = tat[i] - bt[i];
                    rt[i] = 0;
                    completed++;
                }
            }
        }
        if(done_cycle) time++;
    }

    printf("\nP\tAT\tBT\tTAT\tWT\n");
    for(int i=0;i<n;i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], tat[i], wt[i]);
        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf(" \nAverage Waiting Time = %.2f\n", total_wt/n);
    return 0;
}
