//SJF - O(total burst time of all processes*n)
//2 5 1 0 4 == 6 2 8 3 4
#include <stdio.h>
#include <limits.h>

// Define a structure for each process with necessary fields
struct Process {
    int id, at, bt, rt, wt, tat, ct;  // id, arrival time (at), burst time (bt), remaining time (rt), waiting time (wt), turnaround time (tat), completion time (ct)
};

// Function to calculate Shortest Job First (SJF) Preemptive scheduling
void calculateSJFPreemptive(struct Process pr[], int n) {
    int completed = 0, time = 0, minRT, shortest = 0, totalWT = 0, totalTAT = 0;

    // Print header for Gantt Chart
    printf("Gantt Chart:\n");

    // Run the scheduling until all processes are completed
    while (completed < n) {
        minRT = INT_MAX;  // Initialize minimum remaining time as a large value

        // Find the process with the shortest remaining time that has arrived and is still running
        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and if it has remaining time
            if (pr[i].at <= time && pr[i].rt > 0 && pr[i].rt < minRT) {
                minRT = pr[i].rt;  // Update the shortest remaining time
                shortest = i;      // Store the index of the process with the shortest remaining time
            }
        }

        // If no process is ready to execute, increment the time and continue
        if (minRT == INT_MAX) {
            time++;
            continue;
        }

        // Print the ID of the process that is currently executing
        printf("P%d ", pr[shortest].id);

        // Decrease the remaining time of the selected process
        pr[shortest].rt--;

        // If the process has finished executing, calculate the necessary times
        if (pr[shortest].rt == 0) {
            completed++;  // Increment the completed process count
            pr[shortest].ct = time + 1;  // Set the completion time for the process
            pr[shortest].tat = pr[shortest].ct - pr[shortest].at;  // Calculate the turnaround time
            pr[shortest].wt = pr[shortest].tat - pr[shortest].bt;  // Calculate the waiting time
            totalWT += pr[shortest].wt;  // Accumulate total waiting time
            totalTAT += pr[shortest].tat;  // Accumulate total turnaround time
        }

        // Increment the time after each unit of execution
        time++;
    }

    // Print the process details in a table format
    printf("\n\nID  AT  BT  CT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        // Print the ID, arrival time, burst time, completion time, waiting time, and turnaround time for each process
        printf("%d   %d   %d   %d   %d   %d\n", pr[i].id, pr[i].at, pr[i].bt, pr[i].ct, pr[i].wt, pr[i].tat);
    }

    // Calculate and print the average waiting time and average turnaround time
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", (float)totalWT / n, (float)totalTAT / n);
}

// Main function where the program execution starts
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);  // Take input for the number of processes

    struct Process pr[n];  // Declare an array of Process structs

    // Input details for each process
    for (int i = 0; i < n; i++) {
        pr[i].id = i + 1;  // Assign a unique ID to each process
        printf("Enter AT and BT for process %d: ", pr[i].id);  // Prompt for arrival time and burst time
        scanf("%d %d", &pr[i].at, &pr[i].bt);  // Read the arrival time (AT) and burst time (BT)
        pr[i].rt = pr[i].bt;  // Set the remaining time to the burst time initially
    }

    // Call the function to calculate and display the SJF Preemptive scheduling
    calculateSJFPreemptive(pr, n);

    return 0;  // Exit the program successfully
}
