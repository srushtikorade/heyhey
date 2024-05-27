#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t can_read;
sem_t can_write;
sem_t mutex_reader_count;

int readers_reading = 0;
bool writer_writing = false;

void *reader(void *arg) {
    int id = *((int *)arg);
    while (true) {
        sem_wait(&can_read);
        sem_wait(&mutex_reader_count);
        readers_reading++;
        if (readers_reading == 1) {
            sem_wait(&can_write);
        }
        sem_post(&mutex_reader_count);
        sem_post(&can_read);

        // Reading...
        printf("Reader %d is reading...\n", id);
        usleep(1000000);

        sem_wait(&mutex_reader_count);
        readers_reading--;
        if (readers_reading == 0) {
            sem_post(&can_write);
        }
        sem_post(&mutex_reader_count);

        // Simulate time between reads
        usleep(1000000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (true) {
        sem_wait(&can_write);
        writer_writing = true;
        printf("Writer %d is writing...\n", id);
        sem_post(&can_write);

        // Writing...
        usleep(2000000);

        writer_writing = false;
        sem_post(&can_read);

        // Simulate time between writes
        usleep(2000000);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&can_read, 0, 1);
    sem_init(&can_write, 0, 1);
    sem_init(&mutex_reader_count, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&can_read);
    sem_destroy(&can_write);
    sem_destroy(&mutex_reader_count);

    return 0;
}
