#include <arch/cpu.h>
#include <kernel/scheduler.h>
#include <kernel/system.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifdef WITH_MULTITASKING
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
#endif

void system_setup()
{
    disable_interrupts();

    arch_init();
#ifdef WITH_MULTITASKING
    scheduler_init();
    create_test_task();
#endif

    enable_interrupts();
}
