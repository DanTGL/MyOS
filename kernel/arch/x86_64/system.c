#include <kernel/system.h>

#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "misc.h"

void system_setup() {
    cli();
    init_gdt();
    init_idt();
    init_interrupts();
    sti();
}

__attribute__((noreturn)) void hcf(void) {
	for (;;) {
        hlt();
	}
}
