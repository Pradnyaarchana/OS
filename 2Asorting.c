// o(n^2)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0...i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of elements to sort: ");
    scanf("%d", &n);

    int arr[n], arr_copy[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i]; // Copy for child process
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process started. Performing insertion sort...\n");
        insertionSort(arr_copy, n);
        printf("Child process sorted array: ");
        printArray(arr_copy, n);

        // Demonstrate orphan state
        sleep(5);  // Parent process will exit before child

        printf("Child process completed.\n");
    } else {
        // Parent process
        printf("Parent process started. Performing bubble sort...\n");
        bubbleSort(arr, n);
        printf("Parent process sorted array: ");
        printArray(arr, n);

      // Demonstrate zombie process (uncomment sleep to see it)
       //sleep(10);
        // Wait for child process to avoid zombie
        wait(NULL);

        

        printf("Parent process completed.\n");
    }

    return 0;
}
