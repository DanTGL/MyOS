// IWYU pragma: private; include <arch/cpu.h>

#ifndef KERNEL_ARCH_RISCV64_CPU_H_
#define KERNEL_ARCH_RISCV64_CPU_H_

#include <stddef.h>

static inline void disable_interrupts() {}

static inline void enable_interrupts() {}

typedef struct cpu_context_t {

} cpu_context_t;

typedef struct task_t {
    size_t task_id;
    cpu_context_t context;
} task_t;

#define __arch_spin_wait __builtin_riscv_pause

#endif // !KERNEL_ARCH_RISCV64_CPU_H_
