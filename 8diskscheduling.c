// sstf-O(n2)
// other O(n log n)

// 82,170,43,140,24,16,190
#include <stdio.h>   // Standard input-output library for printf and scanf functions
#include <stdlib.h>  // Standard library for functions like abs
#include <limits.h>  // Library for limits of data types, e.g., INT_MAX

// Function to find the closest unvisited request to the current head position for SSTF
int find_min_index(int req[], int visited[], int head_pos, int n) {
    int min = INT_MAX; // Initialize minimum distance to the maximum integer value
    int index = -1;    // Variable to store the index of the closest request

    for (int i = 0; i < n; i++) {
        // Check if request at i is unvisited and closer to head_pos than current min
        if (!visited[i] && abs(head_pos - req[i]) < min) {
            index = i; // Update the index of the closest request
            min = abs(head_pos - req[i]); // Update the minimum distance
        }
    }
    return index; // Return the index of the closest unvisited request
}

// SSTF (Shortest Seek Time First) Disk Scheduling Algorithm
void sstf(int req[], int visited[], int head_pos, int n) {
    int tot_head_mov = 0; // Initialize total head movement counter
    printf("SSTF Order: ");

    for (int i = 0; i < n; i++) {
        int min_index = find_min_index(req, visited, head_pos, n); // Find closest request
        visited[min_index] = 1; // Mark the closest request as visited
        tot_head_mov += abs(head_pos - req[min_index]); // Add head movement to total
        head_pos = req[min_index]; // Move head to this request's position
        printf("%d\t", head_pos); // Print current head position
    }
    printf("\nTotal Head Movements: %d\n", tot_head_mov); // Print total head movements
}

// C-LOOK Disk Scheduling Algorithm
void clook(int req[], int n, int head_pos, int direction, int disk_size) {
    int tot_head_mov = 0; // Initialize total head movement counter
    printf("C-LOOK Order: ");

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) { // Swap elements if out of order
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // Find the index of the first request greater than or equal to head_pos
    int index = 0;
    while (index < n && req[index] < head_pos) {
        index++;
    }

    if (direction == 1) { // If direction is towards higher track numbers
        for (int i = index; i < n; i++) { // Serve requests moving right
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
        for (int i = 0; i < index; i++) { // Loop back to serve leftmost requests
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
    } else { // If direction is towards lower track numbers
        for (int i = index - 1; i >= 0; i--) { // Serve requests moving left
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
        for (int i = n - 1; i >= index; i--) { // Loop back to rightmost requests
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
    }
    printf("\nTotal Head Movements: %d\n", tot_head_mov); // Print total head movements
}

// SCAN Disk Scheduling Algorithm
void scan(int req[], int n, int head_pos, int direction, int disk_size) {
    int tot_head_mov = 0; // Initialize total head movement counter
    printf("SCAN Order: ");

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) { // Swap elements if out of order
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // Find the index of the first request greater than or equal to head_pos
    int index = 0;
    while (index < n && req[index] < head_pos) {
        index++;
    }

    if (direction == 1) { // If direction is towards higher track numbers
        for (int i = index; i < n; i++) { // Serve requests moving right
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
        tot_head_mov += abs(head_pos - (disk_size - 1)); // Move to end of disk
        head_pos = disk_size - 1; // Update head position to end of disk
        for (int i = index - 1; i >= 0; i--) { // Serve requests moving left
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
    } else { // If direction is towards lower track numbers
        for (int i = index - 1; i >= 0; i--) { // Serve requests moving left
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
        tot_head_mov += abs(head_pos - 0); // Move to beginning of disk
        head_pos = 0; // Update head position to start of disk
        for (int i = index; i < n; i++) { // Serve requests moving right
            tot_head_mov += abs(head_pos - req[i]); // Update head movement
            head_pos = req[i]; // Move head to current request
            printf("%d\t", head_pos); // Print request position
        }
    }
    printf("\nTotal Head Movements: %d\n", tot_head_mov); // Print total head movements
}

int main() {
    int choice, disk_size, n, head_pos, direction; // Variables for user input
    printf("Enter the size of the disk: ");
    scanf("%d", &disk_size); // Read disk size from user

    printf("Enter the number of requests: ");
    scanf("%d", &n); // Read number of requests from user
    int req[n]; // Array to store requests
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]); // Read each request
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head_pos); // Read initial head position

    printf("Enter the direction (1 for high, 0 for low): ");
    scanf("%d", &direction); // Read direction for SCAN and C-LOOK

    // Loop until the user chooses to exit
    do {
        printf("\nChoose an option:\n");
        printf("1. SSTF\n2. SCAN\n3. C-LOOK\n4. Exit\n");
        scanf("%d", &choice); // Read user choice

        switch (choice) {
            case 1: // SSTF scheduling
                int visited[n];
                for (int i = 0; i < n; i++) visited[i] = 0; // Initialize visited array
                sstf(req, visited, head_pos, n); // Call SSTF function
                break;
            case 2: // SCAN scheduling
                scan(req, n, head_pos, direction, disk_size); // Call SCAN function
                break;
            case 3: // C-LOOK scheduling
                clook(req, n, head_pos, direction, disk_size); // Call C-LOOK function
                break;
            case 4: // Exit
                printf("Exiting...\n");
                break;
            default: // Invalid choice
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4); // Repeat menu until exit option is chosen
    return 0; // Program ends successfully
}


