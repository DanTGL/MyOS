#include <kernel/system.h>

#include "gdt.h"
#include "idt.h"
#include "misc.h"

void system_setup() {
    cli();
    init_gdt();
    init_idt();
    sti();
}
