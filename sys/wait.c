/* wait.c - wait */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{
	STATWORD ps;    
	unsigned long start_time, end_time;
	struct	sentry	*sptr;
	struct	pentry	*pptr;

	if (syscall_trace_flag) {
		start_time = ctr1000;
	}

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);
		return pptr->pwaitret;
	}
	restore(ps);

	if (syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_WAIT].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_WAIT].total_time += duration;
	}
	
	return(OK);
}
