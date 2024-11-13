#include <stdio.h>
#include <limits.h>

// Define a structure for each process with necessary fields
struct Process {
    int id, at, bt, rt, wt, tat, ct;
};

// Function to calculate Round Robin scheduling
void calculateRoundRobin(struct Process pr[], int n, int quantum) {
    int time = 0, completed = 0, totalWT = 0, totalTAT = 0, i;
    printf("\nGantt Chart (Round Robin): ");
    while (completed < n) {
        int processExecuted = 0;
        for (i = 0; i < n; i++) {
            if (pr[i].at <= time && pr[i].rt > 0) {
                processExecuted = 1;
                printf("P%d ", pr[i].id);
                if (pr[i].rt > quantum) {
                    time += quantum;
                    pr[i].rt -= quantum;
                } else {
                    time += pr[i].rt;
                    pr[i].ct = time;
                    pr[i].tat = pr[i].ct - pr[i].at;
                    pr[i].wt = pr[i].tat - pr[i].bt;
                    totalWT += pr[i].wt;
                    totalTAT += pr[i].tat;
                    pr[i].rt = 0;
                    completed++;
                }
            }
        }
        if (!processExecuted) {
            time++;
        }
    }
    printf("\n\nID  AT  BT  CT  WT  TAT\n");
    for (i = 0; i < n; i++) {
        printf("%d   %d   %d   %d   %d   %d\n", pr[i].id, pr[i].at, pr[i].bt, pr[i].ct, pr[i].wt, pr[i].tat);
    }
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", (float)totalWT / n, (float)totalTAT / n);
}

// Function to calculate Shortest Job First (SJF) Preemptive scheduling
void calculateSJFPreemptive(struct Process pr[], int n) {
    int completed = 0, time = 0, minRT, shortest = 0, totalWT = 0, totalTAT = 0;
    printf("Gantt Chart (SJF Preemptive): ");
    while (completed < n) {
        minRT = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (pr[i].at <= time && pr[i].rt > 0 && pr[i].rt < minRT) {
                minRT = pr[i].rt;
                shortest = i;
            }
        }
        if (minRT == INT_MAX) {
            time++;
            continue;
        }
        printf("P%d ", pr[shortest].id);
        pr[shortest].rt--;
        if (pr[shortest].rt == 0) {
            completed++;
            pr[shortest].ct = time + 1;
            pr[shortest].tat = pr[shortest].ct - pr[shortest].at;
            pr[shortest].wt = pr[shortest].tat - pr[shortest].bt;
            totalWT += pr[shortest].wt;
            totalTAT += pr[shortest].tat;
        }
        time++;
    }
    printf("\n\nID  AT  BT  CT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d   %d   %d   %d   %d\n", pr[i].id, pr[i].at, pr[i].bt, pr[i].ct, pr[i].wt, pr[i].tat);
    }
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", (float)totalWT / n, (float)totalTAT / n);
}

int main() {
    int n, choice, quantum;

    // Input number of processes and their arrival and burst times
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process pr[n];
    for (int i = 0; i < n; i++) {
        pr[i].id = i + 1;
        printf("Enter Arrival Time (AT) and Burst Time (BT) for process %d: ", pr[i].id);
        scanf("%d %d", &pr[i].at, &pr[i].bt);
        pr[i].rt = pr[i].bt;
    }

    // Menu to choose the scheduling algorithm
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Round Robin\n");
    printf("2. Shortest Job First (Preemptive)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &quantum);
            calculateRoundRobin(pr, n, quantum);
            break;
        case 2:
            calculateSJFPreemptive(pr, n);
            break;
        default:
            printf("Invalid choice. Please select 1 or 2.\n");
            break;
    }

    return 0;
}
