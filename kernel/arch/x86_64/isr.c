#include "isr.h"
#include "cpu.h"
#include "kernel/system.h"
#include "pic.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static const char *exception_strings[32] = {
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

static handlerfunc_t handlers[256];

void exception_handler(cpu_context_t *context)
{
    printf("%s\n", exception_strings[context->interrupt]);

    hcf();
}

void interrupt_handler(cpu_context_t *context)
{
    if (context->interrupt < 256 && handlers[context->interrupt] != NULL) {
        (*handlers[context->interrupt])(context);
    }
}

int install_interrupt_handler(uint8_t num, handlerfunc_t handler)
{
    if (handlers[num] != NULL || handler == NULL)
        return -1;

    handlers[num] = handler;

    return 0;
}

int uninstall_interrupt_handler(uint8_t num)
{
    // Check if the interrupt handler is already free
    if (handlers[num] == NULL)
        return -1;

    handlers[num] = NULL;

    return 0;
}

void init_interrupts()
{
    for (int i = 0; i < 32; i++) {
        if (install_interrupt_handler(i, exception_handler) != 0) {
            hcf();
        }
    }

    pic_remap(32);
}
