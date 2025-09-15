/* test.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

int prX;
void halt();

/*------------------------------------------------------------------------
*  main  --  user main program
*------------------------------------------------------------------------
*/
void prch(char c)
{
    int i;
    sleep(5);	
}
int main()
{
    kprintf("Task 1 (zfunction)\n");
    kprintf("0xaabbccdd => 0x%lx\n", zfunction(0xaabbccdd));

    kprintf("Task 2 (printprocstks)\n");
    printprocstks(10);

    kprintf("Task 3 (printsyscallsummary)\n");
    syscallsummary_start();        
    resume(prX = create(prch,2000,20,"proc X",1,'A'));
    sleep(10);
    syscallsummary_stop();
    printsyscallsummary();
    return 0;
}