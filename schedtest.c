#include "types.h"
#include "stat.h"
#include "user.h"

// Infinite loop for child processes 
void spin() {
    while(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        // Print usage and exit if not enough arguments are provided
        printf(1, "usage: schedtest loops tickets1 [tickets2 ... ticketsN]\n");
        printf(1, "\tloops must be greater than 0\n");
        printf(1, "\ttickets must be greater than or equal to 10\n");
        printf(1, "\tup to 7 tickets can be provided\n");
        exit();
    }

    // this will get the number of loops
    int loops = atoi(argv[1]);
    if (loops <= 0) {
        printf(1, "loops must be greater than 0\n");
        exit();
    }

    // check for number of tickets no more than 7 can be provided
    if (argc - 2 > 7) {
        printf(1, "up to 7 tickets can be provided\n");
        exit();
    }

    // start for the child processes 
    int i;
    for (i = 0; i < argc - 2; i++) {
        int tickets = atoi(argv[i + 2]);
        if (tickets < 10) {
            printf(1, "tickets must be greater than or equal to 10\n");
            exit();
        }

        int pid = fork();

        // check for error
        if (pid < 0) {
            exit();
        }

        // each child process should make a system call to settickets then call an infinite loop
        if (pid == 0) {
            settickets(tickets); 
            spin();              
            exit();              
        } 
    }

    // Parent process calls ps() in a loop
    int j;
    for (j = 0; j < loops; j++) {
        ps();      // Call ps to display process status
        sleep(3);  // Sleep for 3 seconds between calls
    }

    // Parent kills child processes and exits
    int k;
    for (k = 0; k < argc - 2; k++) {
        kill(getpid());
        wait();
    }

    // Exit the parent process
    exit();
}
