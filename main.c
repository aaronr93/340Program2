#include "declarations.h"

int main(int argc, char** argv) {

    // 1. Display list of schedulers, have user choose
    // 2. Call controller function for that scheduler
    // 3. Do the stuff (and the things - don't forget about the things)
    // 4. Output results


    // Initialize pointers to structs for each scheduler.
    // Contain all the heuristics for each.
    fcfs_single = (Process)malloc(sizeof(Process));
    fcfs_percore = (Process)malloc(sizeof(Process));
    rr_percore = (Process)malloc(sizeof(Process));
    rr_load = (Process)malloc(sizeof(Process));

    do {

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
            // Call apropros function
        } else if (input == 2) {
            // fcfs_percore
            // Call apropros function
        } else if (input == 3) {
            // rr_percore
            // Call apropros function
        } else if (input == 4) {
            // rr_load
            // Call apropros function
        } else {
            printf("Invalid choice.\n");
        }

    } while (1);

    return 0;
}
