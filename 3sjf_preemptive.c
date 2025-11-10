#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    fflush(stdout);       // <--- Ensures prompt is shown before scan
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n], ct[n], tat[n], wt[n];
    int completed = 0, time = 0, min_rt, shortest, finish;
    float total_tat = 0, total_wt = 0;

    for(int i=0;i<n;i++){
        pid[i] = i+1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        fflush(stdout);   // <--- Ensures prompt does not skip
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    while(completed != n) {
        shortest = -1;
        min_rt = 9999;

        for(int i=0;i<n;i++) {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;
        if(rt[shortest] == 0) {
            completed++;
            finish = time + 1;
            ct[shortest] = finish;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            total_tat += tat[shortest];
            total_wt += wt[shortest];
        }
        time++;
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage Turnaround Time = %.2f", total_tat/n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt/n);
    return 0;
}
