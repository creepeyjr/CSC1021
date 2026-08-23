/*
----------------
Author : Cian McSharry Daly
Student ID : 43857

I HAVE REMOVED COMMENTS FROM STAGE 1 WHERE I FELT APPROPRIATE TO MAKE ROOM FOR STAGE 2 COMMENTS.

STAGE 2 UNDERSTANDING THE BRIEF
External Function Execution
-------------------------------
- All other command line inputs should be done by the shell "forking and execing" the prohrams as their own "Child process"

I/O Redirection
---------------
1. Run programname with arguements arg1 and arg2
2. Instead of reading from keyboard (stdin), read from inputfile
3. instead of writing to the screen (stdout), write to output file.

    The Symbols
    ----------- 
    < Read from file instead of keyboard
    > Write (overwrite) to file.
    >> Write to file, (append) to end if exists. 

Background Operations
---------------------
I believe by removing the waiting function inside the default (or parent) process.
The child should execute and the parent will continue to prompt the user again, simultaneously.

*/


#include "utility.h"

// Need to define the global variable here
char shellExecPath[MAX_BUFFER];
char helpPath[MAX_BUFFER];

/*
Main Function
- Where loop is; and
- Where input parsing happens
*/
int main (int argc, char*argv[]) {
    // Stage 2
    realpath(argv[0], shellExecPath);
    setenv("SHELL", shellExecPath, 1);

    // The below portion of code is to find the path to the readme page
    // find where the executable is located
    char *finalSlash;
    
    finalSlash = strrchr(shellExecPath, '/');  // find the last slash that appears in the path
    if (finalSlash != NULL) {  
        *finalSlash = '\0';  // remove the executable's name, so everything after the last slash.
    }
    snprintf(helpPath, sizeof(helpPath), "%s/../manual/readme.txt", shellExecPath);  // rebuild the path to the help page
    realpath(helpPath, helpPath);  // finally resolves the path by removing the ..


    printf("Cian's Shell\n------------\n\n");
    // If shell is invoked with a command line arguement, enter "Batch Mode".
    
    FILE *pFile = NULL;  // establish file pointer

    if (argv[1] != NULL) {  // if arg[1] (second arguement after shell file) exists, enter "Batch Mode"
        pFile = fopen(argv[1], "r");  // Read the file
        printf("ENTERING BATCH MODE.\n");
        if (pFile == NULL) {  // if the file is empty, produce error
            printf("ERROR : FAILED TO OPEN %s. \n", argv[1]);
            exit(0);
        }
    }
    if (pFile == NULL) {  // If the pointer is empty, there is no second arguement, and so just activates the shell like normal.
        pFile = stdin;  // the file pointer is the input 
    } 

    // Else, continue on to loop.

    // User input loop happens here.
    while(!feof(pFile)) {  // !feof - NOT end of file, stops the looping once we reach end of file in Batch Mode.
        char userInput[MAX_BUFFER]; // Character variable to hold command input
        char *args[MAX_ARGS];  // array to hold the parsed arguements

        // Take in User Input here
        if (pFile == stdin) {
            dirCwd();  // Call function to print PATH and prompt
        }
        fgets(userInput, sizeof(userInput), pFile);  // Grab the user input
        userInput[strcspn(userInput, "\n")] = 0;  // IMMEDIATELY strip the newline character away.
        // If we don't do this, this will cause character conflicts during execution with strcmp.

        // Begin parsing input here. 
        // What is it? What do we do with it?
        // If we are this far into the script, it is assumed that we aren't reading a batch file or in "batch mode"
        parseInput(userInput, args);

        // Execute the now parsed user input
        execute(args);
    }

    exit(0);
}




/*
RESEARCH & RESOURCES REFERENCES - STAGE 2
-----------------------------------------
What are strrchr() in C - https://www.geeksforgeeks.org/c/strrchr-in-c/
Examplde of realpath in C - https://stackoverflow.com/questions/1563168/example-of-realpath-function-in-c
*/