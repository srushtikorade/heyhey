#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Global variables
int available[MAX_RESOURCES];  // Available resources
int request[MAX_PROCESSES][MAX_RESOURCES];  // Request matrix (maximum demand)
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Allocation matrix (current allocation)
bool finish[MAX_PROCESSES] = {false};  // Flag array to check if processes are finished
int work[MAX_RESOURCES];  // Work array to track available resources during the algorithm

// Function to initialize resources and matrices
void initialize() {
    printf("Enter the available resources:\n");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Allocation matrix
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Enter the allocation for process %d:\n", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Request matrix (maximum demand)
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Enter the max demand for process %d:\n", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Initialize work array to be equal to available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }
}

// Function to detect deadlock
void deadlockDetection() {
    bool deadlock = false;

    while (true) {
        int completedProcesses = 0;

        // Check each process
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int count = 0;

                // Check if the process's request can be satisfied
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (request[i][j] <= work[j]) {
                        count++;
                    }
                }

                // If the process can be satisfied
                if (count == MAX_RESOURCES) {
                    // Process can finish; update work array and mark as finished
                    finish[i] = true;
                    completedProcesses++;

                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                }
            }
                /*for(int i = 0;i < MAX_PROCESSES;i++)
                {
                    printf("%d ",finish[i]);
                }
                printf("\n");*/
        }

        // If no processes could be completed in this iteration, there is a deadlock
        if (completedProcesses == 0) {
            deadlock = true;
            break;
        }

        // If all processes are finished, there is no deadlock
        bool allFinished = true;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                //printf("Process %d is in deadlock", i);
                allFinished = false;
                break;
            }
        }

        if (allFinished) {
            deadlock = false;
            break;
        }
    }

    if (deadlock) {
        printf("Deadlock detected.\n");
    } else {
        printf("No deadlock detected.\n");
    }
}

// Main function
int main() {
    initialize();
    deadlockDetection();

    /*for(int i = 0;i < MAX_PROCESSES;i++)
    {
        printf("%d ",finish[i]);
    }*/

    return 0;
}
