#include"utility.h"  // include prototypes

// Helper functions defined

void dirCwd() {  // Function to print PATH to terminal.
    char cwd[MAX_BUFFER];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\n%s :- ", cwd);
    }
}

void parseInput(char *userInput, char *args[]) {
    int index = 0;  // Although we will use a while loop, we will still need to track where to place the parsed token in our array

    // begin tokenisation here.
    char *token;  // pointer token to store the current token during iteration.
    const char sep[] = " \t";  // Seperater (Delimiter) used when tokenising,to split arguements
    // const as it won't change, and is "\t" as that represents spaces and/or tabs
    token = strtok(userInput, sep);  // use strtok to get the first token

    // iterate through input and get tokens until we get a NULL token, which marks the end of the User input.
    while (token != NULL) {
        // Store this token inside array
        args[index] = token;

        // Grab the next token. (Loop again)
        token = strtok(NULL, sep);
        index ++;  // next position in array
    }
    args[index] = NULL;  // add on NULL to the end, Mark the end of the args list
}

void execute(char*args[]) {
    if (args[0] == NULL) {  // If nothing or empty space (pressed enter)
        return;  // prompt again
    }

    // Check for "&" to enable background
    int background = 0;  // boolean integer
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "&") == 0) {
            background = 1;  // found one, so now it is true
            break;
        }
    }

    // Check args fro redirection symbols, If found, use executeExternal
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0 ||
            strcmp(args[i], ">") == 0 ||
            strcmp(args[i], ">>") == 0) {
                    executeExternal(args, background);
                    return;  // Exit after execution
        }   
    }

    // No redirections, so continue here
    

    // I use strcmp here to compare strings, since we can't directly compare strings in C.
    // Essentially, Compare each char in the first arguement, to each char in the outlined "function".
    // If the match (== 0), execute.
    if (strcmp(args[0], "cd") == 0) {
        cdFunc(args[1]);
    }
    else if (strcmp(args[0], "clr") == 0) {
        system("clear");
        printf("Cian's Shell\n------------\n\n");
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
    // So instead of just throwing an error of an unknown command, execute another command that starts the parent/child process.
    else {
        executeExternal(args, background);  // send the entire args form the user to the external execution
    }
}

/* 
Decided to place the external execution function with the normal execution function, 
and classify it as a core function of the process.
*/
extern char shellExecPath[MAX_BUFFER];
void executeExternal(char ** args, int background) {
    pid_t pid;  // Store result of fork()
    int rc;  // return code

    // Use fork() here so the parent can use pid
    pid = fork();

    switch(pid) {
        case -1:  // Failure to create child
            perror("ERROR : Attempted to create child process.\nFork Failure.\n");
            return;
    
        case 0:  // Successfully created child
            // According to the notes, I/O redirection should happen after the fork but before the exec command.
            // So will start building files here.
            
            // Check if the redirect statement had failed
            if (redirect(args) == -1) {
                perror("ERROR : Redirection setup failed\n");
                exit(1);  // exit child process with an error
            }
        
            // set parent enviorment variable
            char *envParent = getenv("SHELL");
            if (envParent != NULL) {
                setenv("parent", envParent, 1);
            } 

            // So here is where if needs be, the code handles built-in functions directly.
            if (strcmp(args[0], "dir") == 0) {
                dir(args[1]);
                exit(0);
            }
            else if (strcmp(args[0], "environ") == 0) {
                printEnviron();
                exit(0);
            }
            else if (strcmp(args[0], "echo") == 0) {
                echo(args);
                exit(0);
            }
            else if(strcmp(args[0], "help") == 0) {
                help();
                exit(0);
            }
            else {
                // Not a built in command, so we execute normally
                execvp(args[0], args);  // Execute the given command, upon success this function will exit
            
                printf("ERROR : Command '%s' not found.\n", args[0]);
                exit(1);
            }



        default :  // Represents the parent process or when pid > 0
            if (background == 1) {  // background enabled
                printf("[%d] %d\n", 1, pid);
                // Don't wait
            }
            else {
                waitpid(pid, &rc, 0);  // wait for the child process to finish
            }
        }
}

