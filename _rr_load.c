#include "declarations.h"
#ifndef _RR_LOAD_
#define _RR_LOAD_

void rr_load(){
	int i;
	Process rr_load_p[500];
	Process * rr_load_cores[20][50]; //up to 20 cores with up to 50 processes each

	//make the entire array null
	for(i = 0; i < 20; i++){
		int j;
		for(j=0; j < 50; j++){
			rr_load_cores[i][j] = NULL;
		}
	}

	// ask user how many processes
    printf("How many processes: ");

    // Receive user's choice
    int num_processes, id, arrive, duration, quantum_rr_load;
    scanf("%d", &num_processes);

	 printf("What is the quantum: ");
	 scanf("%d", &quantum_rr_load);

	
	//adding to a global list of processes
	for(i = 0; i < num_processes; i++){//ask user for info manually for now, will need to do file input at some point
		printf("Process %d id: ", i);
		scanf("%d", &id);
		rr_load_p[i].id = id;
		printf("Process %d arrive time: ", i);
		scanf("%d", &arrive);
		rr_load_p[i].arrive = arrive;
		printf("Process %d duration: ", i);
		scanf("%d", &duration);
		rr_load_p[i].duration = duration;
		rr_load_p[i].done = false;
		rr_load_p[i].start = -1;
		rr_load_p[i].running = false;

	}

	//now distribute the processes to the cores, evenly at first since the empty cores will automatically have the lightest load

	for(i = 0; i <numCores; i++){
		rr_load_cores[i][0] = &rr_load_p[i];
		printf("Added process %d to core %d\n", rr_load_cores[i][0]->id, i);
	}
	//now do the rest
	for(i = numCores; i <num_processes; i++){
		//find out which core has the lightest load
		int j;
		int lightestLoad = rr_load_cores[0][0]->duration;
		int lightestLoadId = 0;
		//for each core
		for(j = 0; j < numCores; j++){
			//count the total durations on each core
			int k = 0, current_load = 0;
			while(true){
				if(rr_load_cores[j][k] == NULL){
					printf("found null spot at Core %d process %d\n", j, k);
					break;
				}
				else{
					current_load += rr_load_cores[j][k]->duration;
					k++;
				}
			}
			if(current_load <= lightestLoad){
				lightestLoad = current_load;
				lightestLoadId = j;
			}
		}
		//now add the process to the end of the lightest processor
		int k = 0;
		while(true){
			 if(rr_load_cores[lightestLoadId][k] == NULL) break;
			 else k++;
		}
		rr_load_cores[lightestLoadId][k] = &rr_load_p[i];
		printf("k = %d. Added process %d to core %d\n", k, rr_load_cores[lightestLoadId][k]->id, lightestLoadId);
	}

	//now that all of the processes have been added, run the simulation
	int current_time = 0;
	bool still_running = true;
	int ticker[20];//ticker for which process can run on each core
	for(i=0;i<20;i++){//start with process 0 on each one
		ticker[i] = 0;
	}
	while(still_running){
		still_running = false;
		for(i = 0; i <numCores; i++)
		{
			
			int temp = ticker[i];
			int tempq = quantum_rr_load;
			while(true)
			{
				

				if(rr_load_cores[i][ticker[i]] != NULL && !rr_load_cores[i][ticker[i]]->done && rr_load_cores[i][ticker[i]]->arrive <= current_time)//if there is a process at the current ticker position
				{
					if(rr_load_cores[i][ticker[i]]->start == -1){
						printf("process %d has started executing\n", rr_load_cores[i][ticker[i]]->id);
						rr_load_cores[i][ticker[i]]->start = current_time;
					}
					still_running = true;
					int k;
					for(k = 0; k < tempq; k++){
						rr_load_cores[i][ticker[i]]->duration -= 1;
						tempq -=1;
						if(tempq <= 0) break;
					}
					if(rr_load_cores[i][ticker[i]]->duration <= 0){
						rr_load_cores[i][ticker[i]]->done = true;
						rr_load_cores[i][ticker[i]]->finish = current_time + (quantum_rr_load - tempq);
						printf("Finished executing process %d\n", rr_load_cores[i][ticker[i]]->id);

					}
				}
				if(tempq <= 0) break;
				ticker[i]++;
				printf("ticker %d is now at %d\n", i, ticker[i]);
				if(rr_load_cores[i][ticker[i]] == NULL){
					printf("The ticker on core %d is at %d so ", i, ticker[i]);
					ticker[i] = 0;//reset the ticker if it's gone through each process
					printf("ticker on core %d has reset\n", i);
				}
				//if you come around to temp again there's nothing left on this core
				if(ticker[i] == temp){
					printf("Core %d is done\n", i);
					break;
				}
			}
			
		}
		current_time += quantum_rr_load;
	}

	float avg_turnaround;
	float avg_wait;
	avg_turnaround = 0;
	avg_wait = 0;
	//this way it's outputting by the order the processes are given
	for(i = 0; i < num_processes; i++)
	{
		rr_load_p[i].turnaround = rr_load_p[i].finish - rr_load_p[i].arrive;
		rr_load_p[i].wait_time = rr_load_p[i].start - rr_load_p[i].arrive;
		avg_turnaround = avg_turnaround + rr_load_p[i].turnaround;
		avg_wait = avg_wait + rr_load_p[i].wait_time;
		printf("%d\t%d\t%d\t%d\t%d\n", rr_load_p[i].id, rr_load_p[i].start, rr_load_p[i].finish, rr_load_p[i].turnaround,rr_load_p[i].wait_time);
	}
	avg_turnaround = avg_turnaround/num_processes;
	avg_wait = avg_wait/num_processes;
	printf("%f\t%f\n", avg_turnaround, avg_wait);


}

#endif