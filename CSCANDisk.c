#include <stdio.h>
#include <stdlib.h>

#define MAX 200

void CSCAN(int* arr, int head, int size)
{
    for (int i = 0;i < size;i++)
    {
        for (int j = 0;j < size - i - 1;j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    /*for (int i = 0;i < size;i++)
    {
        printf("%d ",arr[i]);
    }*/

    int index = 0;

    for (int i = 0;i < size;i++)
    {
        if (arr[i] < head)
        {
            index = i;
        }
    }

    printf("Head moves from %d to 199\n", head);
    printf("Head moves from 199 to 0\n");
    printf("Head moves from 0 to %d\n", arr[index]);

    int headMovement = (199 - head) + (199 - 0) + (arr[index] - 0);

    printf("Total head movements: %d\n",headMovement);
}

int main()
{
    int sequence [] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int size = sizeof(sequence) / sizeof(sequence[0]);

    CSCAN(sequence, head, size);

    return 0;
}
