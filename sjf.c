#include <stdio.h>

int main() {
    int n, bt[10], wt[10], tat[10], ct[10], p[10];
    int sum, i, j, k, temp;
    float totaltat = 0, totalwt = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("Enter the process numbers:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("\nEnter the process burst time:\n");
    for(i = 0; i < n; i++) {
        printf("Enter burst time of process [%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Bubble sort (sorting by burst time)
    for(i = 0; i < n; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(bt[j] > bt[j + 1]) {
                // Swap burst times
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap corresponding process IDs
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate completion time
    sum = 0;
    for(j = 0; j < n; j++) {
        sum = sum + bt[j];
        ct[j] = sum;
    }

    // Calculate Turnaround Time (TAT)
    for(k = 0; k < n; k++) {
        tat[k] = ct[k];
        totaltat += tat[k];
    }

    // Calculate Waiting Time (WT)
    for(k = 0; k < n; k++) {
        wt[k] = tat[k] - bt[k];
        totalwt += wt[k];
    }

    printf("\nProcess\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage turnaround time: %.2f\n", totaltat / n);
    printf("Average waiting time: %.2f\n", totalwt / n);

    return 0;
}
