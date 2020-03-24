#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 16384

int main(int argc, char const* argv[])
{
	int i;
	
	if(mkdir("./tmp1",0777)<0){	// make directory when doesn't exist
		printf("[ERROR]MAKE DIRECTORY! \n");
		return 1;
	}
	
	srand(time(NULL));	// seed

	for(i=0 ; i<MAX_PROCESSES ; i++)
	{
		char f_num[64] = {0, };
		sprintf(f_num, "./tmp1/%d.txt", i);	// store the address of text

		FILE* f_write;
		f_write = fopen(f_num, "w");		// create file as much as MAX_PROCESSES
		fprintf(f_write, "%d", 1+rand()%9);	// write randon number in the file
		fclose(f_write);			// close file
	}

	return 0;
}
