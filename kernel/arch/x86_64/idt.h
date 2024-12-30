#ifndef X86_64_IDT_H
#define X86_64_IDT_H

#include <stdint.h>

#define GATE_TYPE_INT64     0x8E // 64-bit Interrupt Gate
#define GATE_TYPE_TRAP64    0x8F // 64-bit Trap Gate

void init_idt();

#endif