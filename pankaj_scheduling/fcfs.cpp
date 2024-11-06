#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>  // for std::setw

using namespace std;

class Process {
public:
    int pid;           // Process ID
    int arrival;       // Arrival time
    int burst;         // Burst time
    int priority;      // Priority (optional)
    int start;         // Start time
    int completion;    // Completion time
    int waiting;       // Waiting time
    int turnaround;    // Turnaround time

    // Constructor
    Process(int id, int arr, int bur, int pri = 0)
        : pid(id), arrival(arr), burst(bur), priority(pri), start(0), completion(0), waiting(0), turnaround(0) {}
};

// FCFS Scheduling Function
void fcfs(vector<Process>& processes) {
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0;

    // Calculate start, completion, waiting, and turnaround times
    for (auto& p : processes) {
        if (current_time < p.arrival) {
            current_time = p.arrival;
        }
        p.start = current_time;
        p.completion = current_time + p.burst;
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;
        current_time = p.completion;
    }
}

// Function to print process statistics
void print_stats(const vector<Process>& processes) {
    cout << "PID\tArrival\tBurst\tPriority\tStart\tCompletion\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority
             << "\t\t" << p.start << "\t" << p.completion << "\t\t" << p.waiting
             << "\t" << p.turnaround << endl;
    }
}

// Function to display the Gantt Chart
  // Ensure this is included for std::setw

#include <iomanip>  // For setw

void print_gantt_chart(const vector<Process>& processes) {
    cout << "\nGantt Chart:\n";

    // Print process labels in the Gantt Chart
    for (const auto& p : processes) {
        cout << "|  P" << p.pid << "  ";
    }
    cout << "|\n";

    // Print the timeline below the Gantt Chart
    int current_time = 0;
    for (const auto& p : processes) {
        cout << current_time << setw(7);  // Aligns each timestamp with process block
        current_time += p.burst;
    }
    cout << current_time << endl;  // Print the final completion time
}


int main() {
    // Sample processes
    vector<Process> process_list = {
        Process(1, 0, 8, 2),
        Process(2, 3, 4, 1),
        Process(3, 2, 9, 3),
        Process(4, 5, 5, 2)
    };

    // Run FCFS scheduling
    cout << "FCFS Scheduling:\n";
    fcfs(process_list);
    print_stats(process_list);

    // Print Gantt Chart
    print_gantt_chart(process_list);

    return 0;
}
