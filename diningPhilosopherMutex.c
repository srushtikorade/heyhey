#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
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
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);
        usleep((rand() % 100) * 1000);

        // Eat
        printf("Philosopher %d picked up forks and is eating.\n", id);
        usleep((rand() % 100) * 1000);
        printf("Philosopher %d finished eating one bite.\n", id);
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);

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

    // Initialize mutex locks for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
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

    // Destroy mutex locks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
