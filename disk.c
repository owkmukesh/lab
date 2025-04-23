// FCFS - Disk Scheduling
#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int total_seek_time = 0;
    printf("Sequence of disk access: %d", head);

    for (int i = 0; i < n; i++) {
        total_seek_time += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
    printf("Average seek time: %.2f\n", (float)total_seek_time / n);
}

int main() {
    int n, head;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    fcfs(requests, n, head);

    return 0;
}
