#include "declarations.h"


int main(int argc, char** argv) {
    do {

        FILE *ifp, *ofp;
        char *mode = "r";
        char output_filename[] = "out.txt";

        ifp = fopen("in.txt", mode);

        if (ifp == NULL) {
            fprintf(stderr, "Can't open input file.\n");
            exit(1);
        }

<<<<<<< HEAD
        char* pol;
        char eof;
        int qua, cor, id, arr, dur;
        int num_processes = 0;
        Process* coll[500];
        int i = 0;

        while (fscanf(ifp, "%c", eof) != EOF) {

            if (fscanf(ifp, "fcfs_single", pol) == 1 ||
                fscanf(ifp, "fcfs_percore",pol) == 1 ||
                fscanf(ifp, "rr_load",     pol) == 1 ||
                fscanf(ifp, "rr_percore",  pol) == 1) {
                // ^ gets the Policy
                fscanf(ifp, "%d %d", &qua, &pol);   // Get quantum and cores
            }

            while (fscanf(ifp, "%d %d %d", &id, &arr, &dur) == 3) {
                coll[i++] = process_constructor(pol, qua, cor, id, arr, dur);
                num_processes++;
            }
        }

        for (i = 0; i < num_processes; i++) {
            if (strcmp(coll[i]->policy, "FCFS_SINGLE") == true) {
                fcfs_single(&coll[i]);
            } else if (strcmp(coll[i]->policy, "FCFS_PERCORE") == true) {

            } else if (strcmp(coll[i]->policy, "RR_LOAD") == true) {

            } else if (strcmp(coll[i]->policy, "RR_PERCORE") == true) {

            }
        }

        ofp = fopen(output_filename, "w");

        if (ofp == NULL) {
            fprintf(stderr, "Can't open output file.\n");
            exit(1);
=======
    do {
		printf("How many cores: ");
		scanf("%d", &numCores);

        // Display scheduler list to user
        printf("===========================\n");
        printf("Please choose a scheduler:\n");
        printf("(1) FCFS (single core)\n");
        printf("(2) FCFS (per core)\n");
        printf("(3) Round Robin (per core)\n");
        printf("(4) Round Robin (load)\n");
        printf("(0) Quit\n");
        printf("===========================\n");

        // Receive user's choice
        int input;
        scanf("%d", &input);

        // Conditional structure based on user's input:
        if (!input) {
            printf("\nGoodbye.\n");
            return 0;
        } else if (input == 1) {
            // fcfs_single
            fcfs_single();
        } else if (input == 2) {
            // fcfs_percore
            // Call apropros function
        } else if (input == 3) {
            // rr_percore
            rr_percore();
        } else if (input == 4) {
            // rr_load
            rr_load();
        } else {
            printf("Invalid choice.\n");
>>>>>>> 9c8ad9fa8eb6ec19834aec1143bbc3775da975a2
        }

    } while (1);

    return 0;
}
