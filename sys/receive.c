/* receive.c - receive */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return it
 *------------------------------------------------------------------------
 */
SYSCALL	receive()
{

	STATWORD ps;
	unsigned long start_time, end_time;    
	struct	pentry	*pptr;
	WORD	msg;

	if(syscall_trace_flag) {
		start_time = ctr1000;
	}

	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait for one	*/
		pptr->pstate = PRRECV;
		resched();
	}
	msg = pptr->pmsg;		/* retrieve message		*/
	pptr->phasmsg = FALSE;
	restore(ps);

	if(syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
        syscall_table[currpid].syscalls[SYSCALL_RECEIVE].syscall_count++;
        syscall_table[currpid].syscalls[SYSCALL_RECEIVE].total_time += duration;
	}

	return(msg);
}
