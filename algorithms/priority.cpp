#include <iostream>
#include <vector>
#include "priority.h"

using namespace std;

void priorityScheduling(vector<Process>& patients)
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

cout << "\n========== PRIORITY SCHEDULING ==========\n";
cout << "\nPID\tAT\tBT\tPriority\tST\tCT\tTAT\tWT\tRT\n";

while (completed < n)
{
    int highestPriority = -1;

    // Find highest priority available patient
    for (int i = 0; i < n; i++)
    {
        if (!isCompleted[i] &&
            patients[i].arrivalTime <= currentTime)
        {
            if (highestPriority == -1 ||
                patients[i].priority < patients[highestPriority].priority ||
                (patients[i].priority == patients[highestPriority].priority &&
                 patients[i].arrivalTime < patients[highestPriority].arrivalTime))
            {
                highestPriority = i;
            }
        }
    }

    // CPU Idle Handling
    if (highestPriority == -1)
    {
        currentTime++;
        continue;
    }

    Process &p = patients[highestPriority];

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

    isCompleted[highestPriority] = true;
    completed++;

    totalWaitingTime += p.waitingTime;
    totalTurnaroundTime += p.turnaroundTime;
    totalResponseTime += p.responseTime;

    cout << p.pid << "\t"
         << p.arrivalTime << "\t"
         << p.burstTime << "\t"
         << p.priority << "\t\t"
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

cout << "\n\nPriority Scheduling Completed!\n";

}
