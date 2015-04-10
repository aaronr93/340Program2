#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef _DECLARATIONSH_
#define _DECLARATIONSH_

typedef enum {FCFS_SINGLE, FCFS_PERCORE, RR_LOAD, RR_PERCORE} sched_policy;

struct Process_Config {
    char* policy;
    int quantum;
    int cores;      // Number of cores
    int id;         // id of process
    int arrive;     // Arival time of process
    int duration;   // Duration of process
    int start;      // The time it actually starts
    int finish;     // Finish time of process
    int turnaround;
    int wait_time;
    bool done;      // Is the process done executing?
    bool running;   // Is the process currently running?
};

typedef struct Process_Config Process;

/*Process* process_constructor(char* pol, int qua, int cor, int id, int arr, int dur) {
    Process* p = malloc(sizeof(Process));
    p->policy = pol;
    p->quantum = qua;
    p->cores = cor;
    p->id = id;
    p->arrive = arr;
    p->duration = dur;
    p->start = 0;
    p->finish = 0;
    p->turnaround = 0;
    p->wait_time = 0;
    p->done = true;
    return p;
}

void process_destructor(Process* p) {
    free(p->policy);
    free(p);
}*/

int numCores;

#endif
