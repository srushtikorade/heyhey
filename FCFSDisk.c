#include <stdio.h>
#include <stdlib.h>

#define MAX 200

void FCFSDisk(int* arr, int head, int size)
{
    int current = head;
    int headMovement = 0;

    for (int i = 0;i < size;i++)
    {
        printf("Head moved from %d to %d\n", current, arr[i]);
        headMovement = headMovement + abs(current - arr[i]);
        current = arr[i];

        //printf("%d\n", headMovement);
    }

    printf("Total head movements: %d\n",headMovement);
}

int main()
{
    int sequence [] = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int size = sizeof(sequence)/sizeof(sequence[0]);

    FCFSDisk(sequence, head, size);
}
