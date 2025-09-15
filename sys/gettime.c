/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <proc.h>
#include <lab0.h>

extern int getutim(unsigned long *);
extern unsigned long ctr1000;

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
    /* long	now; */

	/* FIXME -- no getutim */
    unsigned long start_time, end_time;
    if (syscall_trace_flag) {
        start_time = ctr1000;
    }

    if (syscall_trace_flag) {
        end_time = ctr1000;
        unsigned long duration = end_time - start_time;
        syscall_table[currpid].syscalls[SYSCALL_GETTIME].syscall_count++;
        syscall_table[currpid].syscalls[SYSCALL_GETTIME].total_time += duration;
    }

    return OK;
}
