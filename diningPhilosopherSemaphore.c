#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
int bites[NUM_PHILOSOPHERS] = {0};
int total_bites = 0;

void *philosopher(void *arg) {
    int id = *((int *) arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (bites[id] < 1) {
        // Think (sleep for random time)
        printf("Philosopher %d is thinking.\n", id);
        usleep((rand() % 100) * 1000);

        // Pick up forks
        printf("Philosopher %d is hungry and trying to pick up forks.\n", id);
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);
        usleep((rand() % 100) * 1000);

        // Eat
        printf("Philosopher %d picked up forks and is eating.\n", id);
        usleep((rand() % 100) * 1000);
        printf("Philosopher %d finished eating one bite.\n", id);
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);

        bites[id]++;
        total_bites++;

        // Take a break between actions
        usleep((rand() % 100) * 1000);
    }

    // Check if all philosophers have had one bite
    if (total_bites == NUM_PHILOSOPHERS) {
        printf("All philosophers have had one bite. Exiting...\n");
        exit(0);
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    // Initialize semaphores for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1); // Initialize with value 1
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&philosophers[i], NULL, philosopher, arg);
    }

    // Join philosopher threads (should never return)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
