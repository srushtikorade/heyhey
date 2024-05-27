#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    int time;
    int priority;
};

void swap(struct Node* p, struct Node* q)
{
    struct Node temp = *p;
    *p = *q;
    *q = temp;
}

void priorityScheduling(struct Node* arr, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j].priority > arr[j+1].priority)
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }

    printf("Order of Execution:\n");
    printf("Process ID\tBurst Time\tPriority\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n", arr[i].id, arr[i].time, arr[i].priority);
    }
}

int main()
{
    struct Node processes[] =
    {
        {1, 10, 3},
        {2, 5, 1},
        {3, 8, 2},
        {4, 3, 4}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    priorityScheduling(processes, n);

    return 0;
}
