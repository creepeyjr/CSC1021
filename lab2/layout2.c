#include <stdio.h>
#include <stdlib.h>

int x;
int a,b,c,d;  // Added uninitialised variables
int y = 15;

int main(int argc, char *argv[])
{
	int *values;
	int i;

	values = (int *)malloc(sizeof(int)*5);

	for(i=0; i<5; i++)
		values[i] = i * y;

	return 0;
}
/*
	Size layout2 output
        - Data is larger with 4 uninitialised variables, each 4 bytes
    -------------------

    text	   data	    bss	    dec	    hex	filename
    1426	    604	     28	   2058	    80a	layout2

    Size layout output
		- Data is large due to runtime and glibc support code in the head.
	------------------
	text	   data	    bss	    dec	    hex	filename
	1426	    604	     12	   2042	    7fa	layout
*/
