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

// Function to find the least recently used page
int findLRUPage(int frames[], int num_frames, int access_time[]) {
    int lru_index = 0;
    int lru_time = access_time[0];

    for (int i = 1; i < num_frames; i++) {
        if (access_time[i] < lru_time) {
            lru_index = i;
            lru_time = access_time[i];
        }
    }

    return lru_index;
}

// Function to implement LRU page replacement algorithm
void lruPageReplacement(int pages[], int num_pages) {
    int frames[MAX_FRAMES]; // Array to hold page frames in memory
    int access_time[MAX_FRAMES]; // Array to hold access time for each page frame
    int page_faults = 0;

    initializeFrames(frames, MAX_FRAMES);
    for (int i = 0; i < MAX_FRAMES; i++) {
        access_time[i] = -1; // Initialize access time to -1
    }

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int currentPage = pages[i];
        printf("%d\t", currentPage);

        // If the page is not already in memory, perform page replacement
        if (!isPagePresent(frames, MAX_FRAMES, currentPage)) {
            int lru_index = findLRUPage(frames, MAX_FRAMES, access_time);
            frames[lru_index] = currentPage;
            access_time[lru_index] = i; // Update access time
            page_faults++;
        } else {
            // If the page is already in memory, update its access time
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == currentPage) {
                    access_time[j] = i; // Update access time
                    break;
                }
            }
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

    lruPageReplacement(pages, num_pages);

    return 0;
}
