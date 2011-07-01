#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>
#include <memory.h>

void runChild(char* param)
{
	printf("0x%08x\n", param);
}

int main()
{
	ucontext_t m;
	
	ucontext_t child;
	getcontext(&child);
	child.uc_link = &m;
	child.uc_stack.ss_sp = malloc(SIGSTKSZ);
	child.uc_stack.ss_size = SIGSTKSZ;
	child.uc_stack.ss_flags = 0;
	makecontext(&child, (void(*)())&runChild, 1, "plop");
	
	setcontext(&child);
	
	return 0;
}