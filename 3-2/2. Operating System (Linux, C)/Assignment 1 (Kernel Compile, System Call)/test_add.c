#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int a=0, b=0;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	printf("%d + %d = %d\n", a, b, syscall(__NR_add, a, b));
	return 0;
}
