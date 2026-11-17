#include <iostream>
#include <vector>
#include <algorithm>
#include "sjf.h"

using namespace std;

void sjf(vector<Process>& patients)
{
    if (patients.empty())
    {
        cout << "\nNo patients available!\n";
        return;
    }

    int n = patients.size();
    int currentTime = 0;
    int completed = 0;

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    double totalResponseTime = 0;

    vector<bool> isCompleted(n, false);

    cout << "\n========== SJF SCHEDULING ==========\n";

    cout << "\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n";

    while (completed < n)
    {
        int shortest = -1;
        int minimumBurst = 999999;

        // Find shortest available process
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] &&
                patients[i].arrivalTime <= currentTime)
            {
                if (patients[i].burstTime < minimumBurst)
                {
                    minimumBurst = patients[i].burstTime;
                    shortest = i;
                }
            }
        }

        // CPU Idle Handling
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }

        Process &p = patients[shortest];

        int startTime = currentTime;

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

        isCompleted[shortest] = true;
        completed++;

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
         << totalWaitingTime / n;

    cout << "\nAverage Turnaround Time: "
         << totalTurnaroundTime / n;

    cout << "\nAverage Response Time: "
         << totalResponseTime / n;

    cout << "\n\nSJF Scheduling Completed!\n";
}
