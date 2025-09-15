#include <kernel.h>
#include <proc.h>
#include <lab0.h>

// syscall name lookup
const char *syscall_names[NSYSCALLS] = {
    "sys_freemem",
    "sys_chprio",
    "sys_getpid",
    "sys_getprio",
    "sys_gettime",
    "sys_kill",
    "sys_receive",
    "sys_recvclr",
    "sys_recvtim",
    "sys_resume",
    "sys_scount",
    "sys_sdelete",
    "sys_send",
    "sys_setdev",
    "sys_setnok",
    "sys_screate",
    "sys_signal",
    "sys_signaln",
    "sys_sleep",
    "sys_sleep10",
    "sys_sleep100",
    "sys_sleep1000",
    "sys_sreset",
    "sys_stacktrace",
    "sys_suspend",
    "sys_unsleep",
    "sys_wait"
};

int syscall_trace_flag = 0;
struct process_syscall_stats syscall_table[NPROC];

// starting syscall summary
void syscallsummary_start() {
    syscall_trace_flag = 1;
    for (int pid = 0; pid < NPROC; pid++) {
        for (int syscall_num = 0; syscall_num < NSYSCALLS; syscall_num++) {
            syscall_table[pid].syscalls[syscall_num].syscall_count = 0;
            syscall_table[pid].syscalls[syscall_num].total_time = 0;
        }
    }
}

// stopping syscall summary
void syscallsummary_stop() {
    syscall_trace_flag = 0;
}

// printing syscall summary
void printsyscallsummary() {
    int pid, syscall_num;
    struct process_syscall_stats *process_stats;

    // iterating over each process
    for (pid = 0; pid < NPROC; pid++) {
        process_stats = &syscall_table[pid];
        int has_stats = 0;

        // checking if the process has any syscall stats
        for (syscall_num = 0; syscall_num < NSYSCALLS; syscall_num++) {
            int count = process_stats->syscalls[syscall_num].syscall_count;
            unsigned long total_time = process_stats->syscalls[syscall_num].total_time;

            // print stats if syscall was made
            if (count > 0) {
                // print only once if the process has stats
                if (!has_stats) {
                    kprintf("Process [pid:%d]\n", pid);
                    has_stats = 1;
                }
                unsigned long avg_time = total_time / count;
                
                // printing syscall stats
                kprintf("\tSYSCALL: %s, COUNT: %d, AVERAGE TIME: %lu (ms)\n", syscall_names[syscall_num], count, avg_time);
            }
        }
    }
}