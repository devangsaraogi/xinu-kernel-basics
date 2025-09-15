/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
extern	struct	sentry	semaph[];

	unsigned long start_time, end_time;
	if(syscall_trace_flag) {
		start_time = ctr1000;
	}
	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
		return(SYSERR);

	if(syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_SCOUNT].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_SCOUNT].total_time += duration;
	}

	return(semaph[sem].semcnt);
}
