#include <kernel/system.h>
#include <stdio.h>

#include "gdt.h"
#include "i8042.h"
#include "idt.h"
#include "isr.h"
#include "kernel/scheduler.h"
#include "misc.h"
#include "pic.h"
#include "pit.h"

// WIP: Temporary test code
__attribute__((aligned(4096))) char task_stack[4096] = {0};

void task_test(void)
{

    while (true) {
        puts("Test\n");
        // puts("task_test\n");
        for (int i = 0; i < 500; ++i) {
            asm volatile("nop" ::: "memory");
        }
    }
}

void create_test_task()
{
    task_t task          = {0};
    task_params_t params = {
        .entry      = (uintptr_t)task_test,
        .userspace  = false,
        .stack_ptr  = (uintptr_t)task_stack,
        .stack_size = sizeof(task_stack),
    };

    task_create(&params, &task);
    scheduler_task_add(&task);
}

void system_setup()
{
    cli();

    init_gdt();
    init_idt();
    init_interrupts();

    scheduler_init();
    create_test_task();

    irq_install_handler(0, timer_handler);
    irq_install_handler(1, keyboard);
    sti();
}

__attribute__((noreturn)) void hcf(void)
{
    for (;;) {
        hlt();
    }
}
