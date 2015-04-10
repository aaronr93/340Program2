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
    /*do {*/

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

        /*for (i = 0; i < num_processes; i++) {
            if (strcmp(coll[i]->policy, "FCFS_SINGLE") == true) {
                fcfs_single(&coll[i]);
            } else if (strcmp(coll[i]->policy, "FCFS_PERCORE") == true) {

            } else if (strcmp(coll[i]->policy, "RR_LOAD") == true) {

            } else if (strcmp(coll[i]->policy, "RR_PERCORE") == true) {

            }
        }*/

        /*ofp = fopen(output_filename, "w");

        if (ofp == NULL) {
            fprintf(stderr, "Can't open output file.\n");
            exit(1);
		}*/

    
		

        // Display scheduler list to user
        /*printf("===========================\n");
        printf("Please choose a scheduler:\n");
        printf("(1) FCFS (single core)\n");
        printf("(2) FCFS (per core)\n");
        printf("(3) Round Robin (per core)\n");
        printf("(4) Round Robin (load)\n");
        printf("(0) Quit\n");
        printf("===========================\n");*/

        // Receive user's choice
        int input;
        /*scanf("%d", &input);*/

		if(strcmp(pol, "fcfs-single") == 0) input = 1;
		else if (strcmp(pol, "fcfs-percore") == 0) input = 2;
		else if (strcmp(pol, "rr-percore") == 0) input = 3;
		else if (strcmp(pol, "rr-load") == 0) input = 4;
		else input = 0;

        // Conditional structure based on user's input:
        if (!input) {
            printf("\nGoodbye.\n");
            return 0;
        } else if (input == 1) {
            // fcfs_single
            fcfs_single();
        } else if (input == 2) {
            // fcfs_percore
            fcfs_percore();
        } else if (input == 3) {
            // rr_percore
			rr_percore();
        } else if (input == 4) {
            // rr_load
            rr_load();
        } else {
            printf("Invalid scheduler.\n");
			exit(1);
        }

    return 0;
}
