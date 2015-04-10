#include "declarations.h"
#ifndef _FCFS_PERCORE_
#define _FCFS_PERCORE_

Core* core_constructor() {
	Core* core = malloc(sizeof(Core));
	core->core_num_proc = 0;
	core->current_process_id = 0;
	return core;
}

void core_destructor(Core* core) {
	free(core->process);
}

void fcfs_percore() {
	srandom((unsigned)time(NULL));
	int i;

	for (i = 0; i < num_processes; i++) {
		coll[i]->done = false;
		coll[i]->start = -1;
		coll[i]->running = false;
	}

	for (i = 0; i < numCores; i++) {
		cores[i] = core_constructor();
	}

	int rand_core;
	for (i = 0; i < num_processes; i++) {
		rand_core = rand() % numCores;
		cores[rand_core]->process[cores[rand_core]->core_num_proc] = coll[i];
		cores[rand_core]->core_num_proc++;
	}

	// Sim time.
	int k;		// Iterator
	int current_time = 0;	// Time counter

	bool still_running = true;

	while (still_running) {
		still_running = false;
		for (i = 0; i < numCores; i++) {

			for (k = 0; k < cores[i]->core_num_proc; k++) {
				if (!cores[i]->process[k]->done) still_running = true;
			}

			if (cores[i]->current_process_id >= cores[i]->core_num_proc) {
				;
			} else if (cores[i]->process[cores[i]->current_process_id]->arrive <= current_time) {
				if (cores[i]->process[cores[i]->current_process_id]->start == -1) {
					cores[i]->process[cores[i]->current_process_id]->start = current_time;

				}

				cores[i]->process[cores[i]->current_process_id]->duration--;

				if (cores[i]->process[cores[i]->current_process_id]->duration <= 0) {
					cores[i]->process[cores[i]->current_process_id]->done = true;
					cores[i]->process[cores[i]->current_process_id]->finish = current_time + 1;
					cores[i]->current_process_id++;
				}

			}

		}
		current_time++;

	}

	float avg_turnaround;
	float avg_wait;
	avg_turnaround = 0;
	avg_wait = 0;

	FILE * ofp = fopen("out.txt", "w");

	//this way it's outputting by the order the processes are given
	for (i = 0; i < num_processes; i++) {
		coll[i]->turnaround = coll[i]->finish - coll[i]->arrive;
		coll[i]->wait_time = coll[i]->start - coll[i]->arrive;
		avg_turnaround = avg_turnaround + coll[i]->turnaround;
		avg_wait = avg_wait + coll[i]->wait_time;
		fprintf(ofp, "\n%d\t%d\t%d\t%d\t%d\n", coll[i]->id, coll[i]->start, coll[i]->finish, coll[i]->turnaround, coll[i]->wait_time);
	}

	avg_turnaround = avg_turnaround / num_processes;
	avg_wait = avg_wait / num_processes;
	fprintf(ofp, "\n%f\t%f\n", avg_turnaround, avg_wait);

	fclose(ofp);
}

#endif
