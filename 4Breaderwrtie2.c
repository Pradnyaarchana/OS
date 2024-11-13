//O(NUM_READERS×NUM_ITERATIONS)
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3         // Number of reader threads
#define NUM_ITERATIONS 5      // Number of iterations each reader and writer performs

// Mutex for synchronizing access to shared data
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Barrier for synchronizing readers before reading the data
pthread_barrier_t barrier;

// Shared data that writer writes to and readers read from
int shared_data;

// Writer thread function
void *writer(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Generate a random number to write
        int random_number = rand() % 100;

        // Lock the mutex to ensure exclusive access to the shared data
        pthread_mutex_lock(&mutex);

        // Write the random number to the shared data
        shared_data = random_number;
        printf("Writer wrote: %d\n", shared_data);

        // Unlock the mutex so other threads can access shared data
        pthread_mutex_unlock(&mutex);

        // Sleep for a while to simulate writing time
        sleep(1);
    }
    pthread_exit(NULL);  // Exit the writer thread
}

// Reader thread function
void *reader(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Wait for all reader threads to reach this point before continuing
        pthread_barrier_wait(&barrier);

        // Lock the mutex to safely read shared data
        pthread_mutex_lock(&mutex);

        // Read the shared data
        int data = shared_data;
        // Print the data read by the reader
        printf("Reader: Item READ from shared data: %d\n", data);

        // Unlock the mutex so other threads can access shared data
        pthread_mutex_unlock(&mutex);

        // Sleep for a while to simulate reading time
        sleep(1);
    }
    pthread_exit(NULL);  // Exit the reader thread
}

int main() {
    srand(time(NULL));  // Initialize the random number generator with a seed

    // Declare threads for writer and readers
    pthread_t writer_thread, reader_threads[NUM_READERS];

    // Initialize the barrier to synchronize reader threads
    pthread_barrier_init(&barrier, NULL, NUM_READERS);

    // Create the writer thread
    pthread_create(&writer_thread, NULL, writer, NULL);

    // Create reader threads (no need to pass reader IDs)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }

    // Wait for the writer thread to finish
    pthread_join(writer_thread, NULL);

    // Wait for all reader threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Clean up the barrier
    pthread_barrier_destroy(&barrier);

    return 0;
}
