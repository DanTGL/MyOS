#ifndef KERNEL_ARCH_X86_64_PIT_H_
#define KERNEL_ARCH_X86_64_PIT_H_

#include <arch/cpu.h>

void timer_handler(cpu_context_t *context);

#endif // !KERNEL_ARCH_X86_64_PIT_H_
