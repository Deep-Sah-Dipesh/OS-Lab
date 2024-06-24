#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to calculate the need matrix
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    calculateNeed(need, max, allot);

    bool finish[P] = {false}; // Array to track finished processes
    int safeSeq[P]; // Array to store safe sequence
    int work[R]; // Available resources array

    // Initialize work array with available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0; // Count of finished processes

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                // Check if all resources for process p can be allocated
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // Allocate resources to process p
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }

                    // Add process p to safe sequence
                    safeSeq[count++] = p;

                    // Mark process p as finished
                    finish[p] = true;

                    found = true;
                }
            }
        }

        if (!found) {
            // If no process could be allocated resources, break the loop
            break;
        }
    }

    // If all processes are finished, system is in a safe state
    if (count == P) {
        printf("System is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
        return true;
    } else {
        // If not all processes are finished, system is in an unsafe state
        printf("System is not in a safe state.\n");
        return false;
    }
}

int main() {
    int avail[R]; // Available instances of each resource type
    int max[P][R]; // Maximum instances needed by each process
    int allot[P][R]; // Currently allocated instances to each process

    // Input available instances of resources
    printf("Enter available instances of resources (R1 R2 R3): ");
    scanf("%d %d %d", &avail[0], &avail[1], &avail[2]);

    // Input maximum instances that each process needs
    printf("Enter maximum instances that each process needs (P1 P2 P3 P4 P5):\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &max[i][0], &max[i][1], &max[i][2]);
    }

    // Input resources currently allocated to each process
    printf("Enter resources allocated to each process (P1 P2 P3 P4 P5):\n");
    for (int i = 0; i < P; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &allot[i][0], &allot[i][1], &allot[i][2]);
    }

    // Check if the system is in a safe state
    if (!isSafe(avail, max, allot)) {
        printf("Deadlock detected or system is in an unsafe state.\n");
    }

    return 0;
}
