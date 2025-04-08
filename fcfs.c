#include <stdio.h>

int main() {
    int n, at[10], bt[10], ct[10], tat[10], wt[10];
    int sum, i, j, k;
    float totaltat = 0, totalwt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process arrival time and burst time\n");

    for (i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &at[i]);
    }

    for (i = 0; i < n; i++) {
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Calculate Completion Time (CT)
    sum = at[0];
    for (j = 0; j < n; j++) {
        if (sum < at[j]) {
            sum = at[j];
        }
        sum = sum + bt[j];
        ct[j] = sum;
    }

    // Calculate Turnaround Time (TAT)
    for (k = 0; k < n; k++) {
        tat[k] = ct[k] - at[k];
        totaltat += tat[k];
    }

    // Calculate Waiting Time (WT)
    for (k = 0; k < n; k++) {
        wt[k] = tat[k] - bt[k];
        totalwt += wt[k];
    }

    // Display Output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totaltat / n);
    printf("Average Waiting Time: %.2f\n", totalwt / n);

    return 0;
}
