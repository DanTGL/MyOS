#ifndef KERNEL_ARCH_CPU_H_
#define KERNEL_ARCH_CPU_H_

static inline void enable_interrupts();
static inline void disable_interrupts();

// IWYU pragma : begin_exports
#ifdef __x86_64__
#include "x86_64/cpu.h"
#elif defined(__riscv) && (__riscv_xlen == 64)
#include "riscv64/cpu.h"
#else
#error "Unsupported architecture"
#endif
// IWYU pragma : end_exports

#ifndef __arch_spin_wait
#define __arch_spin_wait() asm volatile("nop" : : : "memory")
#endif

int arch_init();

/** Halts the CPU until reset (Halt and Catch Fire). */
void hcf(void);

#endif // !KERNEL_ARCH_CPU_H_
