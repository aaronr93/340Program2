#include "declarations.h"

#ifndef _FCFS_SINGLE_
#define _FCFS_SINGLE_



typedef struct fcfs_single_process{//to store all the info about the processes
	int id; //id of process
	int arrive; //arival time of process
	int duration; //duration of process
	int finish; //finish time of process
	int start; //the time it actually starts
	bool done; //is the process done executing?
}fcfs_single_p;

void fcfs_single(){
		struct fcfs_single_process processes[500];
	// ask user how many processes
        printf("How many processes: ");
      
        // Receive user's choice
        int num_processes, id, arrive, duration;
        scanf("%d", &num_processes);

		
		int i;
		for(i = 0; i < num_processes; i++){//ask user for info manually for now, will need to do file input at some point
			printf("Process %d id: ");
			scanf("%d", &id);
			processes[i].id = id;
			printf("Process %d arrive time: ");
			scanf("%d", &arrive);
			processes[i].arrive = arrive;
			printf("Process %d duration: ");
			scanf("%d", &id);
			processes[i].duration = duration;
			processes[i].done = false;
			
		}

		//after the info has been input, run the scheduler
		int current_time = 0; //start at the beginning
		bool still_running = true; //each time through the loop it will reset this to false, if a process is found that is not yet done, it sets it true
		while(still_running)
		{
			still_running = false;
			for(i = 0; i < num_processes; i++)
			{
				if(processes[i].done == false){//only need to do anything if the process still hasn't executed
					still_running = true;
					if(processes[i].arrive <= current_time)//execute the process if it's arrival time is before or at the current time
					{
						processes[i].start = current_time;
						current_time = current_time + processes[i].duration;
						processes[i].done = true;
						processes[i].finish = current_time;
					}
				}
			}

		}

		//this way it's outputting by the order the processes are given
		for(i = 0; i < num_processes; i++)
		{
			printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].start, processes[i].finish, 0, 0); //output the process info
		}
}

#endif