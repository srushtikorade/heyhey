#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5 // Size of the shared buffer

// Define the shared buffer
int buffer[BUFFER_SIZE];
int in = 0;    // Index for the producer to insert into the buffer
int out = 0;   // Index for the consumer to remove from the buffer

// Semaphore declaration
sem_t empty_slots, full_slots;

// Function prototypes
void *producer(void *param);
void *consumer(void *param);
void insertItem(int item);
int removeItem();

int main() {
    pthread_t tid_producer, tid_consumer; // Thread IDs

    // Initialize semaphores
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    // Create producer and consumer threads
    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    // Join threads
    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    // Destroy semaphores
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    return 0;
}

// Producer function
void *producer(void *param) {
    int item;
    while (1) {
        item = rand() % 1000; // Generate a random item

        // Wait for an empty slot in the buffer
        sem_wait(&empty_slots);

        // Insert item into the buffer
        insertItem(item);
        printf("Produced item: %d\n", item);

        // Signal that a slot in the buffer is filled
        sem_post(&full_slots);

        sleep(1); // Sleep for a while
    }
}

// Consumer function
void *consumer(void *param) {
    int item;
    while (1) {
        // Wait for a filled slot in the buffer
        sem_wait(&full_slots);

        // Remove item from the buffer
        item = removeItem();
        printf("Consumed item: %d\n", item);

        // Signal that a slot in the buffer is empty
        sem_post(&empty_slots);

        sleep(2); // Sleep for a while
    }
}

// Function to insert an item into the buffer
void insertItem(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
}

// Function to remove an item from the buffer
int removeItem() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return item;
}
