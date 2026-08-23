// maintains that this file is included only once in the main shell file.
#ifndef UTILITY_H  // begin an if, everything must be included here.
#define UTILITY_H

/* Include necessary libraries*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Used to get User's PATH and manipulate said PATH AND fork()

// Stage 2
#include <errno.h>  //  Used to report back errors occured whilst using child processes.
#include <sys/types.h>  // Used to invoke pid_t
#include <sys/wait.h>  // used for waitpid in the parent default case

// Definitions ADD DEFS
#define MAX_ARGS 64
#define MAX_BUFFER 1024

// Global Variables
extern char **environ;
extern char shellExecPath[MAX_BUFFER]; // Stage 2 - Global variable to set env path of parent process.
extern char helpPath[MAX_BUFFER];  // store the path to help page

// Core Helper Function Prototypes
void parseInput(char *userInput, char *args[]);
void execute(char*args[]);
void dirCwd(); 
void manPath(char * realPath);  // used to get user's path and trace manual page.
void externalExecute(char * args[], int background);  // Add external execution function
int redirect(char * args[]);  // Handles I/O redirection
int checkBackground(char ** args);  // Checks if command is to be run in background

// Function Prototypes
void cdFunc(char *path);
void dir(char *path);
void printEnviron();
void echo(char * args[]);
void pauseFunc();
void help();



// At the end of the file, close the if
#endif