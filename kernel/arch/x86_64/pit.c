#include "pit.h"
#include "kernel/scheduler.h"

void timer_handler(cpu_context_t *context)
{
    static int timer = 0;

    if (timer++ >= 30) {
        scheduler_handler(context);
        timer -= 30;
    }
}
