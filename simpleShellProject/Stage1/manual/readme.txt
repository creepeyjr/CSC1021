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

