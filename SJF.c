#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    int burstTime;
};

void SJF(struct Node* arr, int n)
{
    // Sorting processes based on burst time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].burstTime > arr[j + 1].burstTime)
            {
                // Swap burst times
                int temp = arr[j].burstTime;
                arr[j].burstTime = arr[j + 1].burstTime;
                arr[j + 1].burstTime = temp;

                // Swap process IDs
                temp = arr[j].id;
                arr[j].id = arr[j + 1].id;
                arr[j + 1].id = temp;
            }
        }
    }

    printf("Order of Execution:\n");
    printf("Process ID\tBurst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\n", arr[i].id, arr[i].burstTime);
    }

    int waitingTime = 0;
    float avgTime = 0;

    for (int i = 1; i < n; i++)
    {
        waitingTime += arr[i - 1].burstTime;
        avgTime += waitingTime;
    }

    printf("Average waiting time: %.2f\n", avgTime / n);
}

int main()
{
    struct Node processes[] =
    {
        {1, 6},
        {2, 8},
        {3, 7},
        {4, 3}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    SJF(processes, n);

    return 0;
}
