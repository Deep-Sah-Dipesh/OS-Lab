#include <stdio.h>

#define HYPER_PERIOD 280

void schedule_RMS(int p1, int t1, int p2, int t2) {
    int time;
    int p1_execution_time_remaining = 0;
    int p2_execution_time_remaining = 0;
    int start_time = 0;
    int last_executed_process = -1;

    for (time = 0; time < HYPER_PERIOD; time++) {
        // Check if a new instance of P1 should start
        if (time % p1 == 0) {
            p1_execution_time_remaining = t1;
        }

        // Check if a new instance of P2 should start
        if (time % p2 == 0) {
            p2_execution_time_remaining = t2;
        }

        // Determine which process to run
        if (p1_execution_time_remaining > 0) {
            if (last_executed_process != 1) {
                if (last_executed_process != -1) {
                    printf("Time %d-%d: P%d running\n", start_time, time, last_executed_process);
                }
                start_time = time;
                last_executed_process = 1;
            }
            p1_execution_time_remaining--;
        } else if (p2_execution_time_remaining > 0) {
            if (last_executed_process != 2) {
                if (last_executed_process != -1) {
                    printf("Time %d-%d: P%d running\n", start_time, time, last_executed_process);
                }
                start_time = time;
                last_executed_process = 2;
            }
            p2_execution_time_remaining--;
        } else {
            if (last_executed_process != 0) {
                if (last_executed_process != -1) {
                    printf("Time %d-%d: P%d running\n", start_time, time, last_executed_process);
                }
                start_time = time;
                last_executed_process = 0;
            }
        }
    }

    // Print the final segment
    if (last_executed_process != -1) {
        printf("Time %d-%d: %s\n", start_time, time,
               last_executed_process == 0 ? "Idle" : "P" + last_executed_process);
    }
}

int main() {
    int p1 = 40, t1 = 20;
    int p2 = 70, t2 = 30;

    schedule_RMS(p1, t1, p2, t2);

    return 0;
}
