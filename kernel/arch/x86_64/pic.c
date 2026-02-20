#include "pic.h"
#include "cpu.h"
#include "io.h"
#include <stddef.h>
#include <stdint.h>

#define PIC1_BASE 0x20
#define PIC2_BASE 0xA0

#define PIC_CMD(base)  (base)
#define PIC_DATA(base) (base + 1)

#define ICW1_ICW4      0x1  // ICW4 is needed
#define ICW1_SINGLE    0x2  // Single PIC
#define ICW1_INTERVAL4 0x4  // 4-byte interrupt vector (8-byte otherwise)
#define ICW1_LEVEL     0x8  // Level triggered (edge mode)
#define ICW1_INIT      0x10 // Initialization

#define ICW4_8086          0x1 // 8086 Mode (8080 Mode otherwise)
#define ICW4_AUTO          0x2 // Auto EOI
#define ICW4_BUF_SECONDARY 0x8 // Buffered mode / secondary
#define ICW4_BUF_PRIMARY   0xC // Buffered mode / primary
#define ICW4_SFNM          0x10 // Special fully nested mode (Sequential otherwise)

#define PIC_EOI 0x20 // End of interrupt command

static unsigned int PIC_OFFSET = 0;

static handlerfunc_t irq_vector[16];

void pic_eoi(uint8_t irq)
{
    if (irq >= 8) {
        outb(PIC_CMD(PIC2_BASE), PIC_EOI);
    }

    outb(PIC_CMD(PIC1_BASE), PIC_EOI);
}

void pic_irq_mask_all()
{
    outb(PIC_DATA(PIC1_BASE), 0xFF);
    outb(PIC_DATA(PIC2_BASE), 0xFF);
}

void pic_irq_set_mask(uint8_t irq)
{
    uint16_t pic = (irq < 8) ? PIC1_BASE : PIC2_BASE;
    irq %= 8;
    uint8_t mask = inb(PIC_DATA(pic)) | (1 << irq);
    outb(PIC_DATA(pic), mask);
}

void pic_irq_clear_mask(uint8_t irq)
{
    uint16_t pic = (irq < 8) ? PIC1_BASE : PIC2_BASE;
    irq %= 8;
    uint8_t mask = inb(PIC_DATA(pic)) & ~(1 << irq);
    outb(PIC_DATA(pic), mask);
}

int irq_install_handler(unsigned int irq, handlerfunc_t handler)
{
    if (irq >= 16 || irq_vector[irq] != NULL) {
        return -1;
    }

    irq_vector[irq] = handler;
    pic_irq_clear_mask(irq);

    return 0;
}

int irq_uninstall_handler(unsigned int irq)
{
    if (irq >= 16 || irq_vector[irq] == NULL) {
        return -1;
    }

    irq_vector[irq] = NULL;
    pic_irq_set_mask(irq);

    return 0;
}

void irq_handler(cpu_context_t *context)
{
    if (context->interrupt < PIC_OFFSET)
        return;

    unsigned int irq = context->interrupt - PIC_OFFSET;
    if (irq >= 16 || irq_vector[irq] == NULL) {
        return;
    }

    (*irq_vector[irq])(context);

    pic_eoi(irq);
}

void pic_remap(unsigned int offset)
{
    uint8_t mask1, mask2; // Save interrupt masks
    mask1 = inb(PIC_DATA(PIC1_BASE));
    mask2 = inb(PIC_DATA(PIC2_BASE));

    // Initialize primary and secondary PIC
    outb(PIC_CMD(PIC1_BASE), ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC_CMD(PIC2_BASE), ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(
        PIC_DATA(PIC1_BASE), offset
    ); // ICW2: Primary PIC interrupt vector offset
    io_wait();
    outb(
        PIC_DATA(PIC2_BASE), offset + 8
    ); // ICW2: Secondary PIC interrupt vector offset
    io_wait();
    outb(
        PIC_DATA(PIC1_BASE), 0b00000100
    ); // ICW3: Inform primary PIC of secondary PIC at IRQ2
    io_wait();
    outb(
        PIC_DATA(PIC2_BASE), 2
    ); // ICW3: Secondary PIC attached to IRQ2 on primary PIC
    io_wait();

    // ICW4: Configure PICs to use 8086 mode
    outb(PIC_DATA(PIC1_BASE), ICW4_8086);
    io_wait();
    outb(PIC_DATA(PIC2_BASE), ICW4_8086);
    io_wait();

    // Restore saved interrupt masks
    outb(PIC_DATA(PIC1_BASE), mask1);
    outb(PIC_DATA(PIC2_BASE), mask2);

    for (int i = 0; i < 16; i++) {
        install_interrupt_handler(offset + i, irq_handler);
    }

    pic_irq_mask_all();
    PIC_OFFSET = offset;
}
