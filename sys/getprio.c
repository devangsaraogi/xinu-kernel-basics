/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	STATWORD ps; 
	unsigned long start_time, end_time;
	struct	pentry	*pptr;

	if (syscall_trace_flag) {
		start_time = ctr1000;
	}

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		return(SYSERR);
	}
	restore(ps);

	if (syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_GETPRIO].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_GETPRIO].total_time += duration;
	}

	return(pptr->pprio);
}
