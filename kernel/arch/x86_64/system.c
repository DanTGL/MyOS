#include <kernel/system.h>

#include "gdt.h"
#include "i8042.h"
#include "idt.h"
#include "isr.h"
#include "misc.h"
#include "pic.h"

void system_setup()
{
    cli();
    init_gdt();
    init_idt();
    init_interrupts();

    irq_install_handler(1, keyboard);
    sti();
}

__attribute__((noreturn)) void hcf(void)
{
    for (;;) {
        hlt();
    }
}
