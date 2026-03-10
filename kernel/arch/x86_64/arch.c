#include "gdt.h"
#include "i8042.h"
#include "idt.h"
#include "isr.h"
#include "misc.h"
#include "pic.h"
#include "pit.h"
#include <arch/cpu.h>

int arch_init()
{
    init_gdt();
    init_idt();
    init_interrupts();

    irq_install_handler(0, timer_handler);
    irq_install_handler(1, keyboard);

    return 0;
}

int task_create(const task_params_t *params, task_t *out)
{
    if (out == NULL) {
        return -1; // TODO: Replace with error code
    }

    out->context.int_rip = (uintptr_t)params->entry;
    out->context.int_ss  = params->userspace ? SEG_USER_DATA : SEG_KERNEL_DATA;
    out->context.rbp     = 0;
    out->context.int_rflags = 0x202;

    // Set stack pointer to top of provided stack
    out->context.int_rsp =
        ((uintptr_t)params->stack_ptr) + params->stack_size - 1;

    out->context.int_cs = params->userspace ? SEG_USER_CODE : SEG_KERNEL_CODE;

    return 0;
}

// NOTE: Has to be called from interrupt handler
void task_switch(cpu_context_t *context, const task_t *task)
{
    *context = task->context;
}

__attribute__((__noreturn__)) void hcf()
{
    for (;;) {
        hlt();
    }
}
