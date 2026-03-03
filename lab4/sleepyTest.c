#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <signal.h>


void signalHandler(int sig) {
    /*printf("Program terminated : %d", sig);

    exit(sig);*/
    char msg[] = "Program terminated by signal (SIGINT). Exiting.\n";
    // write uses file descriptor 1 for STDOUT.
    write(1, msg, sizeof(msg) - 1); // sizeof(msg) includes the null terminator, so -1

    exit(sig);
}

int main(int argc, char**argv)
{
    signal(SIGINT, signalHandler); 
    
	// atoi - converts string to integer : see cplusplus.com/reference/cstdlib/atoi/
        int t = atoi(argv[1]);
        unsigned int slept;

        while(1)
        {
		// man7.org/linux/man-pages/man3/sleep.3.html
                slept = sleep(t);

                printf("process=%d ---- slept=%d\n", getpid(), slept  );
        }
}
