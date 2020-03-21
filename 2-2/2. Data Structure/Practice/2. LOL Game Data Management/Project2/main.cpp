#include "Manager.h"
#include <stdio.h>

int main()
{
	Manager k(3);
	k.run("command_list.txt");	// run the textfile
    return 0;
}

