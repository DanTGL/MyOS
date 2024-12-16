#ifndef ARCH_I386_CPU_H
#define ARCH_I386_CPU_H

#include <stdint.h>

struct interrupt_frame
{
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
};

#endif