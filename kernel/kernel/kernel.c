#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/system.h>

void kernel_main(void) {
	terminal_initialize();
	system_setup();
	printf("Hello, kernel World!\n");
}
