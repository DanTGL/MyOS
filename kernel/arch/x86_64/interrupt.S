.section .text
.extern interrupt_handler

.macro isr_err n
isr_\n:
    pushq $\n
    jmp common_int_handler
.endm

.macro isr_no_err n
isr_\n:
    pushq $0
    pushq $\n
    jmp common_int_handler
.endm

common_int_handler:
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rsp
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    mov %rsp, %rdi
    call interrupt_handler
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rsp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax
    add $16, %rsp
    iretq

.section .text
isr_no_err 0
isr_no_err 1
isr_no_err 2
isr_no_err 3
isr_no_err 4
isr_no_err 5
isr_no_err 6
isr_no_err 7
isr_err    8
isr_no_err 9
isr_err    10
isr_err    11
isr_err    12
isr_err    13
isr_err    14
isr_no_err 15
isr_no_err 16
isr_err    17
isr_no_err 18
isr_no_err 19
isr_no_err 20
isr_no_err 21
isr_no_err 22
isr_no_err 23
isr_no_err 24
isr_no_err 25
isr_no_err 26
isr_no_err 27
isr_no_err 28
isr_no_err 29
isr_err    30
isr_no_err 31

.altmacro
.set i, 32
.rept 256-i
isr_no_err %i
.set i, i+1
.endr


.macro isr_ptr n
    .quad isr_\n
.endm

.section .data
.global isr_stubs
isr_stubs:
.set i, 0
.rept 256
    isr_ptr %i
    .set i, i+1
.endr

.noaltmacro
