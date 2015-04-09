#include "declarations.h"

#ifndef _FCFS_SINGLE_
#define _FCFS_SINGLE_

Process fcfs_single_p;

void fcfs_single(){
	Process fcfs_single_p[500];
	// ask user how many processes
    printf("How many processes: ");

    // Receive user's choice
    int num_processes, id, arrive, duration;
    scanf("%d", &num_processes);


	int i;
	for(i = 0; i < num_processes; i++){//ask user for info manually for now, will need to do file input at some point
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

	}

	//after the info has been input, run the scheduler
	int current_time = 0; //start at the beginning
	bool still_running; //each time through the loop it will reset this to false, if a process is found that is not yet done, it sets it true
	bool did_something; // if no process has arrived and not executed before the current time, it needs to advance the clock

	do {
		still_running = false;
		did_something = false;
		for(i = 0; i < num_processes; i++)
		{
			if(fcfs_single_p[i].done == false){//only need to do anything if the process still hasn't executed
				still_running = true;
				printf("process %d\n", i);
				if(fcfs_single_p[i].arrive <= current_time)//execute the process if it's arrival time is before or at the current time
				{
					did_something = true;
					fcfs_single_p[i].start = current_time;
					current_time = current_time + fcfs_single_p[i].duration;
					fcfs_single_p[i].done = true;
					fcfs_single_p[i].finish = current_time;
					printf("duration:%d\n",fcfs_single_p[i].duration);
				}
			}
		}
		if(!did_something) current_time++;
	} while(still_running);

	//this way it's outputting by the order the processes are given
	for(i = 0; i < num_processes; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", fcfs_single_p[i].id, fcfs_single_p[i].start, fcfs_single_p[i].finish, fcfs_single_p[i].finish - fcfs_single_p[i].arrive, fcfs_single_p[i].start - fcfs_single_p[i].arrive);
	}
}

#endif
