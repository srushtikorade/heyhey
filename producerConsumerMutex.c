#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the shared buffer

// Define the shared buffer
int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer
int in = 0;    // Index for the producer to insert into the buffer
int out = 0;   // Index for the consumer to remove from the buffer

// Mutex declaration
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function prototypes
void *producer(void *param);
void *consumer(void *param);
void insertItem(int item);
int removeItem();

int main() {
    pthread_t tid_producer, tid_consumer; // Thread IDs

    // Create producer and consumer threads
    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    // Join threads
    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

// Producer function
void *producer(void *param) {
    int item;
    while (1) {
        item = rand() % 1000; // Generate a random item

        // Lock the critical section
        pthread_mutex_lock(&mutex);
        if (count < BUFFER_SIZE) {
            insertItem(item);
            printf("Produced item: %d\n", item);
        }
        // Unlock the critical section
        pthread_mutex_unlock(&mutex);

        sleep(1); // Sleep for a while
    }
}

// Consumer function
void *consumer(void *param) {
    int item;
    while (1) {
        // Lock the critical section
        pthread_mutex_lock(&mutex);
        if (count > 0) {
            item = removeItem();
            printf("Consumed item: %d\n", item);
        }
        // Unlock the critical section
        pthread_mutex_unlock(&mutex);

        sleep(2); // Sleep for a while
    }
}

// Function to insert an item into the buffer
void insertItem(int item) {
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
}

// Function to remove an item from the buffer
int removeItem() {
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    return item;
}
