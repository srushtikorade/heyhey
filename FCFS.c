#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    int burstTime;
};

void FCFS(struct Node* arr, int n)
{
    printf("Order of Execution:\n");
    printf("Process ID\tBurst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\n", arr[i].id, arr[i].burstTime);
    }

    int waitingTime = 0;
    int avgTime = 0;

    for (int i = 1; i < n; i++)
    {
        waitingTime += arr[i - 1].burstTime;
        avgTime = avgTime + waitingTime;
        //printf("%d %d ",waitingTime, avgTime);
    }

    //printf("%d ",avgTime);

    printf("Average waiting time: %.2f\n", (float)avgTime / n);
}

int main()
{
    struct Node processes[] =
    {
        {1, 24},
        {2, 3},
        {3, 3}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    FCFS(processes, n);

    return 0;
}
