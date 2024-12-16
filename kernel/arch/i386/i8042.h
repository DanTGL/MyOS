#ifndef ARCH_I386_I8042_H
#define ARCH_I386_I8042_H

#include "cpu.h"

void keyboard(struct interrupt_frame* frame);

#endif