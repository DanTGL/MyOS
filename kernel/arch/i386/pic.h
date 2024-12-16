#ifndef ARCH_I386_PIC_H
#define ARCH_I386_PIC_H

#include "cpu.h"
#include <stdint.h>

typedef void (*irq_func_t)(struct interrupt_frame* frame);

void pic_remap(int offset1, int offset2);
void pic_irq_mask_all();
void pic_irq_set_mask(uint8_t irq);
void pic_irq_clear_mask(uint8_t irq);
int irq_install_handler(unsigned int irq, irq_func_t handler);
int irq_uninstall_handler(unsigned int irq);

#endif