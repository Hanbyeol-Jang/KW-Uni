#include <stdio.h>
#include <unistd.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <sched.h>	// sched_setscheduler( )

#define MAX_PROCESSES 16384

void* thr_fn(void*);	// when create thread, call this function
pid_t gettid(void);	// to get thread id
int thr_num = 0;	// global variable

int main()
{
	int i = 0;
	int priority = 0;
	struct sched_param param;
	struct timespec start_time, end_time; 	// performance measure
	clock_gettime(CLOCK_MONOTONIC, &start_time);	// clock start

	pthread_t tid[MAX_PROCESSES];

	printf("Input priority: \n");
	scanf("%d", &priority);
	param.sched_priority = priority;
	//	sched_setscheduler(0, SCHED_OTHER, &param);
	sched_setscheduler(0, SCHED_FIFO, &param);
//	sched_setscheduler(0, SCHED_RR, &param);
	 
	for(i=0 ; i<MAX_PROCESSES ; i++){		// as mush as MAX_PROCESSES
		pthread_create(&tid[i], NULL, thr_fn, (void*)0);  // create thread
		pthread_join(tid[i], NULL);		// wait
		thr_num++;				// increase thread number
	}
	
	if(sched_getscheduler(0) == 0)
		printf("[SCHED_OTHER]\n");
	else if(sched_getscheduler(0) == 1)
		printf("[SCHED_FIFO]\n");
	else if(sched_getscheduler(0) == 2)
		printf("[SCHED_RR]\n");
	
	clock_gettime(CLOCK_MONOTONIC, &end_time);	// clock end
	printf("Run time : %lu.%lu s \n", end_time.tv_sec - start_time.tv_sec, end_time.tv_nsec-start_time.tv_nsec);
						// running time measurement	
	return 0;
}

void* thr_fn(void* arg)
{
	int a = 0;
	char f_num[64] = {0, };		// to store address of text
	sprintf(f_num, "./tmp1/%d.txt", thr_num);	// text name

	FILE* fread = NULL;		// to read file
	fread = fopen(f_num, "r");	

	char temp[128] = {0, };
	char* pthemp;			// to know what it reads
	fgets(temp, sizeof(temp), fread);
	a = atoi(temp);		// type conversion to INT
	
	fclose(fread);		// close file
	
	return (void*)1;
}

pid_t gettid(void)
{
	return syscall(__NR_gettid);	// get thread id
}

