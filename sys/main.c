#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
int main()
{
	kprintf("\n\nHello CSC 501\n\n");

	kprintf("\n\nTask 1: ZFunction\n\n");

	long param = 0xaabbccdd;
	kprintf("Param: 0x%lx\n", param);
	kprintf("Expected Result: 0xbbc00dff\n");
	long result = zfunction(param);
	kprintf("ZFunction Return: 0x%lx\n", result);

	kprintf("\n\nTask 2: Stack Trace\n\n");
	printprocstks(0);

	return 0;
}
