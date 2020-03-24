#include <linux/module.h>
#include <linux/highmem.h>
#include <asm/unistd.h>

#define __NR_add 349

void **syscall_table = (void**)SYSCALL_TABLE;

asmlinkage int (*real_add)(int, int);

asmlinkage int sub(int a, int b)
{
	printk("kernel hooked func %d %d\n", a, b);
	return a-b;
}

/* Make the page writable */
void make_rw(void *address)
{
	unsigned int level;
	pte_t *pte = lookup_address((unsigned long)address, &level);
	if( pte->pte &~ _PAGE_RW )
	    pte->pte |= _PAGE_RW;
}

/* Make the page write protected */
void make_ro(void *address)
{
	unsigned int level;
	pte_t *pte = lookup_address((unsigned long)address, &level);
	pte->pte = pte->pte &~ _PAGE_RW;
}

int hooking_init(void)
{
	printk(KERN_INFO "init_[2012722028]");
	make_rw(syscall_table);
	real_add = syscall_table[__NR_add];
	syscall_table[__NR_add] = sub;
	return 0;
}

void hooking_exit(void)
{
	printk(KERN_INFO "exit_[2012722028]");
	syscall_table[__NR_add] = real_add;
	make_ro(syscall_table);
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");


