/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	short	*nxtdev;
	unsigned long start_time, end_time;
	
	if(syscall_trace_flag) {
		start_time = ctr1000;
	}

	if (isbadpid(pid))
		return(SYSERR);
	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;

	if(syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_SETDEV].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_SETDEV].total_time += duration;
	}

	return(OK);
}
