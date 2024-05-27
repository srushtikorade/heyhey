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

void nextFit()
{
    int currentSlot = 0; // Start from the first slot
    int completed = 0;
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (finish[i] == 0)
        {
            while (currentSlot < MAX_SLOTS && completed < MAX_SLOTS)
            {
                if (processes[i] <= slots[currentSlot])
                {
                    printf("Process %d assigned to slot %d\n", i, currentSlot);
                    finish[i] = 1;
                    slots[currentSlot] -= processes[i];
                    break;
                }
                currentSlot = (currentSlot + 1) % MAX_SLOTS; // Move to the next slot
                completed++;
            }
        }
        //printf("%d",i);
    }

    for (int i = 0;i < MAX_PROCESSES;i++)
    {
        if (finish[i] == 0)
        {
            printf("Memory can't be allocated for process %d\n", i);
        }
    }
}

int main()
{
    initialize();
    nextFit();
}
