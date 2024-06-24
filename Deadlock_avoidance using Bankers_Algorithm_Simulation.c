#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int n, m;

void input() {
    printf("Enter the number of processes and resource types: ");
    scanf("%d %d", &n, &m);

    printf("Enter available resources (R1 R2 ... Rm): ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter maximum demand of each process (R1 R2 ... Rm):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter allocated resources for each process (R1 R2 ... Rm):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    bool finish[MAX_PROCESSES] = {false};
    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[p][j];
                    }
                    finish[p] = true;
                    found = true;
                    count++;
                    break;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    return count == n;
}

int main() {
    input();
    if (isSafe()) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is not in a safe state.\n");
    }
    return 0;
}
