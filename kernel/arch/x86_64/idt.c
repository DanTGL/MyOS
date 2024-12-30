#include "idt.h"
#include <stdint.h>

#define MAX_IDT_GATES 256

struct idt_gate {
    uint16_t offset_low;
    uint16_t selector;  // Code segment selector in GDT or LDT
    uint8_t ist;
    uint8_t type_attributes;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed));

struct idt_descriptor {
    uint16_t size;
    uint64_t address;
} __attribute__((packed));

static struct idt_gate idt_entries[MAX_IDT_GATES];

extern void load_idt(struct idt_descriptor);

void load_idt(struct idt_descriptor idtr) {
    asm volatile("lidt %0" :: "m"(idtr));
}

extern uint64_t isr_stubs[MAX_IDT_GATES];

int set_idt_gate(unsigned int num, uint8_t type) {
    if (num >= MAX_IDT_GATES) return -1; // IDT Gate is unavailable

    idt_entries[num].type_attributes = type;

    uint64_t address = isr_stubs[num];

    idt_entries[num].selector = 0x8;
    idt_entries[num].ist = 0;
    idt_entries[num].offset_low  =  address & 0x000000000000FFFF;
    idt_entries[num].offset_mid =  (address & 0x00000000FFFF0000) >> 16;
    idt_entries[num].offset_high = (address & 0xFFFFFFFF00000000) >> 32;

    return 0;
}

void init_idt() {
    static struct idt_descriptor idtr;

    idtr.size = (sizeof(struct idt_gate) * MAX_IDT_GATES - 1);
    idtr.address = (uint64_t)idt_entries;

    for (unsigned int i = 0; i < MAX_IDT_GATES; i++) {
        set_idt_gate(i, GATE_TYPE_INT64);
    }

    load_idt(idtr);
}