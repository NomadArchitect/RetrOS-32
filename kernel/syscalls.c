#include <syscalls.h>
#include <interrupts.h>

syscall_t syscall[255];

void add_system_call(int index, syscall_t fn)
{
	syscall[index] = fn;
}

int system_call(int index, int arg1, int arg2, int arg3)
{	
	/* Call system call function based on index. */
	syscall_t fn = syscall[index];
	int ret = fn(arg1, arg2, arg3);
	//dbgprintf("[SYSCALL] %d: %s %s\n", index, "test", "test");
	EOI(48);
	return ret;
}
