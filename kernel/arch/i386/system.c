#include "gdt.h"
#include "i8042.h"
#include "idt.h"
#include "misc.h"
#include "pic.h"
#include <kernel/system.h>

void system_setup()
{
    cli();
    init_gdt();
    init_idt();
    pic_remap(0x20, 0x28);
    irq_install_handler(1, &keyboard);
    sti();
}

int interrupt_alloc(void *interrupt_handler)
{
    return alloc_idt_gate((uint32_t)&interrupt_handler, GATE_TYPE_INT32);
}

int interrupt_set(int interrupt, void *interrupt_handler)
{
    return set_idt_gate(
        interrupt, (uint32_t)&interrupt_handler, GATE_TYPE_INT32
    );
}

void interrupt_free(int interrupt) { free_idt_gate(interrupt); }

__attribute__((noreturn)) void hcf(void)
{
    for (;;) {
        hlt();
    }
}
