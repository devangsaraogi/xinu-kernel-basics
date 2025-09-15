/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern unsigned long ctr1000;
/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	unsigned long start_time, end_time;

	if (syscall_trace_flag) {
		start_time = ctr1000;
	}

	if (syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_GETPID].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_GETPID].total_time += duration;
	}

	return(currpid);
}
