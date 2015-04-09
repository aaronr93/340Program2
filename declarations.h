#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef _DECLARATIONSH_
#define _DECLARATIONSH_

typedef struct {
    int id; //id of process
    int arrive; //arival time of process
    int duration; //duration of process
    int start; //the time it actually starts
    int finish; //finish time of process
    int turnaround;
    int wait_time;
    bool done; //is the process done executing?
} Process;

int numCores; //user wil input the number of cores


//Process * fcfs_single;
//Process * fcfs_percore;
//Process * rr_percore;
//Process * rr_load;
//
//void fnc_fcfs_single(Process *);
//void fnc_fcfs_percore(Process *);
//void fnc_rr_percore(Process *);
//void fnc_rr_load(Process *);

#endif
