#ifndef _LAB0_H_
#define _LAB0_H_

#include <kernel.h>
#include <proc.h>

// T1
long zfunction(long param);

// T2
void printprocstks(int priority);

// T3
#define NSYSCALLS 27

// syscall statistics structure
struct syscall_stats {
    int syscall_count;
    unsigned long total_time;
};

// syscall statistics structure for each process
struct process_syscall_stats {
    struct syscall_stats syscalls[NSYSCALLS];
};

// global syscall tracking variables
extern struct process_syscall_stats syscall_table[NPROC];
extern int syscall_trace_flag;

void syscallsummary_start(void);
void syscallsummary_stop(void);
void printsyscallsummary(void);

// syscall numbers
enum syscall_numbers {
    SYSCALL_FREEMEM,    
    SYSCALL_CHPRIO,         
    SYSCALL_GETPID,         
    SYSCALL_GETPRIO,        
    SYSCALL_GETTIME,        
    SYSCALL_KILL,           
    SYSCALL_RECEIVE,        
    SYSCALL_RECVCLR,        
    SYSCALL_RECVTIM,        
    SYSCALL_RESUME,         
    SYSCALL_SCOUNT,         
    SYSCALL_SDELETE,        
    SYSCALL_SEND,           
    SYSCALL_SETDEV,         
    SYSCALL_SETNOK,         
    SYSCALL_SCREATE,        
    SYSCALL_SIGNAL,         
    SYSCALL_SIGNALN,        
    SYSCALL_SLEEP,          
    SYSCALL_SLEEP10,        
    SYSCALL_SLEEP100,       
    SYSCALL_SLEEP1000,      
    SYSCALL_SRESET,         
    SYSCALL_STACKTRACE,     
    SYSCALL_SUSPEND,        
    SYSCALL_UNSLEEP,        
    SYSCALL_WAIT            
};

#endif
