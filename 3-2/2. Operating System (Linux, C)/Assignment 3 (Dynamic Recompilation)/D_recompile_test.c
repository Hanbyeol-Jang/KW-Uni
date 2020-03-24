#include <stdio.h>
#include <stdint.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/user.h>

int Operation(int a)
{
	__asm__(
        ".intel_syntax;"
        "mov %%eax, %1;"
        "add %%eax, 1;"
        "add %%eax, 1;"
	"imul %%eax, 2;"
	"imul %%eax, 4;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 2;"
        "add %%eax, 3;"
        "add %%eax, 1;"
        "add %%eax, 2;"
        "add %%eax, 1;"
	"add %%eax, 1;"
	"imul %%eax, 2;"
	"imul %%eax, 2;"
	"imul %%eax, 2;"
	"add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 3;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 3;"
	"add %%eax, 1;"
	"add %%eax, 1;"
        "add %%eax, 2;"
        "add %%eax, 1;"
        "add %%eax, 1;"
	"add %%eax, 1;"
        "add %%eax, 1;"
	"imul %%eax, 2;"
	"imul %%eax, 4;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 2;"
        "add %%eax, 3;"
        "add %%eax, 1;"
        "add %%eax, 2;"
        "add %%eax, 1;"
	"add %%eax, 1;"
	"imul %%eax, 2;"
	"imul %%eax, 2;"
	"imul %%eax, 2;"
	"add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 3;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 3;"
	"add %%eax, 1;"
	"add %%eax, 1;"
        "add %%eax, 2;"
        "add %%eax, 1;"
        "add %%eax, 1;"
	"add %%eax, 1;"
	"imul %%eax, 2;"
	"imul %%eax, 2;"
	"imul %%eax, 2;"
	"add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 3;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "add %%eax, 3;"
	"add %%eax, 1;"
	"add %%eax, 1;"
        "add %%eax, 2;"
        "add %%eax, 1;"
        "add %%eax, 1;"
        "mov %0, %%eax;"
        ".att_syntax;": "=r"(a): "r"(a) :"eax"
	);
	return a;
}

int main(void)
{
	uint8_t* func = (uint8_t*)Operation;
	int i = 0;
	int segment_id;
	uint8_t* shared_memory;
	
	// request space for shared memory segment
	segment_id = shmget(1234, PAGE_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);
	
	// attach shared memory
	shared_memory = (uint8_t*)shmat(segment_id, NULL, 0);
	do
	{
	shared_memory[i++] = *func;
	} while (*func++ != 0xC3);
	
	// detach shared memroy
	shmdt(shared_memory);
	printf("Data was filled to shared memory.\n");
	return 0;
}
