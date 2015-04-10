#include "declarations.h"
#ifndef _RR_PERCORE_
#define _RR_PERCORE_

void rr_percore() {
	srandom((unsigned)time(NULL));
	int i;
	Process rr_percore_p[500];
	Process * rr_percore_cores[20][50]; //up to 20 cores with up to 50 processes each

	//make the entire array null
	for (i = 0; i < 20; i++) {
		int j;
		for (j = 0; j < 50; j++) {
			rr_percore_cores[i][j] = NULL;
		}
	}

	// ask user how many processes
	printf("How many processes: ");

	// Receive user's choice
	int num_processes, id, arrive, duration, quantum_rr_percore;
	scanf("%d", &num_processes);

	printf("What is the quantum: ");
	scanf("%d", &quantum_rr_percore);


	//adding to a global list of processes
	for (i = 0; i < num_processes; i++) {//ask user for info manually for now, will need to do file input at some point
		printf("Process %d id: ", i);
		scanf("%d", &id);
		rr_percore_p[i].id = id;
		printf("Process %d arrive time: ", i);
		scanf("%d", &arrive);
		rr_percore_p[i].arrive = arrive;
		printf("Process %d duration: ", i);
		scanf("%d", &duration);
		rr_percore_p[i].duration = duration;
		rr_percore_p[i].done = false;
		rr_percore_p[i].start = -1;
		rr_percore_p[i].running = false;

	}





	for (i = 0; i < num_processes; i++) {
		int rand_core = rand() % numCores;

		//now add the process to the end of the random processor
		int k = 0;
		while (true) {
			if (rr_percore_cores[rand_core][k] == NULL) break;
			else k++;
		}
		rr_percore_cores[rand_core][k] = &rr_percore_p[i];
		printf("k = %d. Added process %d to core %d\n", k, rr_percore_cores[rand_core][k]->id, rand_core);
	}

	//now that all of the processes have been added, run the simulation
	int current_time = 0;
	bool still_running = true;
	int ticker[20];//ticker for which process can run on each core
	for (i = 0; i < 20; i++) {//start with process 0 on each one
		ticker[i] = 0;
	}
	while (still_running) {
		still_running = false;
		for (i = 0; i < numCores; i++) {

			int temp = ticker[i];
			int tempq = quantum_rr_percore;
			while (true) {


				if (rr_percore_cores[i][ticker[i]] != NULL && !rr_percore_cores[i][ticker[i]]->done && rr_percore_cores[i][ticker[i]]->arrive <= current_time)//if there is a process at the current ticker position
				{
					if (rr_percore_cores[i][ticker[i]]->start == -1) {
						printf("process %d has started executing\n", rr_percore_cores[i][ticker[i]]->id);
						rr_percore_cores[i][ticker[i]]->start = current_time;
					}
					still_running = true;
					int k;
					for (k = 0; k < tempq; k++) {
						rr_percore_cores[i][ticker[i]]->duration -= 1;
						tempq -= 1;
						printf(" process %d tick. tempq = %d remaining duration of process is %d\n.", rr_percore_cores[i][ticker[i]]->id, tempq, rr_percore_cores[i][ticker[i]]->duration);
						if (tempq <= 0) k = tempq;
					}
					if (rr_percore_cores[i][ticker[i]]->duration <= 0) {
						rr_percore_cores[i][ticker[i]]->done = true;
						rr_percore_cores[i][ticker[i]]->finish = current_time + (quantum_rr_percore - tempq);
						printf("Finished executing process %d\n", rr_percore_cores[i][ticker[i]]->id);
					}
				}

				ticker[i]++;
				printf("ticker %d is now at %d\n", i, ticker[i]);
				if (rr_percore_cores[i][ticker[i]] == NULL) {
					printf("The ticker on core %d is at %d so ", i, ticker[i]);
					ticker[i] = 0;//reset the ticker if it's gone through each process
					printf("ticker on core %d has reset\n", i);
				}
				//if you come around to temp again there's nothing left on this core
				if (ticker[i] == temp) {
					printf("Core %d is done\n", i);
					break;
				}

				if (tempq <= 0) break;
			}

		}
		current_time += quantum_rr_percore;
	}

	float avg_turnaround;
	float avg_wait;
	avg_turnaround = 0;
	avg_wait = 0;
	//this way it's outputting by the order the processes are given
	for (i = 0; i < num_processes; i++) {
		rr_percore_p[i].turnaround = rr_percore_p[i].finish - rr_percore_p[i].arrive;
		rr_percore_p[i].wait_time = rr_percore_p[i].start - rr_percore_p[i].arrive;
		avg_turnaround = avg_turnaround + rr_percore_p[i].turnaround;
		avg_wait = avg_wait + rr_percore_p[i].wait_time;
		printf("%d\t%d\t%d\t%d\t%d\n", rr_percore_p[i].id, rr_percore_p[i].start, rr_percore_p[i].finish, rr_percore_p[i].turnaround, rr_percore_p[i].wait_time);
	}
	avg_turnaround = avg_turnaround / num_processes;
	avg_wait = avg_wait / num_processes;
	printf("%f\t%f\n", avg_turnaround, avg_wait);


}

#endif