#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Process {
public:
    int pid, arrival, burst, remaining, start, completion, waiting, turnaround;

    // Constructor to initialize process
    Process(int id, int arr, int bur)
        : pid(id), arrival(arr), burst(bur), remaining(bur), start(-1), completion(0), waiting(0), turnaround(0) {}
};

// SJF Preemptive Scheduling
void sjf_preemptive(vector<Process>& processes) {
    int current_time = 0, completed = 0;
    
    while (completed < processes.size()) {
        int idx = -1, min_remaining = INT_MAX;

        // Find process with the shortest remaining time
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 && processes[i].remaining < min_remaining) {
                min_remaining = processes[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) {  // No process to execute
            current_time++;
            continue;
        }

        Process &p = processes[idx];
        
        // Set start time and execute process for one unit
        if (p.start == -1) p.start = current_time;
        current_time++;
        p.remaining--;

        // If process is completed
        if (p.remaining == 0) {
            p.completion = current_time;
            p.turnaround = p.completion - p.arrival;
            p.waiting = p.turnaround - p.burst;
            completed++;
        }
    }
}

// Print the stats of processes
void print_stats(const vector<Process>& processes) {
    cout << "PID\tArrival\tBurst\tStart\tCompletion\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.start
             << "\t" << p.completion << "\t\t" << p.waiting << "\t" << p.turnaround << endl;
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
        cout << current_time << setw(7);
        current_time = p.completion;
    }
    cout << current_time << endl;  // Final time
}

int main() {
    vector<Process> processes = {
        Process(1, 0, 8),
        Process(2, 3, 4),
        Process(3, 2, 9),
        Process(4, 5, 5)
    };

    // Run SJF Preemptive scheduling
    cout << "SJF Preemptive Scheduling:\n";
    sjf_preemptive(processes);
    print_stats(processes);
    print_gantt_chart(processes);

    return 0;
}
