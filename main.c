/*
  Author:  Zach Nafziger and Aaron Rosenberger
  Course:  COMP 340, Operating Systems
  Date:    10 March 2015
  Description:   This file implements the main driver
  Compile with:  make all
  Run with:      ./program2 input.txt

*/
#include "declarations.h"

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

int main(int argc, char** argv) {
    FILE *ifp, *ofp;
    char *mode = "r";
    char output_filename[] = "out.txt";
	char line[50];

	char * pol;

    ifp = fopen(argv[1], mode);

    if (ifp == NULL) {
        fprintf(stderr, "Can't open input file.\n");
        exit(1);
    }

    char eof;
    int qua, cor, id, arr, dur;
    num_processes = 0;

    int i = 0;
	fgets(line, 50, ifp);
	char * templine = strdup(line);
	pol = strtok(templine, " ");
	char * intString;
	intString = strtok(NULL, " ");
	quantum = atoi(intString);
	intString = strtok(NULL, " ");
	numCores = atoi(intString);
	printf("policy: %s\nquantum: %d\ncores: %d\n", pol, quantum, numCores);

    while (fgets(line, 50, ifp) != NULL) {
		templine = strdup(line);
		intString = strtok(templine, " ");
		id = atoi(intString);
		intString = strtok(NULL, " ");
		arr = atoi(intString);
		intString = strtok(NULL, " ");
		dur = atoi(intString);

        coll[i++] = process_constructor(pol, quantum, numCores, id, arr, dur);

        num_processes++;
		printf("%d\t%d\t%d\n", coll[num_processes - 1]->id, coll[num_processes - 1]->arrive, coll[num_processes - 1]->duration);
    }

	if      (strcmp(pol, "fcfs-single") == 0)  fcfs_single();
	else if (strcmp(pol, "fcfs-percore") == 0) fcfs_percore();
	else if (strcmp(pol, "rr-percore") == 0)   rr_percore();
	else if (strcmp(pol, "rr-load") == 0)      rr_load();
	else printf("Invalid entry.\n");

    return 0;
}
