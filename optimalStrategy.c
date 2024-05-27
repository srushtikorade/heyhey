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

// Function to find the page that will be referenced farthest in the future
int findOptimalPage(int pages[], int num_pages, int frames[], int num_frames, int current_index) {
    int farthest_index = -1;
    int farthest_distance = -1;

    for (int i = 0; i < num_frames; i++) {
        int page = frames[i];
        int future_index = -1;

        for (int j = current_index; j < num_pages; j++) {
            if (pages[j] == page) {
                future_index = j;
                break;
            }
        }

        if (future_index == -1) {
            return i; // Page will not be used in the future, so replace it
        }

        if (future_index > farthest_distance) {
            farthest_distance = future_index;
            farthest_index = i;
        }
    }

    return farthest_index;
}

// Function to implement Optimal page replacement algorithm
void optimalPageReplacement(int pages[], int num_pages) {
    int frames[MAX_FRAMES]; // Array to hold page frames in memory
    int page_faults = 0;

    initializeFrames(frames, MAX_FRAMES);

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int currentPage = pages[i];
        printf("%d\t", currentPage);

        // If the page is not already in memory, perform page replacement
        if (!isPagePresent(frames, MAX_FRAMES, currentPage)) {
            int replace_index = findOptimalPage(pages, num_pages, frames, MAX_FRAMES, i);
            frames[replace_index] = currentPage;
            page_faults++;
        }

        // Print the current frames in memory
        for (int j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    // Example array of page references
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    optimalPageReplacement(pages, num_pages);

    return 0;
}
