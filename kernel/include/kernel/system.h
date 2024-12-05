#ifndef _SYSTEM_H
#define _SYSTEM_H

void system_setup();

int interrupt_alloc(void* interrupt_handler);
int interrupt_reserve(int interrupt, void* interrupt_handler);
void interrupt_free(int interrupt);

#endif