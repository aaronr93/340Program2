#include "declarations.h"
#ifndef _FCFS_PERCORE_
#define _FCFS_PERCORE_

void fcfs_percore() {
	srandom((unsigned)time(NULL));
	int i;
	//Process fcfs_percore_p[100];
	Process* cores[20][50];
	for (i = 0; i < 20; i++) {
		int j;
		for (j = 0; j < 50; j++) {
			cores[i][j] = NULL;
		}
	}

	//adding to a global list of processes
	for (i = 0; i < num_processes; i++) {
		coll[i]->done = false;
		coll[i]->start = -1;
		coll[i]->running = false;
	}

	for (i = 0; i < num_processes; i++) {
		int rand_core = rand() % numCores;

		//now add the process to the end of the random processor
		int k = 0;
		while (true) {
			if (cores[rand_core][k] == NULL) break;
			else k++;
		}
		cores[rand_core][k] = coll[i];
		printf("k = %d. Added process %d to core %d\n", k, cores[rand_core][k]->id, rand_core);
	}

	// Sim time.
	int k;		// Iterator
	int current_time = 0;	// Time counter

	bool still_running = true;

	int t[20];
	// Init to 0
	for (i = 0; i < 20; i++) {
		t[i] = 0;
	}

	while (still_running)
	{
		still_running = false;

		for (i = 0; i < numCores; i++)
		{

			int temp = t[i];
			int time_left = cores[i][t[i]]->duration;		// Burst time countdown initiates.

			while (true)
			{

				if (cores[i][t[i]] != NULL && !cores[i][t[i]]->done && cores[i][t[i]]->arrive <= current_time)//if there is a process at the current ticker (t) position
				{

					// Set as Ready to Start Processing
					if (cores[i][t[i]]->start == -1) {
						cores[i][t[i]]->start = current_time;
					}

					still_running = true;

					for (k = 0; k < time_left; k++) {
						// EXECUTION
						time_left--;		// Decrement time by 1 unit
						printf("\tProcess %d executing: time left = %d\n", cores[i][t[i]]->id, time_left);
						// If it's all done:
						if (time_left <= 0) {
							cores[i][t[i]]->done = true;
							cores[i][t[i]]->finish = cores[i][t[i]]->start + cores[i][t[i]]->duration;
							printf("Finished executing process %d\n", cores[i][t[i]]->id);
							break;
						}
					}

				}
				t[i]++;
				if (cores[i][t[i]] == NULL) {
					t[i] = 0;//reset the ticker if it's gone through each process
				}
				//if you come around to temp again there's nothing left on this core
				if (t[i] == temp) {
					break;
				}

				if (time_left <= 0) break;
			}

		}
		break;
	}
}

#endif
