#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
};

struct GanttSlot
{
    int processID;
    int startTime;
    int endTime;
};

// Comparator function to sort by arrival time, then by priority if arrival times are the same
bool compareArrivalAndPriority(Process a, Process b)
{
    if (a.arrivalTime == b.arrivalTime)
        return a.priority < b.priority; // Higher priority (lower number) comes first
    return a.arrivalTime < b.arrivalTime;
}

// Function to calculate completion, waiting, and turnaround times, and Gantt chart
void calculateTimes(vector<Process> &processes, vector<GanttSlot> &ganttChart)
{
    int currentTime = 0;

    for (auto &process : processes)
    {
        if (currentTime < process.arrivalTime) // CPU idle until process arrives
            currentTime = process.arrivalTime;

        // Record the start and end times for Gantt chart
        ganttChart.push_back({process.id, currentTime, currentTime + process.burstTime});

        process.completionTime = currentTime + process.burstTime;
        process.turnAroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnAroundTime - process.burstTime;
        currentTime = process.completionTime;
    }
}

// Function to display results and calculate average times
void displayResults(const vector<Process> &processes, const vector<GanttSlot> &ganttChart)
{
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    cout << "\nProcesses  Arrival Time  Burst Time  Priority  Waiting Time  Turnaround Time  Completion Time\n";
    for (const auto &process : processes)
    {
        totalWaitingTime += process.waitingTime;
        totalTurnAroundTime += process.turnAroundTime;
        cout << "   " << process.id << "\t\t" << process.arrivalTime << "\t\t"
             << process.burstTime << "\t\t" << process.priority << "\t\t"
             << process.waitingTime << "\t\t" << process.turnAroundTime << "\t\t"
             << process.completionTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / processes.size();
    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / processes.size();

    // Display Gantt chart
    cout << "\n\nGantt Chart:\n";
    for (const auto &slot : ganttChart)
    {
        cout << "| P" << slot.processID << " ";
    }
    cout << "|\n";

    for (const auto &slot : ganttChart)
    {
        cout << slot.startTime << setw(5);
    }
    cout << ganttChart.back().endTime << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    vector<GanttSlot> ganttChart;

    cout << "Enter arrival time, burst time, and priority for each process:\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Process " << processes[i].id << " - Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << processes[i].id << " - Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Process " << processes[i].id << " - Priority: ";
        cin >> processes[i].priority;
    }

    // Sort processes by arrival time and priority
    sort(processes.begin(), processes.end(), compareArrivalAndPriority);

    // Calculate times and Gantt chart
    calculateTimes(processes, ganttChart);

    // Display results and Gantt chart
    displayResults(processes, ganttChart);

    return 0;
}
