#ifndef KERNEL_ARCH_CPU_H_
#define KERNEL_ARCH_CPU_H_

static inline void enable_interrupts();
static inline void disable_interrupts();

// IWYU pragma : begin_exports
#ifdef __x86_64__
#include "x86_64/cpu_x86_64.h"
#else
#error "Unsupported architecture"
#endif
// IWYU pragma : end_exports


int arch_init();

/** Halts the CPU until reset (Halt and Catch Fire). */
void hcf(void);

#endif // !KERNEL_ARCH_CPU_H_
