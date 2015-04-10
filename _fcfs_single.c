#include "declarations.h"

#ifndef _FCFS_SINGLE_
#define _FCFS_SINGLE_

void fcfs_single(int i) {
	// Adding to the global queue
	for(; i < num_processes; i++){//ask user for info manually for now, will need to do file input at some point
		printf("Process %d id: ", i);
		scanf("%d", &id);
		fcfs_single_p[i].id = id;
		printf("Process %d arrive time: ", i);
		scanf("%d", &arrive);
		fcfs_single_p[i].arrive = arrive;
		printf("Process %d duration: ", i);
		scanf("%d", &duration);
		fcfs_single_p[i].duration = duration;
		fcfs_single_p[i].done = false;
		fcfs_single_p[i].start = -1;

	}

	for(i = 0; i < numCores; i++){
		fcfs_single_cores[i] = &fcfs_single_p[i];
	}

	//after the info has been input, run the scheduler
	int current_time = 0; //start at the beginning
	bool still_running; //each time through the loop it will reset this to false, if a process is found that is not yet done, it sets it true
	bool did_something; // if no process has arrived and not executed before the current time, it needs to advance the clock

	do {

		still_running = false;
		did_something = false;
		for(i = 0; i < numCores; i++)
		{
			if(fcfs_single_cores[i]->done == true){
				int j;
				for(j = 0; j < num_processes; j++){
					if(fcfs_single_p[j].done == false){
						fcfs_single_cores[i] = &fcfs_single_p[j];
						still_running = true;
					}
				}
			}
			if(fcfs_single_cores[i]->done == false){//only need to do anything if the process still hasn't executed
				still_running = true;
				if(fcfs_single_cores[i]->arrive <= current_time)//execute the process if it's arrival time is before or at the current time
				{
					did_something = true;
					if(fcfs_single_cores[i]->start == -1) fcfs_single_cores[i]->start = current_time;
					fcfs_single_cores[i]->duration -= 1;
					if(fcfs_single_cores[i]->duration <= 0){
						fcfs_single_cores[i]->done = true;
						fcfs_single_cores[i]->finish = current_time + 1;
					}
				}
			}

		}
		current_time++;
	} while(still_running);

	//this way it's outputting by the order the processes are given
	for(i = 0; i < num_processes; i++) {
		printf("%d\t%d\t%d\t%d\t%d\n", fcfs_single_p[i].id, fcfs_single_p[i].start, fcfs_single_p[i].finish, fcfs_single_p[i].finish - fcfs_single_p[i].arrive, fcfs_single_p[i].start - fcfs_single_p[i].arrive);
	}
}

#endif
