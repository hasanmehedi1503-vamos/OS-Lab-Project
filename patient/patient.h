#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;

    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;

    int remainingTime;
    int firstStartTime;
};

#endif
