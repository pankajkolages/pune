#include <iostream>
#include <climits>
#include <iomanip>
#include <vector> // for Gantt chart
using namespace std;

struct Process
{
    int id;             // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time of the process
    int remainingTime;  // Remaining burst time (initially set to burstTime)
    int completionTime; // Completion time of the process
    int waitingTime;    // Waiting time calculated for the process
    int turnAroundTime; // Turnaround time calculated for the process
};

struct GanttSlot
{
    int processID; // ID of the process in this slot
    int startTime; // Start time of this slot
    int endTime;   // End time of this slot
};

// Function to find waiting and turnaround times for each process
void findWaitingAndTurnAroundTimes(Process processes[], int n, vector<GanttSlot> &ganttChart)
{
    int completed = 0, currentTime = 0, minRemainingTime;
    int shortest = -1;
    bool found;

    // Initialize remaining times and completion status
    for (int i = 0; i < n; i++)
    {
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Loop until all processes are complete
    while (completed != n)
    {
        minRemainingTime = INT_MAX;
        found = false;

        // Find the process with the minimum remaining time among those that have arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].remainingTime < minRemainingTime)
            {
                minRemainingTime = processes[i].remainingTime;
                shortest = i;
                found = true;
            }
        }

        // If no process found, increment time
        if (!found)
        {
            currentTime++;
            continue;
        }

        // Add Gantt chart entry if process changes
        if (ganttChart.empty() || ganttChart.back().processID != processes[shortest].id)
        {
            ganttChart.push_back({processes[shortest].id, currentTime, currentTime + 1});
        }
        else
        {
            ganttChart.back().endTime++; // Extend the current Gantt slot
        }

        // Reduce remaining time by 1
        processes[shortest].remainingTime--;

        // If a process is completed
        if (processes[shortest].remainingTime == 0)
        {
            completed++;
            processes[shortest].completionTime = currentTime + 1;
            processes[shortest].turnAroundTime = processes[shortest].completionTime - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnAroundTime - processes[shortest].burstTime;
        }

        // Increment time for next iteration
        currentTime++;
    }
}

// Function to calculate average waiting and turnaround times and print results
void findAverageTimes(Process processes[], int n)
{
    int totalWaitingTime = 0, totalTurnAroundTime = 0;
    vector<GanttSlot> ganttChart;

    findWaitingAndTurnAroundTimes(processes, n, ganttChart);

    // Print Gantt chart
    cout << "\nGantt Chart:\n";
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

    // Print process details
    cout << "\nProcesses  Arrival Time  Burst Time  Waiting Time  Turnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        cout << "   " << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t"
             << processes[i].turnAroundTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n;
    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1; // Assign process ID
        cout << "Process " << processes[i].id << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }

    findAverageTimes(processes, n);

    return 0;
}

