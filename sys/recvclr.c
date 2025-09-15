/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{
	STATWORD ps;  
	unsigned long start_time, end_time;  
	WORD	msg;

	if(syscall_trace_flag) {
		start_time = ctr1000;
	}

	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);

	if(syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_RECVCLR].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_RECVCLR].total_time += duration;
	}

	return(msg);
}
