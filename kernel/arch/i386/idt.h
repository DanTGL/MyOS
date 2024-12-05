#ifndef I386_IDT_H
#define I386_IDT_H

#include <stdint.h>

#define GATE_TYPE_TASK      0x5 // Task Gate
#define GATE_TYPE_INT16     0x6 // 16-bit Interrupt Gate
#define GATE_TYPE_TRAP16    0x7 // 16-bit Trap Gate
#define GATE_TYPE_INT32     0xE // 32-bit Interrupt Gate
#define GATE_TYPE_TRAP32    0xF // 32-bit Trap Gate

void init_idt();
int alloc_idt_gate(uint32_t address, uint8_t type);
int set_idt_gate(unsigned int num, uint32_t address, uint8_t type);
void free_idt_gate(unsigned int num);

#endif