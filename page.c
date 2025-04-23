#include <stdio.h>
#include <stdbool.h>

struct PageTable {
    int frame_no;
    bool valid;
};

bool isPagePresent(struct PageTable PT[], int page) {
    return PT[page].valid;
}

void updatePageTable(struct PageTable PT[], int page, int frame_no, int status) {
    PT[page].valid = status;
    PT[page].frame_no = (status == 1) ? frame_no : -1;
}

void printFrameContents(int frame[], int no_of_frames) {
    printf("Frames: ");
    for (int i = 0; i < no_of_frames; i++) {
        if (frame[i] == -1)
            printf("- ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}

int main() {
    int n, no_of_frames, page_faults = 0, current = 0;
    bool frames_filled = false;

    printf("\nEnter the number of pages: ");
    scanf("%d", &n);

    int reference_string[n];
    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &reference_string[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &no_of_frames);

    int frame[no_of_frames];
    struct PageTable PT[50] = {0};

    for (int i = 0; i < no_of_frames; i++) {
        frame[i] = -1;
    }

    printf("\nFrame contents at different times:\n");
    for (int i = 0; i < n; i++) {
        int page = reference_string[i];
        printf("\nProcessing Page %d:\n", page);

        if (!isPagePresent(PT, page)) {
            page_faults++;

            if (!frames_filled) {
                frame[current] = page;
                updatePageTable(PT, page, current, 1);
                current++;

                if (current == no_of_frames) {
                    frames_filled = true;
                    current = 0;
                }
            } else {
                printf("Replacing page %d with page %d\n", frame[current], page);
                updatePageTable(PT, frame[current], current, 0);
                frame[current] = page;
                updatePageTable(PT, page, current, 1);
                current = (current + 1) % no_of_frames;
            }

            printFrameContents(frame, no_of_frames);
        } else {
            printf("Page %d is already in memory\n", page);
        }
    }

    printf("\nTotal Page Faults = %d\n", page_faults);
    printf("Page Fault Ratio = %.2f\n", (float)page_faults / n);
    printf("Page Hit Ratio = %.2f\n", 1 - ((float)page_faults / n));

    return 0;
}
