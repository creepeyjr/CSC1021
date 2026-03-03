#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>  // additional message for when program is manually terminated.
// Reference : https://www.geeksforgeeks.org/c/signals-c-language/

/* 
Where n is the number of 5-seconds period for which the program should sleep.
Program will sleep for 5 seconds n times before exiting.
*/


void signalCatch(int sig) {
    /*
    Unused portion of code - Less effective
    printf("Program terminated : %d", sig);
    exit(sig);
    */
    
    char sig_str[16];  // Space to store signal int
    int len = snprintf(sig_str, sizeof(sig_str), "%d", sig);
    
    const char msg[] = "\nProgram terminated by signal (";
    // write uses file descriptor 1 for STDOUT.
    write(STDOUT_FILENO, msg, sizeof(msg) - 1); // sizeof(msg) includes the null terminator, so -1
    write(1, sig_str, len);
    // char msg
    // write()
    exit(sig);
}

int main(int argc, char*argv[])
{
    // Call signalCatch
    signal(SIGINT, signalCatch); 

    int n = atoi(argv[1]);  // Convert first arguement into int.
    unsigned int slept;  // unsigned is an int that can never be negative.

    while(1)  // Supposite infinite loop
    {
        slept = sleep(n);
        printf("process=%d\nslept=%d\n", getpid(), slept);
    }
    return 0;
}

/*
Function causes the calling process to be suspended unitl either
1. Amount of wall clock time specified by seconds has elapsed.
2. A signal is caught by the process and the signal handler returns.

The return value from sleep is either 0 or number of unslept seconds if interrupted.
*/

/* Program should print out the process ID of each time it loops. */