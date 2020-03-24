#include <stdio.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <semaphore.h>	// to synchronize
#include <pthread.h>
#include <fcntl.h>
#include <time.h>	// clock_gettime()

#define MAX_PROCESSES 128

void* thr_fn(void* arg);	// when create thread, call this function
pid_t gettid(void);		// to get thread id
int thr_num = 0;		// global variable

int main()
{	
	struct timespec start_time, end_time;	// performance measure
	clock_gettime(CLOCK_MONOTONIC, &start_time);	// clock start

	int i = 0;		// variable declaration part
	int max = 0;
	max = MAX_PROCESSES;
	pthread_t tid[MAX_PROCESSES];
	
	sem_t* mysem;	// semaphore to prevent race condition
	if((mysem = sem_open("mysem", O_CREAT, 0777, 1)) == NULL){
		perror("Sem Open Error");	// when open sem failed
		return 1;
	}
		
	while(1)
	{
		for(i = 0 ; i < max ; i++){
			sem_wait(mysem);	// P, entry section
			
			pthread_create(&tid[i], NULL, thr_fn, (void*)0);  // create thread		
			pthread_join(tid[i], NULL);		// wait
			thr_num++;		// increase thread number

			sem_post(mysem);	// S, exit section
		}
		
		max = max/2;	// cause calculation result be half
		if(max == 0)	// when every calculation finished
			break; 
		printf("------------------------------------\n");
	}	
	
	sem_unlink("mysem");		// remove sem

	clock_gettime(CLOCK_MONOTONIC, &end_time);	// clock end
	printf("Run time : %lu.%lu s \n", end_time.tv_sec-start_time.tv_sec, end_time.tv_nsec-start_time.tv_nsec);
					// running time measurement
	return 0;
}

void* thr_fn(void* arg)
{
	int i = 0; 
	unsigned long long int a = 0, b = 0;
	unsigned long long int mul = 0;
	
	FILE* fread = NULL;	// to read file
	FILE* fwrite = NULL;	// to write
	fread = fopen("./temp.txt", "r");	// only read
	fwrite = fopen("./temp.txt", "a+");
	
	char temp[128] = {0, };
	char* ptemp;
	
	while(1)
	{	
		if(i == thr_num*2)	// cause 1 thread read 2 lines
			break;
		fgets(temp, sizeof(temp), fread); // until find line that have to read
		i++;			// next line
	}	
	fgets(temp, sizeof(temp), fread);  // read 1st value
	a = atoi(temp);			   // type conversion to INT
	fgets(temp, sizeof(temp), fread);  // read 2nd value
	b = atoi(temp);			
		
	printf("thread id[%ld]:  ", (unsigned long)gettid()); 		
	
	mul = a*b;	// multiplication
	printf("mul: %llu * %llu = %llu\n", a, b, mul);	// print result
	fprintf(fwrite, "%llu\n", mul); // write result at the last line
	
	fclose(fread);		// close file
	fclose(fwrite);
	
	return (void*)1;
}

pid_t gettid(void)
{
	return syscall(__NR_gettid);	// get thread id
}
