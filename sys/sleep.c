/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	STATWORD ps;    
	unsigned long start_time, end_time;
	if (syscall_trace_flag) {
		start_time = ctr1000;
	}
	if (n<0 || clkruns==0)
		return(SYSERR);
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);

	if (syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_SLEEP].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_SLEEP].total_time += duration;
	}
	
	return(OK);
}
