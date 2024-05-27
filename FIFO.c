#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3 // Number of frames in memory

// Function to initialize an empty page frame array
void initializeFrames(int frames[], int size) {
    for (int i = 0; i < size; i++) {
        frames[i] = -1; // -1 indicates an empty frame
    }
}

// Function to check if a page is present in the frames array
bool isPagePresent(int frames[], int size, int page) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to implement FIFO page replacement algorithm
void fifoPageReplacement(int pages[], int num_pages) {
    int frames[MAX_FRAMES]; // Array to hold page frames in memory
    int frameIndex = 0; // Index to keep track of the current frame to replace
    int pageFaults = 1;

    initializeFrames(frames, MAX_FRAMES);

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int currentPage = pages[i];
        printf("%d\t", currentPage);

        // If the page is not already in memory, replace the oldest page
        if (!isPagePresent(frames, MAX_FRAMES, currentPage)) {
            frames[frameIndex] = currentPage;
            frameIndex = (frameIndex + 1) % MAX_FRAMES; // Move to the next frame using circular buffer logic
            pageFaults++;
        }

        // Print the current frames in memory
        for (int j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Page faults: %d\n", pageFaults);
}

int main() {
    // Example array of page references
    int pages[] = {0, 1, 2, 3, 0, 4, 1, 0, 2, 3, 4};
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    fifoPageReplacement(pages, num_pages);

    return 0;
}
