#include <iostream>
#include <iomanip>
using namespace std;

void findCompletionTime(int processes[], int n, int bt[], int at[], int ct[])
{
    ct[0] = at[0] + bt[0]; // Completion time for the first process
    for (int i = 1; i < n; i++)
    {
        if (at[i] > ct[i - 1]) // If the next process arrives after the previous one finishes
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];
    }
}

void findWaitingTime(int processes[], int n, int bt[], int at[], int ct[], int wt[])
{
    for (int i = 0; i < n; i++)
    {
        wt[i] = ct[i] - at[i] - bt[i]; // Waiting time = Completion time - Arrival time - Burst time
        if (wt[i] < 0)
            wt[i] = 0; // In case a process arrives after its turn
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int at[], int ct[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i]; // Turnaround time = Completion time - Arrival time
    }
}

void findAverageTime(int processes[], int n, int bt[], int at[])
{
    int wt[n], tat[n], ct[n];
    int total_wt = 0, total_tat = 0;

    findCompletionTime(processes, n, bt, at, ct);
    findWaitingTime(processes, n, bt, at, ct, wt);
    findTurnAroundTime(processes, n, bt, at, ct, tat);

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << "  " << processes[i] << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i]
             << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)total_wt / n;
    cout << "\nAverage Turnaround Time: " << (float)total_tat / n;

    // Gantt chart
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "|  P" << processes[i] << "  ";
    }
    cout << "|\n";

    int time = 0;
    for (int i = 0; i < n; i++)
    {
        cout << time << setw(6) << "";
        time = ct[i];
    }
    cout << time << endl;
}

int main()
{
    int n;
    cout << "Enter total number of processes: ";
    cin >> n;

    int processes[n], bt[n], at[n];
    cout << "\nEnter arrival time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        processes[i] = i + 1;
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> at[i];
    }

    cout << "\nEnter burst time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> bt[i];
    }

    findAverageTime(processes, n, bt, at);
    return 0;
}
