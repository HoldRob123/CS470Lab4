#include <stdio.h>

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
    int n, quantum;

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

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int current_time = 0, completed = 0;
    float total_waiting = 0, total_turnaround = 0;

    printf("\nExecution Order:\n");

    while (completed < n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 &&
                p[i].arrival_time <= current_time) {

                done = 0;

                printf("P%d ", p[i].pid);

                if (p[i].remaining_time > quantum) {
                    current_time += quantum;
                    p[i].remaining_time -= quantum;
                } else {
                    current_time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    completed++;

                    p[i].completion_time = current_time;
                    p[i].turnaround_time =
                        p[i].completion_time - p[i].arrival_time;

                    p[i].waiting_time =
                        p[i].turnaround_time - p[i].burst_time;

                    total_waiting += p[i].waiting_time;
                    total_turnaround += p[i].turnaround_time;
                }
            }
        }

        if (done)
            current_time++;
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
