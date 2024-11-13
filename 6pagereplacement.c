//O(f×n), 
// 7 0 1 2 0 3 0 4 2 3 0 3 1 2 0


#include <stdio.h>
#include <string.h>  // Added for strlen function

// Function implementing FIFO (First-In-First-Out) Page Replacement
void fifo(char string[], int frameSize, int count) {
    int faults = 0, front = 0, end = 0;  // Initialize fault count, front, and end pointers
    char frame[frameSize];  // Array to hold pages in memory frames

    printf("Page\tFrame\tPage Fault\n");
    printf("============================\n");

    // Iterate through each page in the reference string
    for (int i = 0; i < count; i++) {
        int found = 0;  // Variable to track if page is already in frame

        // Check if the page is already in the frame
        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;  // Page found in frame, no page fault
                break;
            }
        }

        // If page is not found in frame, we have a page fault
        if (!found) {
            faults++;  // Increment fault count
            if (end < frameSize) {
                // If frame has empty space, add page to the frame
                frame[end++] = string[i];
            } else {
                // If frame is full, replace the oldest page (FIFO order)
                frame[front] = string[i];
                front = (front + 1) % frameSize;  // Update front to point to the oldest page
            }

            // Print current page, frame content, and page fault status
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tY\n");
        } else {
            // If no page fault, print the frame content and 'N'
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    // Print total page faults after processing all pages
    printf("Total Page Faults: %d\n", faults);
}

// Function implementing LRU (Least Recently Used) Page Replacement
void lru(char string[], int frameSize, int count) {
    int faults = 0, end = 0;
    char frame[frameSize];          // Array to hold pages in memory frames
    int recent[frameSize];          // Array to track most recent usage of each page

    printf("Page\tFrame\tPage Fault\n");
    printf("============================\n");

    // Iterate through each page in the reference string
    for (int i = 0; i < count; i++) {
        int found = 0, min = 0;  // Variable to check if page is in frame, min to find LRU

        // Check if the page is already in the frame
        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;             // Page found in frame, no page fault
                recent[j] = i;         // Update recent array with current access
                break;
            }
        }

        // If page not found, page fault occurs
        if (!found) {
            faults++;  // Increment fault count

            if (end < frameSize) {
                // If frame has empty space, add page to the frame
                frame[end] = string[i];
                recent[end++] = i;  // Update recent usage
            } else {
                // Frame is full, find the least recently used page
                for (int j = 1; j < end; j++) {
                    if (recent[j] < recent[min]) 
                        min = j;  // Track index of least recently used page
                }
                // Replace the LRU page
                frame[min] = string[i];
                recent[min] = i;  // Update recent usage for replaced page
            }

            // Print current page, frame content, and page fault status
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tY\n");
        } else {
            // If no page fault, print the frame content and 'N'
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    // Print total page faults after processing all pages
    printf("\nTotal Page Faults: %d\n", faults);
}

// Function implementing Optimal Page Replacement
void optimal(char string[], int frameSize, int count) {
    int faults = 0, end = 0;
    char frame[frameSize];  // Array to hold pages in memory frames

    printf("Page\tFrame\tPage Fault\n");
    printf("============================\n");

    // Iterate through each page in the reference string
    for (int i = 0; i < count; i++) {
        int found = 0;  // Variable to check if page is in frame

        // Check if page is already in frame
        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;  // Page found in frame, no page fault
                break;
            }
        }

        // If page is not found, page fault occurs
        if (!found) {
            faults++;  // Increment fault count

            if (end < frameSize) {
                // If frame has empty space, add page to the frame
                frame[end++] = string[i];
            } else {
                // Frame is full, find the page that won't be used for the longest time
                int replace = -1, farthest = i;

                for (int j = 0; j < end; j++) {
                    int k;
                    // Find the next occurrence of each page in the frame
                    for (k = i + 1; k < count; k++) {
                        if (frame[j] == string[k]) break;
                    }
                    // Track the page that will be used the farthest in the future
                    if (k > farthest) {
                        farthest = k;
                        replace = j;
                    }
                }
                // Replace the page in frame at index replace
                frame[replace] = string[i];
            }

            // Print current page, frame content, and page fault status
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tY\n");
        } else {
            // If no page fault, print the frame content and 'N'
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tN\n");
        }
    }
    // Print total page faults after processing all pages
    printf("\nTotal Page Faults: %d\n", faults);
}

