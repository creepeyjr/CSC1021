#include"utility.h"  // include prototypes

// Helper functions defined

void dirCwd() {  // Function to print PATH to terminal.
    char cwd[MAX_BUFFER];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\n%s :- ", cwd);
    }
}

void parseInput(char *userInput, char *args[]) {
    // DEBUG PRINT STATEMENTS
    //printf("%c", *userInput);  // correctly grabs pointer input

    int index = 0;  // Although we will use a while loop, we will still need to track where to place the parsed token in our array

    // begin tokenisation here.
    char *token;  // pointer token to store the current token during iteration.
    const char sep[] = " \t";  // Seperater (Delimiter) used when tokenising,to split arguements
    // const as it won't change, and is "\t" as that represents spaces and/or tabs
    token = strtok(userInput, sep);  // use strtok to get the first token

    // iterate through input and get tokens until we get a NULL token, which marks the end of the User input.
    while (token != NULL) {
        // DEBUG : print current token
        //printf("TEST Return token entered -: %s\n", token);

        // Store this token inside array
        args[index] = token;

        // Grab the next token. (Loop again)
        token = strtok(NULL, sep);
        index ++;  // next position in array
    }
    args[index] = NULL;  // add on NULL to the end, Mark the end of the args list

    /* // DEBUG CHECK IF ARRAY HAVE BEEN CORRECTLY FILLED WITH ARGS
    for(int j = 0; args[j] != NULL; j++) {
        printf("TEST args[index] : %s\n", args[j]);
    }
    printf("Total Arguements : %i\n", index);
    */
}

void execute(char*args[]) {
    // Internal Command/Aliases

    if (args[0] == NULL) {  // If nothing or empty space (pressed enter)
        return;  // prompt again
    }

    /* // DEBUG Test strcmp, got a problem where strcmp wasnt comparing correctly, Used this to debug the problem/
    printf("args[0] : %s", args[0]);
    printf("strcmp comparison : %d\n", strcmp(args[0], "testt"));
    */

    // I use strcmp here to compare strings, since we can't directly compare strings in C.
    // Essentially, Compare each char in the first arguement, to each char in the outlined "function".
    // If the match (== 0), execute.
    if (strcmp(args[0], "cd") == 0) {
        cdFunc(args[1]);
    }
    else if (strcmp(args[0], "clr") == 0) {
        system("clear");
        printf("Cian's Shell\n------------\n\n");
        //printf("Cleared screen.\n");
    }
    else if (strcmp(args[0], "dir") == 0) {
        dir(args[1]);
    }
    else if (strcmp(args[0], "environ") == 0) {
        printEnviron();
    }
    else if (strcmp(args[0], "echo") == 0) {
        echo(args);
    }
    else if (strcmp(args[0], "quit") == 0) {
        printf("\nClosing Cian's Shell.\nSlán go fóill!\n");
        exit(0);
    }
    else if (strcmp(args[0], "pause") == 0) {
        pauseFunc();
    }
    else if (strcmp(args[0], "help") == 0) {
        help();
    }
    else {
        printf("Unidentified command.\nType 'help' to get a list of commands.\n");
    }
}