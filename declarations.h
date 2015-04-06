#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct my_proc {
    int id;
    unsigned int start;
    unsigned int end;
    int turnaround;
    int wait_time;
};

typedef struct my_proc* Process;

Process fcfs_single;
Process fcfs_percore;
Process rr_percore;
Process rr_load;

void fnc_fcfs_single(Process);
void fnc_fcfs_percore(Process);
void fnc_rr_percore(Process);
void fnc_rr_load(Process);
