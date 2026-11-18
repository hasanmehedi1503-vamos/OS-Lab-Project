#include <iostream>
#include <vector>
#include <set>

#include "patient/patient.h"
#include "algorithms/fcfs.h"
#include "algorithms/sjf.h"
#include "algorithms/priority.h"
#include "algorithms/roundrobin.h"
#include "algorithms/srtf.h"
#include <iomanip>



using namespace std;

int main()
{
    int n;

    vector<Process> patients;
    set<int> usedIDs;

    cout << "=================================\n";
    cout << " HOSPITAL EMERGENCY SYSTEM\n";
    cout << " CPU SCHEDULING SIMULATOR\n";
    cout << "=================================\n";

    cout << "Enter number of patients: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid number of patients!\n";
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        Process p;

        cout << "\nEnter information for Patient "
             << i + 1 << endl;

        cout << "Patient ID: ";
        cin >> p.pid;

        if (cin.fail() || p.pid <= 0 ||
            usedIDs.count(p.pid))
        {
            cout << "Invalid or duplicate Patient ID!\n";
            return 0;
        }

        usedIDs.insert(p.pid);

        cout << "Arrival Time: ";
        cin >> p.arrivalTime;

        if (cin.fail() || p.arrivalTime < 0)
        {
            cout << "Invalid Arrival Time!\n";
            return 0;
        }

        cout << "Treatment Time: ";
        cin >> p.burstTime;

        if (cin.fail() || p.burstTime <= 0)
        {
            cout << "Invalid Treatment Time!\n";
            return 0;
        }

        cout << "Priority: ";
        cin >> p.priority;

        if (cin.fail() || p.priority <= 0)
        {
            cout << "Invalid Priority!\n";
            return 0;
        }

        p.completionTime = 0;
        p.turnaroundTime = 0;
        p.waitingTime = 0;
        p.responseTime = 0;
        p.remainingTime = p.burstTime;
        p.firstStartTime = -1;

        patients.push_back(p);
    }

    cout << "\n========== PATIENT LIST ==========\n";

    cout << "PID\tArrival\tTreatment\tPriority\n";

    for (const auto &p : patients)
    {
        cout << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t\t"
             << p.priority << endl;
    }

    cout << "\nPatient information saved successfully!\n";
     vector<Process> fcfsPatients = patients;
vector<Process> sjfPatients = patients;
vector<Process> priorityPatients = patients;
vector<Process> rrPatients = patients;
vector<Process> srtfPatients = patients;

fcfs(fcfsPatients);

sjf(sjfPatients);

priorityScheduling(priorityPatients);

int quantum;

cout << "\nEnter Time Quantum for Round Robin: ";
cin >> quantum;

if (cin.fail() || quantum <= 0)
{
    cout << "Invalid Time Quantum!\n";
    return 0;
}

roundRobin(rrPatients, quantum);

srtf(srtfPatients);
// Performance Comparison

cout << "\n\n========== SCHEDULING PERFORMANCE COMPARISON ==========\n";

cout << left
     << setw(15) << "Algorithm"
     << setw(15) << "Avg WT"
     << setw(15) << "Avg TAT"
     << setw(15) << "Avg RT" << endl;

cout << "------------------------------------------------------------\n";

// Function to calculate average metrics

auto showPerformance = [](string name, vector<Process>& data)
{
    double totalWT = 0;
    double totalTAT = 0;
    double totalRT = 0;

    for (const auto &p : data)
    {
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
        totalRT += p.responseTime;
    }

    int n = data.size();

    cout << left
         << setw(15) << name
         << setw(15) << fixed << setprecision(2) << totalWT / n
         << setw(15) << totalTAT / n
         << setw(15) << totalRT / n
         << endl;
};

// Display all algorithm results

showPerformance("FCFS", fcfsPatients);

showPerformance("SJF", sjfPatients);

showPerformance("Priority", priorityPatients);

showPerformance("Round Robin", rrPatients);

showPerformance("SRTF", srtfPatients);

cout << "============================================================\n";

// Best Scheduling Algorithm Detection

cout << "\n\n========== BEST SCHEDULING ALGORITHM ==========\n";

struct Performance
{
    string name;
    double avgWT;
    double avgTAT;
    double avgRT;
};

auto calculatePerformance = [](string name, vector<Process>& data)
{
    Performance result;

    double totalWT = 0;
    double totalTAT = 0;
    double totalRT = 0;

    for (const auto &p : data)
    {
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
        totalRT += p.responseTime;
    }

    result.name = name;
    result.avgWT = totalWT / data.size();
    result.avgTAT = totalTAT / data.size();
    result.avgRT = totalRT / data.size();

    return result;
};

vector<Performance> results = {
    calculatePerformance("FCFS", fcfsPatients),
    calculatePerformance("SJF", sjfPatients),
    calculatePerformance("Priority", priorityPatients),
    calculatePerformance("Round Robin", rrPatients),
    calculatePerformance("SRTF", srtfPatients)
};

int bestIndex = 0;
double bestScore = 1e18;

for (int i = 0; i < results.size(); i++)
{
    double score = results[i].avgWT
                 + results[i].avgTAT
                 + results[i].avgRT;

    if (score < bestScore)
    {
        bestScore = score;
        bestIndex = i;
    }
}

cout << "\nAlgorithm Performance Scores:\n";

for (const auto &r : results)
{
    double score = r.avgWT + r.avgTAT + r.avgRT;

    cout << left << setw(15) << r.name
         << "Score: " << fixed << setprecision(2)
         << score << endl;
}



// Tie Detection

vector<int> bestAlgorithms;

for (int i = 0; i < results.size(); i++)
{
    double score = results[i].avgWT
                 + results[i].avgTAT
                 + results[i].avgRT;

    if (score <= bestScore + 0.001)
    {
        bestAlgorithms.push_back(i);
    }
}

cout << "\n------------------------------------------\n";

if (bestAlgorithms.size() == 1)
{
    cout << "BEST SCHEDULING ALGORITHM: "
         << results[bestAlgorithms[0]].name << endl;
}
else
{
    cout << "MULTIPLE BEST SCHEDULING ALGORITHMS:\n";

    for (int index : bestAlgorithms)
    {
        cout << results[index].name << endl;
    }
}

cout << "\nBEST ALGORITHM PERFORMANCE DETAILS\n";

for (int index : bestAlgorithms)
{
    cout << "\nAlgorithm: " << results[index].name << endl;
    cout << "Average WT: " << results[index].avgWT << endl;
    cout << "Average TAT: " << results[index].avgTAT << endl;
    cout << "Average RT: " << results[index].avgRT << endl;
}

cout << "------------------------------------------\n";

return 0;
    return 0;
}
