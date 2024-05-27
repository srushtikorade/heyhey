#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 4
#define MAX_SLOTS 5

int processes[MAX_PROCESSES];
int slots[MAX_SLOTS];
int finish[MAX_PROCESSES];

void initialize()
{
    for(int i = 0;i < MAX_PROCESSES;i++)
    {
        printf("Enter the memory requirement of process %d\n", i);
        scanf("%d",&processes[i]);
    }

    for(int i = 0;i < MAX_SLOTS;i++)
    {
        printf("Enter the available memory in slot %d\n", i);
        scanf("%d",&slots[i]);
    }

    for (int i = 0;i < MAX_PROCESSES;i++)
    {
        finish[i] = 0;
    }
}

void firstFit()
{
    for (int i = 0;i < MAX_PROCESSES;i++)
    {
        if (finish[i] == 0)
        {
            for (int j = 0;j < MAX_SLOTS;j++)
            {
                if (processes[i] < slots[j])
                {
                    printf("Process %d assigned to slot %d\n",i ,j);
                    finish[i] = 1;
                    slots[j] = slots[j] - processes[i];
                    break;
                }
            }
        }
    }

    for(int i = 0;i < MAX_PROCESSES;i++)
    {
        if(finish[i] == 0)
        {
            printf("Memory can't be allocated for process %d\n",i);
        }
    }
}

int main()
{
    initialize();
    firstFit();
}
