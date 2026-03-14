#include <arch/cpu.h>

int arch_init()
{
    return 0;
}

__attribute__((__noreturn__)) void hcf()
{
    for (;;) {
        asm volatile("wfi" ::: "memory");
    }
}
