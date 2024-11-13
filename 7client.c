#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define SZ 4096  // Size of shared memory

int main() {
    int shm_id;              // Shared memory ID
    char *shm_ptr;           // Pointer to shared memory

    // Get the shared memory ID from the user
    printf("Enter shared memory ID: ");
    scanf("%d", &shm_id);    // Input shared memory ID
    getchar();  // Consume the newline character left by scanf

    // Attach the shared memory segment to the process's address space
    shm_ptr = (char *)shmat(shm_id, NULL, 0);  // Attach the shared memory
    if (shm_ptr == (void *)-1) {  // Check if attachment failed
        printf("Error attaching shared memory\n");
        exit(1);  // Exit the program if attaching failed
    }
    printf("Shared memory attached at address %p\n", shm_ptr);  // Print the memory address of shared memory

    // Read and display the data stored in shared memory
    printf("Data read from shared memory: %s\n", shm_ptr);

    // Detach the shared memory segment from the process's address space
    if (shmdt(shm_ptr) == -1) {  // Check if detachment failed
        printf("Error detaching shared memory\n");
        exit(1);  // Exit the program if detaching failed
    }
    printf("Shared memory detached.\n");  // Print confirmation that shared memory was detached

    return 0;  // Program ends successfully
}
