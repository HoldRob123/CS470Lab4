#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i+1);
        scanf("%d", &p[i].arrival_time);

        printf("Process %d Burst Time: ", i+1);
        scanf("%d", &p[i].burst_time);

        p[i].pid = i+1;
        p[i].remaining_time = p[i].burst_time;
    }

    int completed = 0, current_time = 0;
    float total_waiting = 0, total_turnaround = 0;

    printf("\nExecution Order:\n");

    while (completed != n) {
        int shortest = -1;
        int min_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time &&
                p[i].remaining_time > 0 &&
                p[i].remaining_time < min_time) {

                min_time = p[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        printf("P%d ", p[shortest].pid);

        p[shortest].remaining_time--;
        current_time++;

        if (p[shortest].remaining_time == 0) {
            completed++;

            p[shortest].completion_time = current_time;
            p[shortest].turnaround_time =
                p[shortest].completion_time - p[shortest].arrival_time;

            p[shortest].waiting_time =
                p[shortest].turnaround_time - p[shortest].burst_time;

            total_waiting += p[shortest].waiting_time;
            total_turnaround += p[shortest].turnaround_time;
        }
    }

    printf("\n\nPID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}
