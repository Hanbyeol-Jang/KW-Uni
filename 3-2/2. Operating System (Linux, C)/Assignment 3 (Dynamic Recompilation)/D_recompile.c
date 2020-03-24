#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <time.h>

uint8_t* Operation;
uint8_t* compiled_code;

int segment_id;
int fd;

void sharedmem_init(); // access to shared memory
void sharedmem_exit();
void drecompile_init(); // memory mapping start
void drecompile_exit(); 
void* drecompile(uint8_t *func); // optimized

int main(void)
{
	struct timespec start_time, end_time;  // performance measure
	clock_gettime(CLOCK_MONOTONIC, &start_time);	// clock start

	int (*func)(int a);
	int i;
	int f_execute = 0;

	sharedmem_init();
	drecompile_init();

	func = (int (*)(int a))drecompile(Operation);	// recompile
	f_execute = func(0);	// execute function
	
	drecompile_exit();
	sharedmem_exit();
	
	clock_gettime(CLOCK_MONOTONIC, &end_time);	// clock end
	printf("execute time: %lu.%06lu s \n", end_time.tv_sec - start_time.tv_sec, end_time.tv_nsec-start_time.tv_nsec);
			// running time measurement
	return 0;
}

void sharedmem_init()
{	// 1
	int pagesize = 0;
	pagesize = getpagesize();	

	segment_id = shmget(1234, getpagesize(), 0);  // get shared memory
	Operation = (uint8_t*)shmat(segment_id, NULL, 0);  // attach
	mprotect(Operation, pagesize, PROT_READ | PROT_WRITE);  // set protection RW
}

void sharedmem_exit()
{	// 4
	shmdt(Operation);  // detach
	shmctl(segment_id, IPC_RMID, NULL);  // remove shared memory
}


void drecompile_init()
{	// 2
	int pagesize = 0;
	pagesize = getpagesize();

	compiled_code = mmap(0, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);  // memory mapping 
}


void drecompile_exit()
{	// 3
	int pagesize = 0;
	pagesize = getpagesize();

	msync(compiled_code, pagesize, MS_ASYNC);  // synchronized
	munmap(compiled_code, pagesize);  // unmap
}


void* drecompile(uint8_t* func)
{	
	compiled_code = func;

#ifdef dynamic			// when make dynamic
	printf("[dynamic]\n");	
	int i = 0, j = 0;
	int flag_add = 0, flag_mul = 0;
	int last = 0;
	int add = 0;
	int mul = 1;
	int op = 0;	// operation result
	
	while(1)	
	{
		if(func[i] == 0xc3)	// ret
			break;
		
		if(func[i] == 0x83 && func[i+1] == 0xc0)  // add
		{	
			if(add == 0)	// not add yet, when first add
				flag_add = i;
			
			if(func[i+3] != 0x83)
				last = i+3;	// to store last instruction
			
			add += func[i+2];  // add operation
			op += func[i+2];
		}
		else if(func[i] == 0x6b && func[i+1] == 0xc0)  // imul
		{
			if(mul == 1)	// not mul yet, when first mul
				flag_mul = i;
			
			mul *= func[i+2]; // mul operation
			op *=func[i+2];
		}
		i++;
	}
	
	printf("result: %d \n", op);
		
	for(j=0 ; j<flag_add ; j++)	// before operation	
		compiled_code[j] = func[j];

	compiled_code[flag_add] = 0x83;		// add command
	compiled_code[flag_add+1] = func[flag_add+1];
	compiled_code[flag_add+2] = add;
	compiled_code[flag_add+3] = 0x6b;	// mul command
	compiled_code[flag_add+4] = func[flag_mul+1];
	compiled_code[flag_add+5] = mul;
	
	j = flag_add+6;

	while(func[last] != 0xc3)	// fill the rest
	{	
		compiled_code[j] = func[last];
		j++;
		last++;
	}

	compiled_code[j] = 0xc3;	// fill last instrustion
	
#endif	
	int pagesize = 0;
	pagesize = getpagesize();
	mprotect(compiled_code, pagesize, PROT_READ | PROT_EXEC);
	// set protection RX
	return compiled_code;
}

