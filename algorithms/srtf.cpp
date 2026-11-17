#include <iostream>
#include <vector>
#include <algorithm>
#include "srtf.h"

using namespace std;

struct SRTFEntry
{
    int pid;
    int start;
    int end;
};

void srtf(vector<Process>& patients)
{
    int n = patients.size();

    int completed = 0;
    int currentTime = 0;

    vector<SRTFEntry> ganttChart;

    while (completed < n)
    {
        int shortest = -1;
        int minRemaining = 999999;

        // Find process with shortest remaining time

        for (int i = 0; i < n; i++)
        {
            if (patients[i].arrivalTime <= currentTime &&
                patients[i].remainingTime > 0 &&
                patients[i].remainingTime < minRemaining)
            {
                minRemaining = patients[i].remainingTime;
                shortest = i;
            }
        }

        // CPU Idle condition

        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        Process &p = patients[shortest];

        // First response time

        if (p.firstStartTime == -1)
        {
            p.firstStartTime = currentTime;
            p.responseTime = currentTime - p.arrivalTime;
        }

        int start = currentTime;

        // Execute process for one time unit

        p.remainingTime--;
        currentTime++;

        // Gantt Chart

        if (!ganttChart.empty() &&
            ganttChart.back().pid == p.pid)
        {
            ganttChart.back().end = currentTime;
        }
        else
        {
            ganttChart.push_back(
                {p.pid, start, currentTime}
            );
        }

        // Process completed

        if (p.remainingTime == 0)
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

    cout << "\n========== SRTF GANTT CHART ==========\n";

    for (const auto &entry : ganttChart)
    {
        cout << entry.start << " -- P"
             << entry.pid << " -- ";
    }

    cout << currentTime << endl;

    // Display Scheduling Table

    cout << "\n========== SRTF SCHEDULING ==========\n";

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

    // Performance Metrics

    double totalWT = 0;
    double totalTAT = 0;

    for (const auto &p : patients)
    {
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
    }

    cout << "\n========== SRTF PERFORMANCE ==========\n";

    cout << "Average Waiting Time: "
         << totalWT / n << endl;

    cout << "Average Turnaround Time: "
         << totalTAT / n << endl;
}
