#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_PROCESSORS 10

typedef struct processor {
    int num;
    int arrival_time;
    int burst_time;
    int completion_time;
    int tat;
    int wt;
    float rt; // Change rt to float for more accurate calculations
    int priority;
} processor;

int compareArrivalTime(const void *a, const void *b) {
    return ((processor *)a)->arrival_time - ((processor *)b)->arrival_time;
}

int main() {
    int n;
    printf("Enter the number of processors: ");
    scanf("%d", &n);

    processor p[MAX_PROCESSORS];

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time, burst time, and priority of processor %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].num = i + 1; // Start numbering from 1 for better readability
        p[i].rt = -1; // Initialize response time to -1
    }

    qsort(p, n, sizeof(processor), compareArrivalTime);

    int currentTime = 0;
    int completed = 0;
    int shortest_job = -1;
    int highest_priority = INT_MAX;

    int total_tat = 0; // Total Turnaround Time
    int total_wt = 0;  // Total Waiting Time
    float total_rt = 0;  // Total Response Time

    printf("Processor\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    while (completed < n) {
        highest_priority = INT_MAX;
        shortest_job = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= currentTime && p[i].burst_time > 0) {
                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    shortest_job = i;
                }
                if (p[i].rt == -1) { // Calculate response time only if it hasn't been set yet
                    p[i].rt = currentTime - p[i].arrival_time;
                }
            }
        }

        if (shortest_job == -1) {
            currentTime = p[completed].arrival_time;
        } else {
            p[shortest_job].burst_time--;
            currentTime++;

            if (p[shortest_job].burst_time == 0) {
                completed++;
                p[shortest_job].completion_time = currentTime;
                p[shortest_job].tat = p[shortest_job].completion_time - p[shortest_job].arrival_time;
                p[shortest_job].wt = p[shortest_job].tat - p[shortest_job].burst_time;
                total_tat += p[shortest_job].tat;
                total_wt += p[shortest_job].wt;
                total_rt += p[shortest_job].rt;
                printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%.2f\n", p[shortest_job].num, p[shortest_job].arrival_time,
                                                        p[shortest_job].burst_time + 1, p[shortest_job].completion_time,
                                                        p[shortest_job].tat, p[shortest_job].wt, p[shortest_job].rt);
            }
        }
    }

    // Calculate averages
    float avg_tat = (float)total_tat / n;
    float avg_wt = (float)total_wt / n;
    float avg_rt = total_rt / n;

    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Response Time: %.2f\n", avg_rt);

    return 0;
}