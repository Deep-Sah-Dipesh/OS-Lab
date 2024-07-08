#include<stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    float turnaround_time;
    float waiting_time;
    float response_time;
};

void priorityScheduling(struct Process[], int);

int main() {
    int n, i;
    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("\nEnter the details of processes:\n");
    for(i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        processes[i].id = i + 1;
        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = -1; // Initialize to -1 indicating not yet started
    }

    // Sort processes based on arrival time
    struct Process temp;
    for(i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(processes[j].arrival_time > processes[j+1].arrival_time) {
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }

    priorityScheduling(processes, n);

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t%.2f\t%.2f\t%.2f\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time, processes[i].response_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        total_response_time += processes[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Response Time: %.2f\n", total_response_time / n);

    return 0;
}

void priorityScheduling(struct Process processes[], int n) {
    int i, j;
    struct Process temp;

    // Sort processes based on priority
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(processes[j].priority > processes[j+1].priority) {
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }

    int current_time = processes[0].arrival_time;
    for(i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;
        if (processes[i].response_time == -1) // First time processing
            processes[i].response_time = current_time - processes[i].arrival_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        current_time = processes[i].completion_time;
    }
}