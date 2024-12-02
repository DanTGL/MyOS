#include <stdint.h>
#include <stdio.h>

struct interrupt_frame
{
    unsigned int error_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
};

static const char* exception_strings[32] = {
    "Division Error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bounds Check",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Exception",
    "General Protection Exception",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved",
};

void exception_handler(struct interrupt_frame* frame, unsigned int interrupt) {
    if (interrupt < 32) {
        printf("%s", exception_strings[interrupt]);
    }
}