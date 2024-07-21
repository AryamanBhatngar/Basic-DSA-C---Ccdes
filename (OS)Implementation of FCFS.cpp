#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
};

void findWaitingTime(vector<Process>& processes, vector<int>& wt) {
    wt[0] = 0;  // Waiting time for the first process is 0

    // Calculate waiting time for each process
    for (int i = 1; i < processes.size(); i++) {
        wt[i] = processes[i - 1].burst + wt[i - 1];
    }
}

void findTurnAroundTime(vector<Process>& processes, vector<int>& wt, vector<int>& tat) {
    // Calculate turnaround time by adding burst time and waiting time
    for (int i = 0; i < processes.size(); i++) {
        tat[i] = processes[i].burst + wt[i];
    }
}

void findAverageTime(vector<Process>& processes) {
    int n = processes.size();
    vector<int> wt(n);      // Vector to store waiting times
    vector<int> tat(n);     // Vector to store turnaround times
    int total_wt = 0, total_tat = 0;

    // Calculate waiting time of all processes
    findWaitingTime(processes, wt);

    // Calculate turnaround time of all processes
    findTurnAroundTime(processes, wt, tat);

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Calculate average waiting time and average turnaround time
    float average_wt = (float)total_wt / n;
    float average_tat = (float)total_tat / n;

    // Display results
    cout << "Processes  Arrival Time  Burst Time  Waiting Time  Turn-Around Time\n";
    for (int i = 0; i < n; i++) {
        cout << "   " << processes[i].pid << "\t\t" << processes[i].arrival << "\t\t"
             << processes[i].burst << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "\nAverage waiting time: " << average_wt << endl;
    cout << "Average turnaround time: " << average_tat << endl;
}

int main() {
    // Example processes
    vector<Process> processes = {
        {1, 0, 5},
        {2, 2, 3},
        {3, 4, 7},
        {4, 6, 2},
        {5, 8, 4}
    };

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    // Calculate average time
    findAverageTime(processes);

    return 0;
}

