
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Array to store remaining burst times
    int execution_order[1000];
    int execution_count = 0;
    
    // Initialize remaining time
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
    }

    // Current time
    int current_time = 0;

    // Keep traversing processes in round-robin manner until all of them are not done
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            // If burst time of a process is greater than 0 then only need to process further
            if (proc[i].remaining_time > 0) {
                done = 0; // There is a pending process
                
                // Add process to execution order
                execution_order[execution_count++] = proc[i].process_id;
                
                if (proc[i].remaining_time > quantum) {
                    // Process will not complete in this time quantum
                    current_time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    // Process will complete in this time quantum
                    current_time += proc[i].remaining_time;
                    proc[i].waiting_time = current_time - proc[i].arrival_time - proc[i].burst_time;
                    proc[i].remaining_time = 0;
                }
            }
        }

        // If all processes are done
        if (done == 1) break;
    }

    // Print the execution order
    printf("Execution Order: ");
    for (int i = 0; i < execution_count; i++) {
        printf("%d ", execution_order[i]);
    }
    printf("\n");
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 
    printf("Round Robin Scheduling (Quantum = %d):\n", quantum);
    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
