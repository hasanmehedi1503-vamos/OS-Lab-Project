#include <iostream>
#include <vector>
#include <set>
#include "patient/patient.h"
#include "algorithms/fcfs.h"

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
     fcfs(patients);
    return 0;
}
