#include <arch/cpu.h>
#include <kernel/scheduler.h>
#include <stddef.h>

#define NUM_TASKS 10

static task_t tasks[NUM_TASKS] = {0};
static size_t current_task;
static size_t task_count = 1;

void scheduler_init()
{
    current_task = 0;
}

// IMPORTANT: Should only be called by interrupt handler
void scheduler_handler(cpu_context_t *context)
{
    // No need to switch task if only one exists
    if (task_count == 1)
        return;
    tasks[current_task].context = *context;
    current_task                = (current_task + 1) % task_count;
    task_switch(context, &tasks[current_task]);
}

void scheduler_task_add(const task_t *task)
{
    if (task_count < NUM_TASKS) {
        tasks[task_count++] = *task;
    }
}
