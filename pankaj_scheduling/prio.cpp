#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>  // for std::setw

using namespace std;

class Process {
public:
    int pid, arrival, burst, priority, start, completion, waiting, turnaround;

    // Constructor to initialize process
    Process(int id, int arr, int bur, int pri)
        : pid(id), arrival(arr), burst(bur), priority(pri), start(-1), completion(0), waiting(0), turnaround(0) {}
};

// Priority Scheduling (Non-preemptive)
void priority_scheduling(vector<Process>& processes) {
    int current_time = 0, completed = 0;
    
    // Process the processes in order of arrival time and priority
    while (completed < processes.size()) {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Find the process with highest priority (lower priority number)
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival <= current_time && processes[i].completion == 0 && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {  // No process is ready to execute
            current_time++;
            continue;
        }

        Process &p = processes[idx];

        // Set start time for the process
        if (p.start == -1) {
            p.start = current_time;
        }

        // Execute the process
        current_time += p.burst;
        p.completion = current_time;
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;

        completed++;
    }
}

// Print the stats of processes
void print_stats(const vector<Process>& processes) {
    cout << "PID\tArrival\tBurst\tPriority\tStart\tCompletion\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority
             << "\t\t" << p.start << "\t" << p.completion << "\t\t" << p.waiting
             << "\t" << p.turnaround << endl;
    }
}

// Display the Gantt Chart
void print_gantt_chart(const vector<Process>& processes) {
    cout << "\nGantt Chart:\n";
    
    // Print the process blocks
    for (const auto& p : processes) {
        cout << "|  P" << p.pid << "  ";
    }
    cout << "|\n";

    // Print timeline
    int current_time = 0;
    for (const auto& p : processes) {
        cout << current_time << setw(6);
        current_time = p.completion;
    }
    cout << current_time << endl;  // Final time
}

int main() {
    vector<Process> processes = {
        Process(1, 0, 8, 2),  // Process 1: arrival=0, burst=8, priority=2
        Process(2, 1, 4, 1),  // Process 2: arrival=1, burst=4, priority=1
        Process(3, 2, 9, 3),  // Process 3: arrival=2, burst=9, priority=3
        Process(4, 3, 5, 2)   // Process 4: arrival=3, burst=5, priority=2
    };

    // Run Priority Scheduling
    cout << "Priority Scheduling:\n";
    priority_scheduling(processes);
    print_stats(processes);
    print_gantt_chart(processes);

    return 0;
}
