//O(m*N)
#include <stdio.h>

// Safety Algorithm Function
int safetyAlgorithm(int m, int n, int avail[n], int alloc[m][n], int need[m][n], int safeSequence[m]) {
    int success[m];  // Array to track the completion status of each process
    for (int i = 0; i < m; i++) {
        success[i] = 0;  // Mark all processes as not finished initially
    }

    int count = 0;  // Variable to track the number of processes added to the safe sequence
    while (count < m) {  // Loop until all processes are finished
        int found = 0;  // Flag to indicate if a process can be completed
        for (int i = 0; i < m; i++) {
            if (success[i] == 0) {  // Process i has not finished yet
                int flag = 1;  // Assume the process can execute
                for (int j = 0; j < n; j++) {
                    if (need[i][j] > avail[j]) {  // If the needed resources exceed available resources
                        flag = 0;  // Process cannot execute
                        break;
                    }
                }

                if (flag == 1) {  // If the process can be executed
                    for (int j = 0; j < n; j++) {
                        avail[j] += alloc[i][j];  // Release resources from process i
                    }
                    safeSequence[count++] = i;  // Add process to safe sequence
                    success[i] = 1;  // Mark process as finished
                    found = 1;  // Found a process that can execute
                }
            }
        }

        if (found == 0) {  // If no process can be found to execute, the system is unsafe
            return 0;  // Unsafe state
        }
    }
    return 1;  // Safe state, all processes can execute without deadlock
}

// Resource Request Algorithm Function
int requestResources(int m, int n, int proc, int request[n], int avail[n], int alloc[m][n], int need[m][n]) {
    // Check if the request exceeds the process's maximum claim or available resources
    for (int i = 0; i < n; i++) {
        if (request[i] > need[proc][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return 0;  // Request exceeds maximum claim
        }
        if (request[i] > avail[i]) {
            printf("Error: Resources are not available.\n");
            return 0;  // Not enough resources available
        }
    }

    // Temporarily allocate requested resources
    for (int i = 0; i < n; i++) {
        avail[i] -= request[i];  // Decrease the available resources
        alloc[proc][i] += request[i];  // Increase the allocated resources for the process
        need[proc][i] -= request[i];  // Decrease the remaining needed resources for the process
    }
    return 1;  // Resources allocated successfully
}

int main() {
    int m, n;  // Number of processes and resources

    // Input the number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &m);
    printf("Enter number of resources: ");
    scanf("%d", &n);

    // Declare matrices and arrays
    int alloc[m][n], max[m][n], avail[n], need[m][n], safeSequence[m];

    // Input the allocation matrix (allocated resources for each process)
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input the maximum matrix (maximum resources required by each process)
    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources (total available resources in the system)
    printf("Enter the available resources:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate and display the need matrix (remaining resources required by each process)
    printf("The need matrix is:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            need[i][j] = max[i][j] - alloc[i][j];  // Need = Max - Allocated
            printf("%d ", need[i][j]);  // Display the need matrix
        }
        printf("\n");
    }

    // Check for system's initial safety
    if (safetyAlgorithm(m, n, avail, alloc, need, safeSequence)) {
        // If system is in a safe state, print the safe sequence
        printf("The system is initially in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < m; i++) {
            printf("P%d", safeSequence[i]);  // Print the safe sequence of processes
            if (i != m - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        // If system is in an unsafe state (deadlock), print the message
        printf("The system is in an unsafe state (deadlock).\n");
        return 0;
    }

    // Resource Request
    char option;  // To store user's decision to request resources
    printf("Do you want to request resources? (y/n): ");
    scanf(" %c", &option);  // Read user's choice

    if (option == 'y' || option == 'Y') {
        int proc, request[n];  // Process number and requested resources array

        // Request process number and resources
        printf("Enter the process number (0 to %d): ", m - 1);
        scanf("%d", &proc);  // Read the process number
        printf("Enter the requested resources: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &request[i]);  // Read requested resources for each type
        }
        

        // Check if the request can be granted
        if (requestResources(m, n, proc, request, avail, alloc, need)) {
            // If resources are allocated successfully, check if the system remains in a safe state
            if (safetyAlgorithm(m, n, avail, alloc, need, safeSequence)) {
                // If system is still in a safe state after granting resources, print new safe sequence
                printf("Request can be granted. The system is in a safe state.\nNew safe sequence is: ");
                for (int i = 0; i < m; i++) {
                    printf("P%d", safeSequence[i]);
                    if (i != m - 1) {
                        printf(" -> ");
                    }
                }
                printf("\n");
            } else {
                // If system would be unsafe after granting request, deny the request
                printf("Request cannot be granted. The system would be in an unsafe state.\n");
                // Rollback the request (restore original state)
                for (int i = 0; i < n; i++) {
                    avail[i] += request[i];
                    alloc[proc][i] -= request[i];
                    need[proc][i] += request[i];
                }
            }
        }
    }

    return 0;  // End the program
}
