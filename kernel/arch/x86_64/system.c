#include <kernel/system.h>

#include "gdt.h"
#include "misc.h"

void system_setup() {
    cli();
    init_gdt();
    sti();
}
