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
<<<<<<< HEAD
    bool done;      // Is the process done executing?
};

typedef struct Process_Config Process;
=======
    bool done; //is the process done executing?
	bool running; //is the process currently running?
} Process;
>>>>>>> 9c8ad9fa8eb6ec19834aec1143bbc3775da975a2

Process* process_constructor(char* pol, int qua, int cor, int id, int arr, int dur) {
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
}

void process_output(Process* p, int num_processes) {
    int i;          // Iterator
    int sum_t = 0;  // Sum of turnaround times, used for avg
    int sum_w = 0;  // Sum of wait times, used for average
    for (i = 0; i < num_processes; i++) {
		printf("\nID = %d\t\tSTART = %d\t\tEND = %d\t\tTURNAROUND = %d\t\tWAIT = %d\n",
            p[i].id,
            p[i].start,
            p[i].finish,
            p[i].finish - p[i].arrive,
            p[i].start - p[i].arrive
        );
        sum_t += p[i].finish - p[i].arrive;     // Accrue turnaround
        sum_w += p[i].start - p[i].arrive;      // Accrue wait
	}
    printf("\nAVG TURNAROUND = %d\t\tAVG WAIT = \n\n", sum_t / num_processes, sum_w / num_processes);
}

#endif
