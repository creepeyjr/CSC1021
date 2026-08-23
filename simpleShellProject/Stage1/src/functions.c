#include"utility.h"  // include prototypes

void cdFunc(char *path) {
    char cwd[MAX_BUFFER];  // buffer for current working dir
    
    // First check if there is any addition arg
    if (path == NULL) {
        printf("Current Dir : %s\n", getenv("PWD"));
        /*
        if (getcwd(cwd, sizeof(cwd)) != NULL) {  // if current working exists, then print it 
            printf("%s\n", cwd);  // print out cwd
        }*/
    }
    else if (chdir(path) == 0) {  // chdir causes path named to become current curr working dir.  
        getcwd(cwd, sizeof(cwd));  // get the PATH
        setenv("PWD\n", cwd, 1);  // 1 means overwrite if exists
    }
    else {
        printf("Failure. No file or directory %s", path);
    }
}

void dir(char *path) {
    // DEBUG grab and store path
    //printf("Handle this PATH : %s\n", path);

    // check the contents of the path, if it is nothing, show current dir
    if (path == NULL) {
        printf("Listing current dir.\n");
        path = ".";
    }
    else {
        printf("Listing this PATH : %s\n", path);
    }
    // build the command for executing.
    char command[MAX_BUFFER]; 
    /*
    OLD SOLUTION Encounter segmentation fault : Memory problem I assume, something with the allocation of memory.
    strcpy(command, "ls -al ");  // copy beginning of command to variable.
    strcat(command, path);  // add on path
    */


    // REVISED : safe formatted print
    // We use snprintf here to create the command, since we dedicate 1024 bytes to command, we need to cut off the
    // excess somewhere, which I will do here
    snprintf(command, sizeof(command), "ls -al %s", path);

    system(command);
}

void printEnviron() {
    int i = 0;
    while(environ[i]) {  // loop through the list of environ
        printf("%s\n", environ[i++]);  // printing in the format variable = value
    }
}

void echo(char * args[]) {
    int i = 1;  // skip the echo command itself

    // if the input arguements is empty, print a blank line.
    if (args[i] == NULL) {
        printf("\n");
        return;  // Exit the function, no need to continue
    }

    printf("%s", args[i]);  // first arguement, with no space behind it
    i++;

    while(args[i] != NULL) {  // Repeat until we reach the end (NULL)
        printf(" %s", args[i]);  // first arguement, with no space behind it
        i++;
    }
    printf("\n"); // Lastly, finish with one last new line.
}

void pauseFunc() {
    printf("[PAUSED] Press Enter to continue.");

    system("stty -echo");  // disable echo on terminal
    // wait for enter from user
    while (getchar() != '\n');

    system("stty echo");  // renable echo on terminal
}

void help() {

    // tried and failed to make the manual more page open anywhere in the terminal.
    // It will only properly open when inside the bin directory.
    FILE *file = fopen("../manual/readme.txt", "r");

    if (file == NULL) {
        printf("Manual not found or corrupt.\n");
        printf("Printing embedded man page\n\n");
        printf("LIST OF BUILT-IN COMMANDS\n===========================\n\n");
        printf("cd /path/to/somwhere     Changes the current working directory.\nclr                      Wipes the screen of all text.\ndir                      List the contents of current directory.\nenviron                  List all environment strings.\necho Text of some sort.  Repeats back text typed after command. \nhelp                     Opens basic user manual.\npause                    Halt all operations and inputs to shell until 'Enter' is pressed.\nquit                     Close the shell.\n\n");
        printf("MODES :\n========\n\n.INTERACTIVE MODE : ./simpleshell\n\tWill read individual command arguements typed into shell.\n");
        printf("READ MODE : ./simpleshell batchfile.txt\n\tWill read the contents of a specified Batch text file.\n\n");
        
        printf("(Tried and failed to make the manual more page open anywhere in the terminal.\nIt will only properly open when called inside the /bin/ directory.)\n");
        return;
    }

    system("cat ../manual/readme.txt | more");
    
    fclose(file);
}