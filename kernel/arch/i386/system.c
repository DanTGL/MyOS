#include <kernel/system.h>
#include "idt.h"
#include "gdt.h"
#include "misc.h"

void system_setup() {
    cli();
    init_gdt();
    init_idt();
    sti();
}

int interrupt_alloc(void* interrupt_handler) {
    return alloc_idt_gate((uint32_t)&interrupt_handler, GATE_TYPE_INT32);
}

int interrupt_set(int interrupt, void *interrupt_handler) {
    return set_idt_gate(interrupt, (uint32_t)&interrupt_handler, GATE_TYPE_INT32);
}

void interrupt_free(int interrupt) {
    free_idt_gate(interrupt);
}