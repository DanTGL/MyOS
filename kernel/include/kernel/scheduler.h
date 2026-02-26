#ifndef KERNEL_SCHEDULER_H_
#define KERNEL_SCHEDULER_H_

#include <arch/cpu.h>

void scheduler_init();

void scheduler_handler(cpu_context_t *context);

void scheduler_task_add(const task_t *task);

#endif // !KERNEL_SCHEDULER_H_
