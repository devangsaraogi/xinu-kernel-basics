// go through the all the processes, proctab[] holds all processes
// info will be printed for all processes that are not free and are with priority > given priority
// print info; get current esp if current process else get pesp

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>  

static inline unsigned long read_esp(void) {
    unsigned long v;
    __asm__ __volatile__("movl %%esp, %0" : "=r"(v));
    return v;
}

void printprocstks(int priority) {
    int i;
    unsigned long curr_esp;

    // get the current stack pointer
    curr_esp = read_esp();

    // going through all the processes
    for (i = 0; i < NPROC; i++) {
        // skip free processes first
        if (proctab[i].pstate == PRFREE) {
            continue;
        }

        // skip processes with priority <= to given priority
        if (proctab[i].pprio <= priority) {
            continue;
        }

        // required process info
        kprintf("Process [%s]\n", proctab[i].pname);
        kprintf("\tpid: %d\n", i);
        kprintf("\tpriority: %d\n", proctab[i].pprio);
        kprintf("\tbase: 0x%X\n", proctab[i].pbase);
        kprintf("\tlimit: 0x%X\n", proctab[i].plimit);
        kprintf("\tlen: %d\n", proctab[i].pstklen);    
        
        // currebt process from current stack pointer, read from esp else read from pesp
        if (i == currpid) {
            kprintf("\tpointer: 0x%X\n", curr_esp);
        } else {
            kprintf("\tpointer: 0x%X\n", proctab[i].pesp);
        }
        kprintf("\n");
    }
}