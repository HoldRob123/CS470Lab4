#include <stdio.h>

// Structure to store process information
typedef struct {
    int pid;              // Process ID
    int arrival_time;     // Time when process arrives in ready queue
    int burst_time;       // CPU burst time required
    int remaining_time;   // Remaining time for Round Robin scheduling
    int waiting_time;     // Total waiting time
    int turnaround_time;  // Total turnaround time
    int completion_time;  // Completion time of the process
} Process;

int main() {
    int n, quantum; // Number of processes and time quantum

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

    // Ask user for time quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int current_time = 0;            // Current time in simulation
    int completed = 0;               // Number of completed processes
    float total_waiting = 0;         // Sum of waiting times
    float total_turnaround = 0;      // Sum of turnaround times

    printf("\nExecution Order:\n");

    // Round Robin scheduling loop: continue until all processes are completed
    while (completed < n) {
        int done = 1; // Flag to check if any process is ready in this cycle

        // Iterate through all processes in order
        for (int i = 0; i < n; i++) {
            // Check if process has arrived and has remaining time
            if (p[i].remaining_time > 0 && p[i].arrival_time <= current_time) {
                done = 0; // There is at least one process ready to execute

                // Print process execution for visualization
                printf("P%d ", p[i].pid);

                // Execute process for a time slice (quantum) or remaining time
                if (p[i].remaining_time > quantum) {
                    current_time += quantum;         // Increment current time
                    p[i].remaining_time -= quantum; // Reduce remaining time
                } else {
                    current_time += p[i].remaining_time; // Increment time by remaining time
                    p[i].remaining_time = 0;             // Process finished
                    completed++;                          // Increment completed count

                    p[i].completion_time = current_time;

                    // Turnaround Time = Completion Time - Arrival Time
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;

                    // Waiting Time = Turnaround Time - Burst Time
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

                    // Add to totals for averages
                    total_waiting += p[i].waiting_time;
                    total_turnaround += p[i].turnaround_time;
                }
            }
        }

        // If no process was ready, CPU idle for 1 unit of time
        if (done)
            current_time++;
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
