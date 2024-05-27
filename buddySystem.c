#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MEMORY_SIZE 1024
#define MIN_SIZE 32

#define MAX_PROCESSES 5

int processes[MAX_PROCESSES];

struct Node
{
    int size;
    bool free;
    struct Node* next;
};

void initialize()
{
    for(int i = 0; i < MAX_PROCESSES; i++)
    {
        printf("Enter the memory requirement for process %d\n", i);
        scanf("%d", &processes[i]);
    }
}

struct Node* initializeMemory()
{
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));

    root->size = MEMORY_SIZE;
    root->free = true;
    root->next = NULL;

    return root;
}

void split(struct Node* root)
{
    if (root->size < 2 * MIN_SIZE)
    {
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->size = root->size / 2;
    newNode->free = true;
    newNode->next = root->next;
    root->next = newNode;
    root->size = root->size / 2;
}

void buddySystem()
{
    struct Node* root = initializeMemory();

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        struct Node* current = root;

        while(current != NULL)
        {
            if (current->free == true && current->size / 2 < processes[i])
            {
                printf("Process %d allocated at memory block of size %d\n", i, current->size);

                current->free = false;
                break;
            }

            else if (current->free == true && current->size / 2 >= processes[i])
            {
                split(current);
                current = current->next;
                //break;
            }

            else
            {
                current = current->next;
            }
        }

        if (!current)
        {
            printf("Memory allocation failed for process %d\n", i);
        }
    }
}

int main()
{
    initialize();
    buddySystem();
    return 0;
}
