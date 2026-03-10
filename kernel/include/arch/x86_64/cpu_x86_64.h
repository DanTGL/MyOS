// IWYU pragma: private; include <arch/cpu.h>

#ifndef KERNEL_ARCH_X86_64_CPU_H_
#define KERNEL_ARCH_X86_64_CPU_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct cpu_context_t {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t interrupt;
    uint64_t error_code;
    uint64_t int_rip;
    uint64_t int_cs;
    uint64_t int_rflags;
    uint64_t int_rsp;
    uint64_t int_ss;
} cpu_context_t;

typedef void (*funcptr_t)(void);

typedef struct task_params {
    uintptr_t entry;
    bool userspace;
    uintptr_t stack_ptr;
    size_t stack_size;
} task_params_t;

typedef struct task_t {
    size_t task_id;
    cpu_context_t context;
} task_t;
static inline void disable_interrupts()
{
    asm volatile("cli" ::: "memory");
}

static inline void enable_interrupts()
{
    asm volatile("sti" ::: "memory");
}

int task_create(const task_params_t *params, task_t *out);
void task_switch(cpu_context_t *cur_context, const task_t *task);

#endif // !KERNEL_ARCH_X86_64_CPU_H_
