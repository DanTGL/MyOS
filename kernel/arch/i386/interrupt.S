.section .text
.extern exception_handler

.global load_idt
.type load_idt, @function
load_idt:
    push %ebp
    mov %esp, %ebp
    lidt 0x8(%ebp)
    pop %ebp
    ret

.macro isr_err n
isr_\n:
    push $\n
    jmp common_int_handler
.endm

.macro isr_no_err n
isr_\n:
    push $0
    push $\n
    jmp common_int_handler
.endm

common_int_handler:
    pushal
    push %esp
    call exception_handler
    add $4, %esp
    popal
    add $8, %esp
    iret

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

.macro isr_ptr n
    .long isr_\n
.endm

.section .data
.global isr_stubs
isr_stubs:
.set i, 0
.rept 32
    isr_ptr %i
    .set i, i+1
.endr

.section .text
.extern irq_handler

.macro irq_stub n
irq_\n:
    push $0
    push $\n
    jmp common_irq_handler
.endm

common_irq_handler:
    pushal
    push %esp
    call irq_handler
    add $4, %esp
    popal
    add $8, %esp
    iret

.set i, 32
.rept 16
    irq_stub %i
    .set i, i+1
.endr

.section .data
.macro irq_ptr n
    .long irq_\n
.endm

.global irq_stubs
irq_stubs:
.set i, 32
.rept 16
    irq_ptr %i
    .set i, i+1
.endr

.noaltmacro
