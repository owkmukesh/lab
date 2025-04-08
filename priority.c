#include <stdio.h>

int main() {
    int n, at[10], bt[10], wt[10], tat[10], ct[10], p[10], sum, i, j, k, pr[10], temp;
    float totalTat = 0, totalWt = 0;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    printf("Enter the process numbers:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("Enter the burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Enter burst time of process[%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("Enter the priority of each process:\n");
    for (i = 0; i < n; i++) {
        printf("Enter priority of process[%d]: ", i + 1);
        scanf("%d", &pr[i]);
    }

    // Sorting based on priority (lower value = higher priority)
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pr[j] > pr[j + 1]) {
                // Swap priority
                temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;

                // Swap burst time
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                // Swap process number
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate Completion Time
    sum = 0;
    for (j = 0; j < n; j++) {
        sum += bt[j];
        ct[j] = sum;
    }

    // Calculate Turnaround Time
    for (k = 0; k < n; k++) {
        tat[k] = ct[k];
        totalTat += tat[k];
    }

    // Calculate Waiting Time
    for (k = 0; k < n; k++) {
        wt[k] = tat[k] - bt[k];
        totalWt += wt[k];
    }

    // Output
    printf("\nProcess\tBT\tPriority\tTAT\tWT\n");
    for (j = 0; j < n; j++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n", p[j], bt[j], pr[j], tat[j], wt[j]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTat / n);
    printf("Average Waiting Time: %.2f\n", totalWt / n);

    return 0;
}
