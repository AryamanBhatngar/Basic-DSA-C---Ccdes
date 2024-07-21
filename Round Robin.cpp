#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
  int process_id;
  int arrival_time;
  int burst_time;
  int remaining_burst_time; // Remaining burst time for scheduling
  int completion_time;
  int turnaround_time;
  int waiting_time;
};

bool compareArrival(const Process& p1, const Process& p2) {
  return p1.arrival_time < p2.arrival_time;
}

vector<Process> roundRobin(vector<Process>& processes, int time_quantum) {
  // Sort processes by arrival time for fair scheduling
  sort(processes.begin(), processes.end(), compareArrival);

  int current_time = 0;
  queue<Process> ready_queue;

  for (Process& process : processes) {
    ready_queue.push(process);
  }

  while (!ready_queue.empty()) {
    Process process = ready_queue.front();
    ready_queue.pop();

    // Adjust for processes arriving later than current time (idle CPU)
    if (current_time < process.arrival_time) {
      current_time = process.arrival_time;
    }

    // Execute the process for the time quantum or remaining burst time (whichever is less)
    int executed_time = min(time_quantum, process.remaining_burst_time);
    process.remaining_burst_time -= executed_time;
    current_time += executed_time;

    // Check for process completion
    if (process.remaining_burst_time == 0) {
      process.completion_time = current_time;
      process.turnaround_time = process.completion_time - process.arrival_time;
      process.waiting_time = process.turnaround_time - process.burst_time;
    } else {
      // Add the process back to the queue for next round (avoid starvation)
      ready_queue.push(process);
    }
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
    process.process_id = i + 1;
    process.remaining_burst_time = process.burst_time; // Initialize remaining burst time
    processes.push_back(process);
  }

  // Get time quantum from user
  int time_quantum;
  cout << "Enter the time quantum: ";
  cin >> time_quantum;

  // Schedule processes using Round Robin
  vector<Process> scheduled_processes = roundRobin(processes, time_quantum);

  // Print results
  cout << "\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
  for (const Process& process : scheduled_processes) {
    cout << process.process_id << "\t\t" << process.arrival_time << "\t\t" << process.burst_time << "\t\t"
         << process.completion_time << "\t\t" << process.turnaround_time << "\t\t" << process.waiting_time << endl;
  }

  return 0;
}
