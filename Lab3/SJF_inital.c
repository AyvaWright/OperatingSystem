
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_time = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && !proc[i].is_completed) {
            if (proc[i].remaining_time < min_time) {
                min_time = proc[i].remaining_time;
                index = i;
            }
        }
    }
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int current_time = 0;
    int completed = 0;
    int prev = -1;
    int execution_order[1000];  // Assuming a maximum of 1000 time units
    int execution_count = 0;

    // Initialize waiting and turnaround times
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
    }
    
    // Build the loop to execute processes in the queue list
    while (completed != n) {
        int index = findNextProcess(proc, current_time);
        //Process found to execute
        if (index != -1) {
            // If the process changes, record the execution order
            if (prev != index) {
                execution_order[execution_count++] = proc[index].process_id;
                prev = index;
            }
            
            proc[index].remaining_time--;
            current_time++;
            
            // If the process is completed
            if (proc[index].remaining_time == 0) {
                proc[index].is_completed = 1;
                completed++;
                
                // Calculate waiting time and turnaround time
                proc[index].turnaround_time = current_time - proc[index].arrival_time;
                proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
            }
        } else {
            // No process available, increment time
            current_time++;
        }
    }
    
    // Print execution order
    printf("Execution Order: ");
    for (int i = 0; i < execution_count; i++) {
        printf("%d ", execution_order[i]);
    }
    printf("\n");
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t\t%d\t\t\t\t%d\t\t\t%d\t\t\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    printf("Shortest Job First (Preemptive) Scheduling:\n");
    srtf(proc);
    printProcesses(proc);

    return 0;
}
