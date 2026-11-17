#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include <vector>
#include "../patient/patient.h"

void roundRobin(std::vector<Process>& patients, int quantum);

#endif
