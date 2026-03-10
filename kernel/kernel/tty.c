#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include <flanterm/flanterm.h>

static struct flanterm_context *flanterm_ctx;

void terminal_initialize(struct flanterm_context *ft_ctx)
{
    flanterm_ctx = ft_ctx;
}

void terminal_putchar(char c)
{
    flanterm_write(flanterm_ctx, &c, sizeof(c));
}

void terminal_write(const char *data, size_t size)
{
    flanterm_write(flanterm_ctx, data, size);
}

void terminal_writestring(const char *data)
{
    terminal_write(data, strlen(data));
}
