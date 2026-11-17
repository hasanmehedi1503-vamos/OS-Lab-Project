#include <iostream>
#include <vector>
#include <algorithm>

#include "fcfs.h"

using namespace std;

void fcfs(vector<Process>& patients)
{
    // Sort patients according to Arrival Time
    sort(patients.begin(), patients.end(),
         [](Process a, Process b)
         {
             return a.arrivalTime < b.arrivalTime;
         });

    int currentTime = 0;

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    cout << "\n========== FCFS SCHEDULING ==========\n";

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto &p : patients)
    {
        // Find starting time
        int startTime = max(currentTime, p.arrivalTime);

        p.firstStartTime = startTime;

        // Calculate Completion Time
        p.completionTime = startTime + p.burstTime;

        // Calculate Turnaround Time
        p.turnaroundTime = p.completionTime - p.arrivalTime;

        // Calculate Waiting Time
        p.waitingTime = p.turnaroundTime - p.burstTime;

        // Calculate Response Time
        p.responseTime = startTime - p.arrivalTime;

        // Update current time
        currentTime = p.completionTime;

        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;

        cout << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << endl;
    }

    cout << "\nAverage Waiting Time: "
         << totalWaitingTime / patients.size();

    cout << "\nAverage Turnaround Time: "
         << totalTurnaroundTime / patients.size();

    cout << "\n\nFCFS Scheduling Completed!\n";
}
