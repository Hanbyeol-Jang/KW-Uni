#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 128

int main(int argc, char const* argv[])
{
	int i = 0;
	FILE* fwrite;
	fwrite = fopen("./temp.txt", "a+");	// create file
	
	if(fwrite == NULL){			// when create failed
		printf("FILE WRITE ERROR!\n");
		return 1;
	}
	
	srand(time(NULL));	// seed for random sampling number

	for(i=0 ; i<MAX_PROCESSES*2 ; i++)		// write random number	
	{						// twice as much as
		fprintf(fwrite, "%d\n", 2+rand()%20);	// MAX_PORCESSES
	}

	fclose(fwrite);		// close file
	return 0;
}
