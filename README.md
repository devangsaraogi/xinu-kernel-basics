# XINU Kernel Basics

## Overview
Introduction to XINU operating system kernel programming, implementing low-level x86 assembly operations, process stack inspection, and system call tracing with statistical tracking across 27 system calls.

## Key Features
- **Assembly Programming**: Bitwise operations implemented entirely in x86 assembly (`zfunction`)
- **Process Stack Analysis**: Inspection and reporting of process stack information including base, limit, size, and pointer
- **System Call Tracing**: Comprehensive tracking of 27 system calls with frequency counts and average execution time per process
- **Statistical Analysis**: Start/stop tracing mechanism with per-process syscall summaries
- **LTTng-inspired Design**: Loosely based on Linux Trace Toolkit Next Generation functionality

## Files Modified/Created

### Created Files
- [`h/lab0.h`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/h/lab0.h) - Header file exposing task functions
- [`sys/zfunction.S`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/zfunction.S) - Task 1: x86 assembly bitwise operations
- [`sys/printprocstks.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/printprocstks.c) - Task 2: Process stack information display
- [`sys/printsyscallsummary.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/printsyscallsummary.c) - Task 3: System call tracing and summary (includes `syscallsummary_start()` and `syscallsummary_stop()`)

### Modified Files (27 System Calls)
All system calls modified to add tracing hooks:
- [`sys/freemem.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/freemem.c), [`sys/chprio.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/chprio.c), [`sys/getpid.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/getpid.c), [`sys/getprio.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/getprio.c), [`sys/gettime.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/gettime.c)
- [`sys/kill.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/kill.c), [`sys/receive.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/receive.c), [`sys/recvclr.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/recvclr.c), [`sys/recvtim.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/recvtim.c), [`sys/resume.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/resume.c)
- [`sys/scount.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/scount.c), [`sys/sdelete.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/sdelete.c), [`sys/send.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/send.c), [`sys/setdev.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/setdev.c), [`sys/setnok.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/setnok.c)
- [`sys/screate.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/screate.c), [`sys/signal.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/signal.c), [`sys/signaln.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/signaln.c), [`sys/sleep.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/sleep.c), [`sys/sleep10.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/sleep10.c)
- [`sys/sleep100.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/sleep100.c), [`sys/sleep1000.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/sleep1000.c), [`sys/sreset.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/sreset.c), [`sys/stacktrace.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/stacktrace.c), [`sys/suspend.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/suspend.c)
- [`sys/unsleep.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/unsleep.c), [`sys/wait.c`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/wait.c)

### Build Configuration
- [`compile/Makefile`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/compile/Makefile) - Added new source files to build

## How to Build and Run

### Build
```bash
cd compile
make depend  # First time only or after Makefile changes
make
```

This creates the XINU kernel image `xinu.elf`.

### Run
```bash
cd compile
make run
```

To exit QEMU: Press `Ctrl-a` then `c`, then type `q` at the (qemu) prompt.

### Debug
In one terminal:
```bash
cd compile
make debug
```

In another terminal:
```bash
gdb xinu.elf
(gdb) target remote localhost:1234
(gdb) b main
(gdb) c
```

### Clean
```bash
cd compile
make clean
```

## Expected Results

### Task 1: `zfunction()`
```
Task 1 (zfunction)
0xaabbccdd => 0xbbc00dff
```

**Operations performed:**
- Clear bits 20-27 (counting from left, starting at 0)
- Shift left by 8 bits
- Fill rightmost 8 bits with 1s

### Task 2: `printprocstks()`
```
Task 2 (printprocstks)
Process [main]
    pid: 49
    priority: 20
    base: 0x00ff0ff0
    limit: 0x00ffffff
    len: 4096
    pointer: 0x00ffff33
```

Displays stack information for all processes with priority greater than the specified parameter.

### Task 3: `printsyscallsummary()`
```
Task 3 (printsyscallsummary)
Process [pid:49]
    Syscall: sys_sleep, count: 1, average execution time: 5000 (ms)
```

Shows frequency and average execution time of all traced system calls, grouped by process.

## Notes/Assumptions
- **Assembly requirement**: `zfunction()` must be written entirely in x86 assembly (`.S` file, not inline assembly)
- **Stack pointer access**: Uses inline assembly to read `%esp` register for current process
- **Time measurement**: Uses global variable [`ctr1000`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/sys/clkinit.c) (millisecond counter)
- **Process table**: Accesses [`proctab[]`](https://github.com/devangsaraogi/xinu-kernel-basics/blob/main/h/proc.h) array for process information
- **System calls traced**: 27 out of 43 declared system calls
- **Tracing window**: Only syscalls between `syscallsummary_start()` and `syscallsummary_stop()` are recorded
- **Process tracking**: Includes terminated processes in the summary
- **Main.c warning**: Test programs should not be in `main.c` as it will be replaced during grading
- **Debug output**: Must be disabled before submission

## Development Environment
- **Platform**: XINU+QEMU VCL image (CSC501)
- **Storage**: NC State Drive (`/mnt/ncsudrive/`)
- **Architecture**: x86 (32-bit)
- **Assembler**: GNU Assembler (AT&T syntax)
- **Debugger**: GDB with remote target support

## Acknowledgments

This project was completed as part of the graduate-level Operating Systems course (Fall 2025), **CSC 501: Operating Systems Principles**, at North Carolina State University, instructed by **Prof. Man-Ki Yoon**.

## Additional Resources
- See [ASSIGNMENT.md](ASSIGNMENT.md) for complete project specification
- [XINU Source Documentation](https://github.com/devangsaraogi/xinu-kernel-basics)
- [AT&T Assembly Syntax](http://en.wikibooks.org/wiki/X86_Assembly/GAS_Syntax)
- [Intel 64 and IA-32 Software Developer's Manual](https://cdrdv2.intel.com/v1/dl/getContent/671200)
- [GDB Documentation](https://www.sourceware.org/gdb)
