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

void worstFit()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (finish[i] == 0)
        {
            int bestSlot = -1;
            int maxSize = INT_MIN; // Initialize minimum size to maximum possible value
            for (int j = 0; j < MAX_SLOTS; j++)
            {
                if (slots[j] >= processes[i] && slots[j] > maxSize)
                {
                    maxSize = slots[j];
                    bestSlot = j;
                }
            }
            if (bestSlot != -1)
            {
                printf("Process %d assigned to slot %d\n", i, bestSlot);
                finish[i] = 1;
                slots[bestSlot] -= processes[i];
            }
            else
            {
                printf("Memory can't be allocated for process %d\n", i);
            }
        }
    }
}

int main()
{
    initialize();
    worstFit();
}

