//RR - O(total burst time of all processes×n),
// 0 1 2=== 5 3 4
#include <stdio.h>

// Define a structure to store information about each process
struct Process {
    int id, at, bt, rt, wt, tat, ct;
    // id: Process ID
    // at: Arrival Time
    // bt: Burst Time
    // rt: Remaining Time (to be updated during execution)
    // wt: Waiting Time
    // tat: Turnaround Time
    // ct: Completion Time
};

// Function to calculate Round Robin scheduling
void calculateRoundRobin(struct Process pr[], int n, int quantum) {
    int time = 0;          // Current time
    int completed = 0;     // Count of completed processes
    int totalWT = 0;       // Total Waiting Time for all processes
    int totalTAT = 0;      // Total Turnaround Time for all processes
    int i;                 // Loop index
    printf("\nGantt Chart : ");
    // Main loop to process each process in a Round Robin manner until all are completed
    while (completed < n) {
        int processExecuted = 0;  // Flag to check if a process was executed in this iteration
      

        for (i = 0; i < n; i++) {
            // Check if the process has arrived and still has remaining time
            if (pr[i].at <= time && pr[i].rt > 0) {
                processExecuted = 1;  // Set flag to indicate a process is being executed
                printf("P%d ", pr[i].id);  // Print process ID for Gantt chart

                // If the remaining time is greater than the time quantum, process for quantum time
                if (pr[i].rt > quantum) {
                    time += quantum;       // Increase current time by quantum
                    pr[i].rt -= quantum;   // Decrease remaining time by quantum
                } else {
                    // If remaining time is less than or equal to quantum, complete the process
                    time += pr[i].rt;      // Update time to reflect process completion
                    pr[i].ct = time;       // Set completion time for the process
                    pr[i].tat = pr[i].ct - pr[i].at;  // Calculate Turnaround Time (TAT)
                    pr[i].wt = pr[i].tat - pr[i].bt;  // Calculate Waiting Time (WT)
                    totalWT += pr[i].wt;   // Accumulate total WT
                    totalTAT += pr[i].tat; // Accumulate total TAT
                    pr[i].rt = 0;          // Set remaining time to 0 to mark completion
                    completed++;           // Increment the count of completed processes
                }
            }
        }

        // If no process was executed in this loop (e.g., all pending processes haven't arrived), increment time
        if (!processExecuted) {
            time++;
        }
    }

    // Output the details for each process after completion
    printf("\n\nID  AT  BT  CT  WT  TAT\n");
    for (i = 0; i < n; i++) {
        printf("%d   %d   %d   %d   %d   %d\n", pr[i].id, pr[i].at, pr[i].bt, pr[i].ct, pr[i].wt, pr[i].tat);
    }

    // Calculate and print the average waiting time and turnaround time for all processes
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", (float)totalWT / n, (float)totalTAT / n);
}

int main() {
    int n, quantum;

    // Input number of processes and their arrival and burst times
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process pr[n];
    for (int i = 0; i < n; i++) {
        pr[i].id = i + 1; // Set process ID
        printf("Enter Arrival Time (AT) and Burst Time (BT) for process %d: ", pr[i].id);
        scanf("%d %d", &pr[i].at, &pr[i].bt);
        pr[i].rt = pr[i].bt;  // Initialize remaining time as burst time initially
    }

    // Input time quantum for Round Robin scheduling
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Calculate Round Robin scheduling
    calculateRoundRobin(pr, n, quantum);
    return 0;
}

