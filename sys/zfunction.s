# 0 "../sys/zfunction.S"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "../sys/zfunction.S"
    .globl zfunction

zfunction:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    andl $0xFFFFF00F, %eax
    shll $8, %eax
    orl $0x000000FF, %eax

    movl %ebp, %esp
    popl %ebp
    ret