// redirect is an int function, that will return an integer based on it's success/failure.
int redirect(char ** args) {
    // Declare variables as they are required inside the function
    char *inputFileName = NULL;
    char *outputFileName = NULL;
    const char * appendMode = "w";  // Used as a boolean to determine if we overwrite or append an output file, by default will overwrite files
    int i, j = 0;  // prepare loop counters
    

    // Firstly, must parse input to find redirection sysmbols
    // Then determine what the command is trying to accomplish
    for (i = 0, j = 0; args[i] != NULL; i++) {

        // Should a "&" be found, I decided to skip over it here
        // will search for "&" in the normal execute function
        if (strcmp(args[i], "&") == 0) {
            continue;
        }
        
        // "<" INPUT FILE (Typically < precedes an input file)
        if (strcmp(args[i], "<") == 0) {
            i++;  // Jump to the name of input file
            // error check to make sure it exists
            if (args[i] == NULL) {
                perror("ERROR : Missing input file after <\n");
                return -1;  // We will return -1 upon a failure.
            }
            
            inputFileName = args[i];  // set as name
        }
        // ">" OUTPUT FILE (Overwrite)
        else if (strcmp(args[i], ">") == 0) {
            i++;  // jump ahead
            if (args[i] == NULL) {  // Same error, incase of no file name
                perror("ERROR : Missing output file after >\n");
                return -1;
            }
            outputFileName = args[i];
            // appendMode = "w";  // Although appendMode is already "w", to represent that we would declare that we are overwriting the output file
        }
        else if (strcmp(args[i], ">>") == 0) {
            i++;  // jump ahead
            if (args[i] == NULL) {
                perror("ERROR : Missing output file after >>\n");
                return -1;
            }
            outputFileName = args[i];
            appendMode = "a";  // AppendMode is now "a", so we know that we are appending to the output file.
        }
        else {  // This is a regular arguement, and shall be kept for execvp later on
            args[j++] = args[i];
        }
    }
    args[j] = NULL;  // Add NULL to the end of cleaned arguement


    // Next, must begin redirecting arguements for execution
    // Decided to use freopen, as it seems to be the simplist implementation of file redirection

    if (inputFileName != NULL) {  // If input file exists
        if (freopen(inputFileName, "r", stdin) == NULL) {  // attempt to read
            perror("Input redirection failure.\n");  // error if failure occurs
            return -1;
        }
    }

    if (outputFileName != NULL) {
        if (freopen(outputFileName, appendMode, stdout) == NULL) {
            perror("Output redirection failure.\n");
            return -1;
        }
    }
    return 0;  // Return a successful run of this function
}

/*
STAGE 2 RESOURCES AND REFERENCES
--------------------------------
fork() in C - https://www.geeksforgeeks.org/c/fork-system-call/
Adding fork and exec to your shell - https://loop.dcu.ie/mod/book/view.php?id=2862651&chapterid=613153
switch() in C - https://www.w3schools.com/c/c_switch.php#:~:text=The%20switch%20expression%20is%20evaluated,block%20and%20stops%20the%20execution
execvp() in C - https://www.geeksforgeeks.org/c/exec-family-of-functions-in-c/
getenv() in C - https://www.tutorialspoint.com/c_standard_library/c_function_getenv.htm
setenv() in C - https://pubs.opengroup.org/onlinepubs/009604499/functions/setenv.html
Example of waitpid() - https://stackoverflow.com/questions/21248840/example-of-waitpid-in-use
What is freopen() - https://www.tutorialspoint.com/c_standard_library/c_function_freopen.htm
What is dup in C - https://stackoverflow.com/questions/7861611/can-someone-explain-what-dup-in-c-does
dup() and dup2() linux system call - https://www.geeksforgeeks.org/c/dup-dup2-linux-system-call/
*/