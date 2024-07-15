#include <stdio.h>

#define HYPER_PERIOD 150

typedef struct {
    int period;
    int execution_time;
    int remaining_time;
    int next_deadline;
} Process;

void schedule_EDF(Process processes[], int num_processes) {
    int time;
    int last_executed_process = -1;
    int start_time = 0;

    for (time = 0; time < HYPER_PERIOD; time++) {
        // Update deadlines and remaining times at the beginning of each period
        for (int i = 0; i < num_processes; i++) {
            if (time % processes[i].period == 0) {
                processes[i].remaining_time = processes[i].execution_time;
                processes[i].next_deadline = time + processes[i].period;
            }
        }

        // Find the process with the earliest deadline
        int earliest_deadline = HYPER_PERIOD + 1;
        int process_to_run = -1;
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0 && processes[i].next_deadline < earliest_deadline) {
                earliest_deadline = processes[i].next_deadline;
                process_to_run = i;
            }
        }

        // Schedule the process with the earliest deadline
        if (process_to_run != -1) {
            if (last_executed_process != process_to_run) {
                if (last_executed_process != -1) {
                    if (last_executed_process == -2) {
                        printf("Time %d-%d: Idle\n", start_time, time);
                    } else {
                        printf("Time %d-%d: P%d running\n", start_time, time, last_executed_process + 1);
                    }
                }
                start_time = time;
                last_executed_process = process_to_run;
            }
            processes[process_to_run].remaining_time--;
        } else {
            if (last_executed_process != -2) {
                if (last_executed_process != -1) {
                    printf("Time %d-%d: P%d running\n", start_time, time, last_executed_process + 1);
                }
                start_time = time;
                last_executed_process = -2;
            }
        }
    }

    // Print the final segment
    if (last_executed_process != -1) {
        if (last_executed_process == -2) {
            printf("Time %d-%d: Idle\n", start_time, time);
        } else {
            printf("Time %d-%d: P%d running\n", start_time, time, last_executed_process + 1);
        }
    }
}

int main() {
    Process processes[] = {
        {50, 25, 0, 50}, // P1: period, execution_time, remaining_time, next_deadline
        {75, 30, 0, 75}  // P2: period, execution_time, remaining_time, next_deadline
    };

    int num_processes = sizeof(processes) / sizeof(Process);

    schedule_EDF(processes, num_processes);

    return 0;
}
