/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:   This file contains declarations for program 2
  Compile with:  make all
  Run with:      ./program2 input.txt

*/
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

Process* coll[100];

int numCores;
int quantum;
int num_processes;


#endif
