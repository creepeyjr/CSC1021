Cian's Shell Manual
-------------------


NAVIGATION:
===========

Press SPACE for next page
Press ENTER for next line
Press 'q' to quit



OVERVIEW :
==========

A simple C based command line interpreter (Shell) 


LIST OF BUILT-IN COMMANDS :
===========================

cd /path/to/somwhere     Changes the current working directory.
clr                      Wipes the screen of all text.
dir                      List the contents of current directory.
environ                  List all environment strings.
echo Text of some sort.  Repeats back text typed after command. 
help                     Opens basic user manual.
pause                    Halt all operations and inputs to shell until "Enter" is pressed.
quit                     Close the shell.


MODES :
=======

This Shell supports 2 modes, which can be controlled by how the shell is invoked.

Interactive Mode
----------------

./simpleshell                Will read individual command arguements typed into shell.


Read Mode
---------

./simpleshell batchfile.txt  Will read the contents of a specified Batch text file.

EXTERNAL COMMAND EXECUTION :
============================

Any command not recognised as a built-in is executed as an external program.

The shell will fork a child process and execute the program.

I/O REDIRECTION :
=================

The shell supports both standard input and output redirection.

Output Redirection (Overwrite) :
--------------------------------
>   Redirects standard output to a file, overwriting the file if it exists.

Output Redirection (Append) :
-----------------------------
>>  Redirects standard output to a file, appending to the file if it exists.

Input Redirection (Reading) :
-----------------------------
<   Redirects standard input from a file.

Input and output redirections can be used in tandum with eachother.

BACKGROUND EXECUTION :
======================

The shell supports running programs in the background.

&   When a command ends with "&", the shell will return it's prompt immediately, while the program continues running.