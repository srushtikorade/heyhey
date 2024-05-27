#include <stdio.h>
#include <stdlib.h>

#define MAX 200

void SCAN(int* arr, int head, int size)
{
    for (int i = 0;i < size;i++)
    {
        for (int j = 0;j < size -  i - 1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    printf("Head moves from %d to 0\n", head);
    printf("Head moves from 0 to %d\n", arr[size - 1]);

    int headMovement = 0;

    int left = abs(head - 0);
    int right = abs(arr[size-1] - 0);

    headMovement = left + right;

    printf("Total head movements: %d\n",headMovement);
}

int main()
{
    int sequence [] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int size = sizeof(sequence) / sizeof(sequence[0]);

    SCAN(sequence, head, size);

    return 0;
}
