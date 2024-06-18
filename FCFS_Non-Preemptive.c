#include <stdio.h>

// Structure to represent a process
struct Process {
    int burst_time; // Burst time of the process
    int waiting_time; // Waiting time for the process
    int turnaround_time; // Turnaround time for the process
};

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input burst times for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Calculate waiting time for each process
    processes[0].waiting_time = 0; // First process doesn't wait
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    // Display results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
