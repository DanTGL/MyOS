#ifndef KERNEL_ARCH_CPU_H_
#define KERNEL_ARCH_CPU_H_

#ifdef __x86_64__
#include "x86_64/cpu.h"
#else
#error "Unsupported architecture"
#endif

#endif // !KERNEL_ARCH_CPU_H_
