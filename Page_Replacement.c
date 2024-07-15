#include <stdio.h>

void FIFO(int pages[], int n, int capacity) {
    int frames[capacity], index = 0, pageFaults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % capacity;
            pageFaults++;
        }

        printf("Page: %d\tFrames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

void LRU(int pages[], int n, int capacity) {
    int frames[capacity], age[capacity], pageFaults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = age[i] = -1;

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                age[j] = i;
                break;
            }
        }

        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < capacity; j++) {
                if (age[j] < age[lru_index]) lru_index = j;
            }
            frames[lru_index] = pages[i];
            age[lru_index] = i;
            pageFaults++;
        }

        printf("Page: %d\tFrames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

void Optimal(int pages[], int n, int capacity) {
    int frames[capacity], pageFaults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int replace_index = -1, farthest = i + 1;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace_index = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replace_index = j;
                    break;
                }
            }
            if (replace_index == -1) replace_index = 0;
            frames[replace_index] = pages[i];
            pageFaults++;
        }

        printf("Page: %d\tFrames: ", pages[i]);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);

    return 0;
}
