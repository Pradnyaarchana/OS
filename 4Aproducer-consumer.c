//O(1)

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>  // Include for srand and time

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        int item = rand() % 100; // Generate a random number (between 0 and 99)

        // Wait if buffer is full
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); // Enter critical section

        // Produce an item and store it in the buffer
        buffer[in] = item;  
        printf("Produced: %d at buffer position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; // Update buffer index

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Signal consumer that there's new data
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        // Wait if buffer is empty
        sem_wait(&full);
        pthread_mutex_lock(&mutex); // Enter critical section

        // Consume an item from the buffer
        int item = buffer[out];
        printf("Consumed: %d from buffer position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Update buffer index

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Signal producer that there's space in buffer
    }
    return NULL;
}

int main() {
    // Initialize random number generator
    srand(time(NULL)); // Initialize random seed to get different results each time

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer is empty initially
    sem_init(&full, 0, 0); // No items in the buffer initially
    pthread_mutex_init(&mutex, NULL);

    // Create threads for producer and consumer
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish execution
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up resources
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
