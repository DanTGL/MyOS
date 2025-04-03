#ifndef ARCH_x86_64_I8042_H
#define ARCH_x86_64_I8042_H

#include "cpu.h"

void keyboard(struct interrupt_frame *frame);

#endif
