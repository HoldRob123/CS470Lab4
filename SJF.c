#include <stdio.h>
#include <limits.h> // For INT_MAX

// Structure to store process information
typedef struct {
    int pid;              // Process ID
    int arrival_time;     // Time when process arrives in ready queue
    int burst_time;       // CPU burst time required
    int remaining_time;   // Remaining time for preemptive SJF
    int waiting_time;     // Total waiting time
    int turnaround_time;  // Total turnaround time
    int completion_time;  // Completion time of the process
} Process;

int main() {
    int n; // Number of processes

    // Ask user for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n]; // Array to store all processes

    // Input process arrival time and burst time
    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i+1);
        scanf("%d", &p[i].arrival_time);

        printf("Process %d Burst Time: ", i+1);
        scanf("%d", &p[i].burst_time);

        p[i].pid = i+1;                 // Assign PID
        p[i].remaining_time = p[i].burst_time; // Initialize remaining time
    }

    int completed = 0;           // Number of completed processes
    int current_time = 0;        // Current time in the simulation
    float total_waiting = 0;     // Sum of waiting times
    float total_turnaround = 0;  // Sum of turnaround times

    printf("\nExecution Order:\n");

    // Preemptive SJF loop: continue until all processes are completed
    while (completed != n) {
        int shortest = -1;       // Index of process with shortest remaining time
        int min_time = INT_MAX;  // Initialize to max value

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && // Has arrived
                p[i].remaining_time > 0 &&          // Not finished
                p[i].remaining_time < min_time) {   // Shortest remaining time

                min_time = p[i].remaining_time;
                shortest = i;
            }
        }

        // If no process is ready, increment time (CPU idle)
        if (shortest == -1) {
            current_time++;
            continue;
        }

        // Print execution for visualization
        printf("P%d ", p[shortest].pid);

        // Execute process for 1 time unit
        p[shortest].remaining_time--;
        current_time++;

        // If process finished, calculate metrics
        if (p[shortest].remaining_time == 0) {
            completed++; // Increment completed process count

            p[shortest].completion_time = current_time;

            // Turnaround Time = Completion Time - Arrival Time
            p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;

            // Waiting Time = Turnaround Time - Burst Time
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;

            // Add to totals for averages
            total_waiting += p[shortest].waiting_time;
            total_turnaround += p[shortest].turnaround_time;
        }
    }

    // Print process table with results
    printf("\n\nPID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);
    }

    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);

    return 0;
}
