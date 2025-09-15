/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
	STATWORD ps;    
	unsigned long start_time, end_time;
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/

	if (syscall_trace_flag) {
		start_time = ctr1000;
	}

	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);
		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);

	if (syscall_trace_flag) {
		end_time = ctr1000;
		unsigned long duration = end_time - start_time;
		syscall_table[currpid].syscalls[SYSCALL_RESUME].syscall_count++;
		syscall_table[currpid].syscalls[SYSCALL_RESUME].total_time += duration;
	}

	return(prio);
}
