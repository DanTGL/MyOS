#ifndef I386_IDT_H
#define I386_IDT_H

#include <stdint.h>

void init_idt();
void free_gate(int num);
int set_idt_gate(unsigned int num, uint32_t address, uint8_t type);

#endif