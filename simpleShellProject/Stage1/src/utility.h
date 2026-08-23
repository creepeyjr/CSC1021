// maintains that this file is included only once in the main shell file.
#ifndef UTILITY_H  // begin an if, everything must be included here.
#define UTILITY_H

/* Include necessary libraries*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Used to get User's PATH and manipulate said PATH

// Definitions ADD DEFS
#define MAX_ARGS 64
#define MAX_BUFFER 1024

// Global Variables
extern char **environ;

// Helper Function Prototypes
void parseInput(char *userInput, char *args[]);
void execute(char*args[]);
void dirCwd(); 
void manPath(char * realPath);  // used to get user's path and trace manual page.


// Function Prototypes
void cdFunc(char *path);  // NEED TO IMPLEMENT THIS
void dir(char *path);
void printEnviron();
void echo(char * args[]);
void pauseFunc();
void help();


// At the end of the file, close the if
#endif