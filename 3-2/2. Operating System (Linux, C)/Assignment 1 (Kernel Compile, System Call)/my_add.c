#include <linux/kernel.h>

asmlinkage int sys_add(int a, int b)
{
	return a+b;
}
