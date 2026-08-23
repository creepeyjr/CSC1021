/*
----------------
Author : Cian McSharry Daly
Student ID : 43857



PLAN :
After reading the brief, I have outlined the steps I shall take to build the simple shell below.

- Begin by adding libraries and function prototypes.
- Must decern if the command input is a:
    - Batch text file to read & execute ; or
    - a command function for my shell to perform.
- If not in Batch mode, start trying to parse cmd input arguements outside the main function.
- Then, execute the now parsed commands with another external function.

- Polish functions, make sure they execute correctly in the shell.
- Throughout, but maninly at the end, thoroughly analyise code and compare with brief.
*/


// USE WHEN COMPILING : gcc simpleshell.c functions.c helperFunctions.c -o simpleshell


#include "utility.h" // So this links this file to the function prototypes in utility.h
// Standard necessary includes are also stored in utility.h


// Function prototypes are inside utility.h


/*
Main Function
- Where loop is; and
- Where input parsing happens
*/
int main (int argc, char*argv[]) {
    printf("Cian's Shell\n------------\n\n");
    // If shell is invoked with a command line arguement, enter "Batch Mode".
    
    FILE *pFile = NULL;  // establish file pointer

    if (argv[1] != NULL) {  // if arg[1] (second arguement after shell file) exists, enter "Batch Mode"
        pFile = fopen(argv[1], "r");  // Read the file
        printf("ENTERING BATCH MODE.\n");
        if (pFile == NULL) {  // if the file is empty, produce error
            printf("ERROR : FAILED TO OPEN%s. \n", argv[1]);
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
RESEARCH & RESOURCES REFERENCES
-------------------------------
C User Input - https://www.w3schools.com/c/c_user_input.php
3.C : A Simple Shell - https://loop.dcu.ie/mod/book/view.php?id=2862651&chapterid=613151
    - DEFINE explanation from here
    - General structure of program inspired from here
    - Beginning of execution function also based from here
What is strcmp - https://www.w3schools.com/c/ref_string_strcmp.php
What are tokens and Why should I use them? - https://stackoverflow.com/questions/4547570/tokenizing-a-string-in-c
    - How I would go about implementing tokens into my code? - https://blog.jyotiprakash.org/split-a-string-by-a-delimiter
Strip \n characters from my args - https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
snfprints, what are they, why should I use them? - https://www.geeksforgeeks.org/c/snprintf-c-library/
How to print Environ - https://stackoverflow.com/questions/4291080/print-the-environment-variables-using-environ
How to make cd function work - https://www.geeksforgeeks.org/linux-unix/chdir-in-c-language-with-examples/
Get path - https://www.tutorialspoint.com/find-out-the-current-working-directory-in-c-cplusplus#:~:text=In%20C%2FC%2B%2B%2C%20we,it%20with%20the%20directory%20path.
Reading in text file - https://csc1038.computing.dcu.ie/file.html
chdir to change dir - https://pubs.opengroup.org/onlinepubs/009695299/functions/chdir.html#:~:text=The%20chdir()%20function%20shall,pathnames%20not%20beginning%20with%20'%2F'.
hide text input to terminal - https://www.tutorialspoint.com/hiding-text-input-on-linux-terminal#:~:text=Using%20read%20%2Ds%20Option,displaying%20anything%20on%20the%20terminal. 
How to make a makefile - https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/#:~:text=Makefiles%20are%20a%20simple%20way,small%20to%20medium%2Dsized%20projects.
*/