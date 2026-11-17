#include <iostream>
#include <vector>
#include <algorithm>
#include "fcfs.h"

using namespace std;

void fcfs(vector<Process>& patients)
{
    if (patients.empty())
    {
        cout << "\nNo patients available!\n";
        return;
    }

    // Sort according to Arrival Time
    stable_sort(patients.begin(), patients.end(),
        [](const Process& a, const Process& b)
        {
            return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0;

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    double totalResponseTime = 0;

    cout << "\n========== FCFS SCHEDULING ==========\n";

    cout << "\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n";

    for (auto &p : patients)
    {
        int startTime = max(currentTime, p.arrivalTime);

        p.firstStartTime = startTime;

        p.completionTime = startTime + p.burstTime;

        p.turnaroundTime =
            p.completionTime - p.arrivalTime;

        p.waitingTime =
            p.turnaroundTime - p.burstTime;

        p.responseTime =
            startTime - p.arrivalTime;

        p.remainingTime = 0;

        currentTime = p.completionTime;

        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
        totalResponseTime += p.responseTime;

        cout << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << startTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << endl;
    }

    cout << "\nAverage Waiting Time: "
         << totalWaitingTime / patients.size();

    cout << "\nAverage Turnaround Time: "
         << totalTurnaroundTime / patients.size();

    cout << "\nAverage Response Time: "
         << totalResponseTime / patients.size();

    cout << "\n\nFCFS Scheduling Completed!\n";
}
