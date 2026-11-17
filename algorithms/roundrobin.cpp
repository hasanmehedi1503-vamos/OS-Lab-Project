#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "roundrobin.h"

using namespace std;

struct GanttEntry
{
    int pid;
    int start;
    int end;
};

void roundRobin(vector<Process>& patients, int quantum)
{
    if (quantum <= 0)
    {
        cout << "Invalid Time Quantum!\n";
        return;
    }

    int n = patients.size();
    int completed = 0;
    int currentTime = 0;

    queue<int> readyQueue;
    vector<bool> visited(n, false);
    vector<GanttEntry> ganttChart;

    sort(patients.begin(), patients.end(),
         [](Process a, Process b)
         {
             return a.arrivalTime < b.arrivalTime;
         });

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] &&
                patients[i].arrivalTime <= currentTime)
            {
                readyQueue.push(i);
                visited[i] = true;
            }
        }

        if (readyQueue.empty())
        {
            int start = currentTime;
            currentTime++;

            ganttChart.push_back({-1, start, currentTime});
            continue;
        }

        int index = readyQueue.front();
        readyQueue.pop();

        Process &p = patients[index];

        if (p.firstStartTime == -1)
        {
            p.firstStartTime = currentTime;
            p.responseTime = currentTime - p.arrivalTime;
        }

        int start = currentTime;

        int executionTime = min(quantum, p.remainingTime);

        currentTime += executionTime;
        p.remainingTime -= executionTime;

        ganttChart.push_back({p.pid, start, currentTime});

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] &&
                patients[i].arrivalTime <= currentTime)
            {
                readyQueue.push(i);
                visited[i] = true;
            }
        }

        if (p.remainingTime > 0)
        {
            readyQueue.push(index);
        }
        else
        {
            completed++;

            p.completionTime = currentTime;

            p.turnaroundTime =
                p.completionTime - p.arrivalTime;

            p.waitingTime =
                p.turnaroundTime - p.burstTime;
        }
    }

    // Display Gantt Chart

    cout << "\n========== ROUND ROBIN GANTT CHART ==========\n";

    for (const auto &entry : ganttChart)
    {
        cout << entry.start << " -- ";

        if (entry.pid == -1)
            cout << "IDLE";
        else
            cout << "P" << entry.pid;

        cout << " -- ";
    }

    cout << currentTime << endl;

    // Display Scheduling Table

    cout << "\n========== ROUND ROBIN SCHEDULING ==========\n";

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (const auto &p : patients)
    {
        cout << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << endl;
    }
double totalWT = 0;
double totalTAT = 0;

for (const auto &p : patients)
{
    totalWT += p.waitingTime;
    totalTAT += p.turnaroundTime;
}

cout << "\nAverage Waiting Time: "
     << totalWT / n << endl;

cout << "Average Turnaround Time: "
     << totalTAT / n << endl;
}