int main() {
    char string[50];
    int frameSize, count = 0, choice;

    // Take input for the reference string
    printf("Enter the reference string: ");
    scanf("%s", string);

    // Take input for frame size
    printf("Enter the frame size: ");
    scanf("%d", &frameSize);

    // Calculate the length of the reference string
    count = strlen(string);

    // Display menu and execute chosen page replacement algorithm
    do {
        printf("\nMenu:\n");
        printf("1. FIFO Page Replacement\n");
        printf("2. LRU Page Replacement\n");
        printf("3. Optimal Page Replacement\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                fifo(string, frameSize, count);  // Call FIFO function
                break;
            case 2:
                lru(string, frameSize, count);   // Call LRU function
                break;
            case 3:
                optimal(string, frameSize, count);  // Call Optimal function
                break;
            case 4:
                printf("Exiting program...\n");  // Exit program
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}









/*

1. FIFO (First-In-First-Out) Page Replacement Algorithm

In the FIFO page replacement algorithm, pages are replaced in the order they were loaded into the frame. When the frame reaches its full capacity, the page that was loaded first is removed to make room for the new page. This approach does not consider which page is the least or most frequently accessed but instead follows a simple rule of replacing the "oldest" page.

Steps in FIFO Algorithm:

    Check if the page is already in the frame: Loop through each page currently in the frame. If the page is found, there is no page fault.
    If page is not in frame (page fault):
        Increment the faults count.
        If there is still space in the frame (i.e., end < frameSize), the new page is added to the end of the frame.
        If the frame is full, replace the page at the front index with the new page and then update the front pointer to point to the next oldest page (by incrementing front in a circular manner).
    Display page fault and frame content: For each page access, print whether there was a page fault and the current contents of the frame.

2. LRU (Least Recently Used) Page Replacement Algorithm

The LRU algorithm replaces the page that has not been used for the longest period. The approach tracks the access history of each page in the frame to identify which page is the "least recently used." When a page fault occurs and the frame is full, it replaces the page with the oldest "recent usage" time.

Steps in LRU Algorithm:

    Check if the page is already in the frame:
        If the page is found, update its "last accessed" timestamp in the recent array. This marks the page as recently used.
    If page is not in frame (page fault):
        Increment the faults count.
        If there is space in the frame, add the page to the frame and update its recent access time.
        If the frame is full, locate the page with the oldest access time by searching the recent array. Replace that page with the new page and update the recent array to reflect the new page's access time.
    Display page fault and frame content: Print whether there was a page fault and the current contents of the frame after each page access.

3. Optimal Page Replacement Algorithm

The Optimal page replacement algorithm replaces the page that will not be used for the longest period in the future. This approach aims to minimize future page faults by preemptively removing the page that is least likely to be accessed soon. However, it requires knowing the entire reference string in advance, which limits its practical use.

Steps in Optimal Algorithm:

    Check if the page is already in the frame:
        If the page is found, no replacement is needed.
    If page is not in frame (page fault):
        Increment the faults count.
        If there is still space in the frame, add the new page.
        If the frame is full, the algorithm identifies which page in the frame will not be used for the longest time. This is done by:
            For each page currently in the frame, checking when it will next appear in the reference string.
            Keeping track of the page with the farthest next occurrence.
        Replace the page that has the farthest next occurrence with the new page.
    Display page fault and frame content: For each page access, print the page fault status and the frame content.
    */