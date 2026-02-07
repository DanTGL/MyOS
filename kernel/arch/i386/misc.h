#ifndef ARCH_I386_INTERRUPT_UTILS_H
#define ARCH_I386_INTERRUPT_UTILS_H

static inline void cli()
{
    asm volatile ("cli" : : : "memory");
}

static inline void sti()
{
    asm volatile ("sti" : : : "memory");
}

static inline void hlt()
{
    asm volatile ("hlt" : : : "memory");
}

#endif
