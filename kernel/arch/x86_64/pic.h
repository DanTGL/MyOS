#ifndef ARCH_X86_64_PIC_H
#define ARCH_X86_64_PIC_H

#include "isr.h"

void pic_remap(unsigned int offset);
int irq_install_handler(unsigned int irq, handlerfunc_t handler);
int irq_uninstall_handler(unsigned int irq);

#endif
