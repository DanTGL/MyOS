#ifndef X86_64_ISR_H
#define X86_64_ISR_H

#include "cpu.h"
#include <stdint.h>

typedef void (*handlerfunc_t)(struct interrupt_frame*);

void init_interrupts();
int install_interrupt_handler(uint8_t num, handlerfunc_t handler);
int uninstall_interrupt_handler(uint8_t num);

#endif