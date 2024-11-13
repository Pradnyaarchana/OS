// Parent Program: parent.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    

    // Sort the array
    bubbleSort(arr, n);
    
    
    // Fork a new process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process

        // Convert sorted array elements to strings
        char *args[n + 2];
        args[0] = "./child"; // Path to the child program

        for (int i = 0; i < n; i++) {
            char *num = malloc(10);
            sprintf(num, "%d", arr[i]);
            args[i + 1] = num;
        }

        args[n + 1] = NULL; // Null-terminate the argument array

        // Execute the child program using execve
        execve(args[0], args, NULL);

        // If execve fails
        perror("execve failed");
        for (int i = 1; i <= n; i++) free(args[i]); // Free allocated memory
        exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Parent process completed.\n");
    }

    return 0;
}