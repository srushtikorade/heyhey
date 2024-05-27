#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_read = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_write = PTHREAD_COND_INITIALIZER;

int readers_reading = 0;
bool writer_writing = false;

void *reader(void *arg) {
    int id = *((int *)arg);
    while (true) {
        pthread_mutex_lock(&mutex);
        while (writer_writing) {
            pthread_cond_wait(&can_read, &mutex);
        }
        readers_reading++;
        printf("Reader %d is reading...\n", id);
        pthread_mutex_unlock(&mutex);

        // Simulate reading
        usleep(1000000);

        pthread_mutex_lock(&mutex);
        readers_reading--;
        if (readers_reading == 0) {
            pthread_cond_signal(&can_write);
        }
        pthread_mutex_unlock(&mutex);

        // Simulate time between reads
        usleep(1000000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (true) {
        pthread_mutex_lock(&mutex);
        while (readers_reading > 0 || writer_writing) {
            pthread_cond_wait(&can_write, &mutex);
        }
        writer_writing = true;
        printf("Writer %d is writing...\n", id);
        pthread_mutex_unlock(&mutex);

        // Simulate writing
        usleep(2000000);

        pthread_mutex_lock(&mutex);
        writer_writing = false;
        pthread_cond_broadcast(&can_read);
        pthread_mutex_unlock(&mutex);

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

    return 0;
}
