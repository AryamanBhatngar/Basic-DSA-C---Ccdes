#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
  int process_id;
  int arrival_time;
  int burst_time;
  int priority; // Higher value indicates higher priority
  int completion_time;
  int turnaround_time;
  int waiting_time;
};

bool compareArrival(const Process& p1, const Process& p2) {
  return p1.arrival_time < p2.arrival_time;
}

bool comparePriority(const Process& p1, const Process& p2) {
  // Higher priority processes come first
  return p1.priority > p2.priority;
}

vector<Process> priority(vector<Process>& processes) {
  // Sort processes by arrival time
  sort(processes.begin(), processes.end(), compareArrival);

  int current_time = 0;

  for (Process& process : processes) {
    // Adjust for processes arriving later than current time
    if (current_time < process.arrival_time) {
      current_time = process.arrival_time;
    }

    // Update completion time
    process.completion_time = current_time + process.burst_time;
    current_time = process.completion_time;

    // Update turnaround time and waiting time
    process.turnaround_time = process.completion_time - process.arrival_time;
    process.waiting_time = process.turnaround_time - process.burst_time;
  }

  return processes;
}

int main() {
  vector<Process> processes;

  // Get number of processes from user
  int num_processes;
  cout << "Enter the number of processes: ";
  cin >> num_processes;

  // Get process data for each process from user
  for (int i = 0; i < num_processes; ++i) {
    Process process;
    cout << "Enter details for process " << i + 1 << ":" << endl;
    cout << "Arrival Time: ";
    cin >> process.arrival_time;
    cout << "Burst Time: ";
    cin >> process.burst_time;
    cout << "Priority (higher value indicates higher priority): ";
    cin >> process.priority;
    process.process_id = i + 1;
    processes.push_back(process);
  }

  // Schedule processes using priority
  vector<Process> scheduled_processes = priority(processes);

  // Print results
  cout << "\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
  for (const Process& process : scheduled_processes) {
    cout << process.process_id << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << "\t\t"
         << process.priority << "\t\t" << process.completion_time << "\t\t" << process.turnaround_time << "\t\t" << process.waiting_time << endl;
  }

  return 0;
}
