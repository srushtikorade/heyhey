#include <stdio.h>
#include <stdlib.h>

#define MAX 200

// Function to calculate the absolute difference between two numbers
int absDiff(int a, int b) {
    return abs(a - b);
}

// Function to find the index of the closest request to the current head position
int findClosestRequest(int* arr, int head, int size, int visited[]) {
    int minDiff = MAX;
    int minIndex = -1;

    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            int diff = absDiff(head, arr[i]);
            if (diff < minDiff) {
                minDiff = diff;
                minIndex = i;
            }
        }
    }

    return minIndex;
}

void SSTFDisk(int* arr, int head, int size) {
    int headMovement = 0;
    int visited[MAX] = {0}; // Array to keep track of visited requests

    for (int i = 0; i < size; i++) {
        int closestIndex = findClosestRequest(arr, head, size, visited);
        visited[closestIndex] = 1; // Mark the request as visited
        printf("Head moved from %d to %d\n", head, arr[closestIndex]);
        headMovement += absDiff(head, arr[closestIndex]);
        head = arr[closestIndex];
    }

    printf("Total head movements: %d\n", headMovement);
}

int main() {
    int sequence [] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int size = sizeof(sequence) / sizeof(sequence[0]);

    SSTFDisk(sequence, head, size);

    return 0;
}
