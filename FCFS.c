#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
};

// Function to calculate waiting time for each process
void findWaitingTime(struct Process processes[], int n, int wt[]) {
    wt[0] = 0;  // Waiting time for the first process is 0

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        wt[i] = processes[i - 1].burst + wt[i - 1];
    }
}

// Function to calculate turnaround time for each process
void findTurnAroundTime(struct Process processes[], int n, int wt[], int tat[]) {
    // Calculate turnaround time by adding burst time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = processes[i].burst + wt[i];
    }
}

// Function to calculate average time and display process details
void findAverageTime(struct Process processes[], int n) {
    int wt[n];      // Array to store waiting times
    int tat[n];     // Array to store turnaround times
    int total_wt = 0, total_tat = 0;

    // Calculate waiting time of all processes
    findWaitingTime(processes, n, wt);

    // Calculate turnaround time of all processes
    findTurnAroundTime(processes, n, wt, tat);

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Calculate average waiting time and average turnaround time
    float average_wt = (float)total_wt / n;
    float average_tat = (float)total_tat / n;

    // Display results
    printf("Processes  Arrival Time  Burst Time  Waiting Time  Turn-Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("   %d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival, processes[i].burst, wt[i], tat[i]);
    }

    printf("\nAverage waiting time: %.2f\n", average_wt);
    printf("Average turnaround time: %.2f\n", average_tat);
}

// Function to sort processes by arrival time
void sortProcessesByArrival(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    // Example processes
    struct Process processes[] = {
        {1, 0, 5},
        {2, 2, 3},
        {3, 4, 7},
        {4, 6, 2},
        {5, 8, 4}
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    // Sort processes by arrival time
    sortProcessesByArrival(processes, n);

    // Calculate average time
    findAverageTime(processes, n);

    return 0;
}
