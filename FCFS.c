#include<stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int n, int bt[], int wt[], int at[], int ct[]) {
    int service_time[n];
    service_time[0] = at[0];
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        // Calculate service time for each process
        service_time[i] = service_time[i - 1] + bt[i - 1];

        // Calculate waiting time for each process
        wt[i] = service_time[i] - at[i];

        // If waiting time for a process is negative, make it zero
        if (wt[i] < 0)
            wt[i] = 0;
    }

    // Calculate completion time for each process
    for (int i = 0; i < n; i++) {
        ct[i] = service_time[i] + bt[i];
    }
}

// Function to find the turnaround time for all processes
void findTurnaroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        // Calculate turnaround time for each process
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average waiting and turnaround time
void findAvgTime(int n, int bt[], int at[]) {
    int wt[n], tat[n], ct[n];

    // Find waiting time of all processes
    findWaitingTime(n, bt, wt, at, ct);

    // Find turnaround time for all processes
    findTurnaroundTime(n, bt, wt, tat);

    // Calculate total waiting time and total turnaround time
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Calculate average waiting time and average turnaround time
    float avg_wt = (float)total_wt / n;
    float avg_tat = (float)total_tat / n;

    // Display the average waiting time and average turnaround time
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main() {
    // Number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Arrays to store arrival times and burst times of processes
    int arrival_time[n], burst_time[n];
    printf("Enter the arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
    }

    // Call function to calculate average waiting time and average turnaround time
    findAvgTime(n, burst_time, arrival_time);

    return 0;
}
