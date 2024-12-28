#include "idt.h"
#include <stdint.h>
#include <stdbool.h>

#define MAX_IDT_GATES 256

#define GATE_TYPE_INT64     0x8E // 64-bit Interrupt Gate
#define GATE_TYPE_TRAP64    0x8F // 64-bit Trap Gate

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
static bool idt_gates[MAX_IDT_GATES];

extern void load_idt(struct idt_descriptor);

void load_idt(struct idt_descriptor idtr) {
    asm volatile("lidt %0" :: "m"(idtr));
}

extern uint64_t isr_stubs[32];

int set_idt_gate(unsigned int num, uint64_t address, uint8_t type) {
    if (idt_gates[num] || num >= MAX_IDT_GATES) return -1; // IDT Gate is unavailable

    idt_entries[num].type_attributes = type;

    idt_entries[num].selector = 0x8;
    idt_entries[num].ist = 0;
    idt_entries[num].offset_low  =  address & 0x000000000000FFFF;
    idt_entries[num].offset_mid =  (address & 0x00000000FFFF0000) >> 16;
    idt_entries[num].offset_high = (address & 0xFFFFFFFF00000000) >> 32;


    idt_gates[num] = true;

    return 0;
}

int alloc_idt_gate(uint64_t address, uint8_t type) {
    for (int i = 32; i < MAX_IDT_GATES; i++) {
        if (set_idt_gate(i, address, type) != -1) {
            return i;
        }
    }

    return -1;
}

void free_idt_gate(unsigned int num) {
    if (num < 32 || num >= MAX_IDT_GATES) return; // The first 32 entries are required by x86
    idt_gates[num] = false;
    idt_entries[num].type_attributes &= 0b01111111;
}

void init_idt() {
    static struct idt_descriptor idtr;

    idtr.size = (sizeof(struct idt_gate) * MAX_IDT_GATES - 1);
    idtr.address = (uint64_t)idt_entries;

    for (unsigned int i = 0; i < 32; i++) {
        set_idt_gate(i, isr_stubs[i], GATE_TYPE_INT64);
    }

    load_idt(idtr);
}