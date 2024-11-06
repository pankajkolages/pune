#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define a structure for each process to store its attributes
struct Process
{
    int id;             // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time (CPU time required)
    int waitingTime;    // Waiting time for the process
    int turnAroundTime; // Turnaround time for the process
    int completionTime; // Completion time when process finishes
    int remainingTime;  // Remaining time for the process (initially equals burstTime)
};

// Define a structure for each time slot in the Gantt chart
struct GanttSlot
{
    int processId; // ID of the process
    int startTime; // Start time of the process in this time slot
    int endTime;   // End time of the process in this time slot
};

// Function to calculate waiting and completion times using Round Robin scheduling with arrival times
void calculateWaitingTimeAndTurnAroundTime(vector<Process> &processes, int quantum, vector<GanttSlot> &ganttChart)
{
    int t = 0;         // Initialize time to zero
    int completed = 0; // Track the number of completed processes
    int n = processes.size();

    // Sort processes by arrival time to handle them in the correct order
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.arrivalTime < b.arrivalTime; });

    // Loop until all processes are complete
    while (completed < n)
    {
        bool idle = true; // Check if CPU is idle during this loop

        // Iterate over all processes to simulate Round Robin scheduling
        for (auto &process : processes)
        {
            // Process must have arrived and should have remaining burst time to execute
            if (process.arrivalTime <= t && process.remainingTime > 0)
            {
                idle = false;      // CPU is not idle
                int startTime = t; // Start time for the current quantum slot

                // Calculate the execution time for the current quantum
                int execTime = min(process.remainingTime, quantum);
                t += execTime;                     // Increment the time by execTime
                process.remainingTime -= execTime; // Decrease remaining time

                // Add the time slot to the Gantt chart
                ganttChart.push_back({process.id, startTime, t});

                // If process is completed during this time slot, set its completion and waiting times
                if (process.remainingTime == 0)
                {
                    process.completionTime = t;
                    process.turnAroundTime = process.completionTime - process.arrivalTime;
                    process.waitingTime = process.turnAroundTime - process.burstTime;
                    completed++;
                }
            }
        }

        // If CPU was idle, increment time to the next arrival time
        if (idle)
        {
            t++;
        }
    }
}

// Function to display the scheduling results, including Gantt chart and average times
void displayResults(const vector<Process> &processes, const vector<GanttSlot> &ganttChart)
{
    int total_wt = 0, total_tat = 0;
    int n = processes.size();

    // Display table headers
    cout << "Process No  Arrival Time  Burst Time  Waiting Time  Turnaround Time  Completion Time\n";

    // Calculate and display times for each process
    for (const auto &process : processes)
    {
        total_wt += process.waitingTime;
        total_tat += process.turnAroundTime;

        cout << "   " << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t"
             << process.waitingTime << "\t\t" << process.turnAroundTime << "\t\t" << process.completionTime << endl;
    }

    // Display Gantt chart
    cout << "\nGantt Chart:\n";
    for (const auto &slot : ganttChart)
    {
        cout << "| P" << slot.processId << " (" << slot.startTime << "-" << slot.endTime << ") ";
    }
    cout << "|\n";

    // Calculate and display average times
    cout << "Average Waiting Time: " << (float)total_wt / n << endl;
    cout << "Average Turnaround Time: " << (float)total_tat / n << endl;
}

int main()
{
    int n, quantum;
    cout << "Enter the total number of processes: ";
    cin >> n;

    vector<Process> processes(n); // Vector to store all processes

    // Input arrival time and burst time for each process and initialize remaining time
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Process " << processes[i].id << " - Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << processes[i].id << " - Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Input time quantum for Round Robin scheduling
    cout << "Enter time quantum: ";
    cin >> quantum;

    vector<GanttSlot> ganttChart; // Vector to store Gantt chart slots

    // Perform Round Robin calculations
    calculateWaitingTimeAndTurnAroundTime(processes, quantum, ganttChart);

    // Display results
    displayResults(processes, ganttChart);

    return 0;
}
