#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

#define SZ 4096  // Size of shared memory

int main() {
    int shm_id;  // Shared memory ID
    char *shm_ptr;  // Pointer to the shared memory segment
    char data[100];  // Buffer to store user input

    // Create shared memory segment
    shm_id = shmget(IPC_PRIVATE, SZ, IPC_CREAT | 0666);  // Create shared memory with the size SZ
    if (shm_id < 0) {  // If shmget fails, print error and exit
        perror("Error creating shared memory");
        exit(1);
    }

    // Print the shared memory ID created
    printf("Shared memory created with ID: %d\n", shm_id);

    // Attach the shared memory segment to the process’s address space
    shm_ptr = (char *)shmat(shm_id, NULL, 0);  // Attach shared memory, return pointer
    if (shm_ptr == (void *)-1) {  // Check for error during attachment
        printf("Error attaching shared memory\n");
        exit(1);
    }
    // Print the address where the shared memory is attached
    printf("Shared memory attached at address %p\n", shm_ptr);

    // Take input from the user
    printf("Enter data to write to shared memory: ");
    fgets(data, sizeof(data), stdin);  // Read user input
    data[strcspn(data, "\n")] = 0;  // Remove the trailing newline from input
    strcpy(shm_ptr, data);  // Copy user input into shared memory
    printf("Data written to shared memory: %s\n", shm_ptr);

    printf("Waiting for client to read data...\n");
    sleep(10);  // Sleep for 10 seconds to allow client to read

    // Detach shared memory from the process
    if (shmdt(shm_ptr) == -1) {  // Detach the shared memory segment
        printf("Error detaching shared memory\n");
        exit(1);
    }
    printf("Shared memory detached.\n");

    // Delete the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {  // Remove shared memory
        printf("Error deleting shared memory\n");
        exit(1);
    }
    printf("Shared memory deleted.\n");

    return 0;  // Exit program
}
