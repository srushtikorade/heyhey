#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    bool completed;
};

void SRTF(struct Node* processes, int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestRemainingTime = __INT_MAX__;
        int shortestIndex = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime &&
                processes[i].remainingTime < shortestRemainingTime) {
                shortestRemainingTime = processes[i].remainingTime;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        // Execute the shortest process for one unit of time
        processes[shortestIndex].remainingTime--;
        currentTime++;

        // Check if the process is completed
        if (processes[shortestIndex].remainingTime == 0) {
            processes[shortestIndex].completed = true;
            completedProcesses++;
            int waitingTime = currentTime - processes[shortestIndex].arrivalTime - processes[shortestIndex].burstTime;
            printf("Process %d completed. Arrival Time: %d, Burst Time: %d, Waiting Time: %d\n",
                   processes[shortestIndex].id, processes[shortestIndex].arrivalTime,
                   processes[shortestIndex].burstTime, waitingTime);
        }
    }
}

int main() {
    struct Node processes[] = {
        {1, 6, 0, 6, false},
        {2, 8, 2, 8, false},
        {3, 7, 3, 7, false},
        {4, 3, 7, 3, false}
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    printf("Order of Execution:\n");
    printf("Process ID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime);
    }

    SRTF(processes, n);

    return 0;
}
