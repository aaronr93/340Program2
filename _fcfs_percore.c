#include "declarations.h"
#ifndef _FCFS_PERCORE_
#define _FCFS_PERCORE_

void fcfs_percore() {
	srandom((unsigned)time(NULL));
	int i;
	Process fcfs_percore_p[500];
	Process* fcfs_percore_cores[20][50];

	for (i = 0; i < 20; i++) {
		int j;
		for (j = 0; j < 50; j++) {
			fcfs_percore_cores[i][j] = NULL;
		}
	}


	// ask user how many processes
    printf("How many processes: ");

    // Receive user's choice
    int num_processes, id, arrive, duration, quantum_fcfs_percore;
    scanf("%d", &num_processes);

	printf("What is the quantum: ");
	scanf("%d", &quantum_fcfs_percore);

	//adding to a global list of processes
	for(i = 0; i < num_processes; i++){//ask user for info manually for now, will need to do file input at some point
		printf("Process %d id: ", i);
		scanf("%d", &id);
		fcfs_percore_p[i].id = id;
		printf("Process %d arrive time: ", i);
		scanf("%d", &arrive);
		fcfs_percore_p[i].arrive = arrive;
		printf("Process %d duration: ", i);
		scanf("%d", &duration);
		fcfs_percore_p[i].duration = duration;
		fcfs_percore_p[i].done = false;
		fcfs_percore_p[i].start = -1;
		fcfs_percore_p[i].running = false;
	}

	for (i = 0; i < num_processes; i++) {
		int rand_core = rand() % numCores;

		//now add the process to the end of the random processor
		int k = 0;
		while (true) {
			if (fcfs_percore_cores[rand_core][k] == NULL) break;
			else k++;
		}
		fcfs_percore_cores[rand_core][k] = &fcfs_percore_p[i];
		printf("k = %d. Added process %d to core %d\n", k, fcfs_percore_cores[rand_core][k]->id, rand_core);
	}

	// Sim time.

	int current_time = 0;
	bool still_running = true;
	int ticker[20];
	for (i = 0; i < 20; i++) {
		ticker[i] = 0;
	}
	while (still_running) {
		still_running = false;
		for (i = 0; i < numCores; i++) {

			int temp = ticker[i];
			int time_left = fcfs_percore_cores[i][ticker[i]]->duration;
			while (true) {


				if (fcfs_percore_cores[i][ticker[i]] != NULL && !fcfs_percore_cores[i][ticker[i]]->done && fcfs_percore_cores[i][ticker[i]]->arrive <= current_time)//if there is a process at the current ticker position
				{
					if (fcfs_percore_cores[i][ticker[i]]->start == -1) {
						printf("process %d has started executing\n", fcfs_percore_cores[i][ticker[i]]->id);
						fcfs_percore_cores[i][ticker[i]]->start = current_time;
					}
					still_running = true;
					int k;
					for (k = 0; k < time_left; k++) {
						time_left -= 1;
						printf("\tProcess %d is executing. Duration = %d remaining duration of process is %d\n.", fcfs_percore_cores[i][ticker[i]]->id, fcfs_percore_cores[i][ticker[id]]->duration, time_left);
						if (time_left <= 0) k = time_left;
					}
					if (time_left <= 0) {
						fcfs_percore_cores[i][ticker[i]]->done = true;
						fcfs_percore_cores[i][ticker[i]]->finish = current_time;
						printf("Finished executing process %d\n", fcfs_percore_cores[i][ticker[i]]->id);
					}
				}

				ticker[i]++;
				printf("ticker %d is now at %d\n", i, ticker[i]);
				if (fcfs_percore_cores[i][ticker[i]] == NULL) {
					printf("The ticker on core %d is at %d so ", i, ticker[i]);
					ticker[i] = 0;//reset the ticker if it's gone through each process
					printf("ticker on core %d has reset\n", i);
				}
				//if you come around to temp again there's nothing left on this core
				if (ticker[i] == temp) {
					printf("Core %d is done\n", i);
					break;
				}

				if (time_left <= 0) break;
			}

		}
		current_time += quantum_fcfs_percore;
	}
}

#endif
