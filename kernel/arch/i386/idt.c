#include <kernel/idt.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_IDT_GATES 256

#define GATE_TYPE_TASK      0x5 // Task Gate
#define GATE_TYPE_INT16     0x6 // 16-bit Interrupt Gate
#define GATE_TYPE_TRAP16    0x7 // 16-bit Trap Gate
#define GATE_TYPE_INT32     0xE // 32-bit Interrupt Gate
#define GATE_TYPE_TRAP32    0xF // 32-bit Trap Gate

struct idt_gate_flags {
    unsigned int zero   : 8; // Always 0
    unsigned int type   : 5; // 4-bit Gate type (5th bit is not part of gate type, and should be 0)
    unsigned int dpl    : 2; // Privilege level (0 - 3)
    unsigned int p      : 1; // Present bit (has to be 1)
} __attribute__((packed));

struct idt_gate {
    uint16_t offset_low;
    uint16_t selector;  // Code segment selector in GDT or LDT
    struct idt_gate_flags flags;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_descriptor {
    uint16_t size;
    uint32_t address;
} __attribute__((packed));

static struct idt_gate idt_entries[MAX_IDT_GATES];
static bool idt_gates[MAX_IDT_GATES];

extern void load_idt(struct idt_descriptor);

extern uint32_t isr_stubs[32];

int set_idt_gate(unsigned int num, uint32_t address, uint8_t type) {
    if (idt_gates[num] || num >= MAX_IDT_GATES) return -1; // IDT Gate is unavailable

    idt_entries[num].flags.zero = 0;
    idt_entries[num].flags.type = type;
    idt_entries[num].flags.dpl = 0;
    idt_entries[num].flags.p = 1;

    idt_entries[num].selector = 0x8;
    idt_entries[num].offset_low  =  address & 0x0000FFFF;
    idt_entries[num].offset_high = (address & 0xFFFF0000) >> 16;

    idt_gates[num] = true;

    return 0;
}

void free_idt_gate(unsigned int num) {
    if (num < 32 || num >= MAX_IDT_GATES) return; // The first 32 entries are required by x86
    idt_gates[num] = false;
    idt_entries[num].flags.p = 0;
}

void init_idt() {
    static struct idt_descriptor idtr;

    idtr.size = (sizeof(struct idt_gate) * MAX_IDT_GATES - 1);
    idtr.address = (uint32_t)&idt_entries;

    for (unsigned int i = 0; i < 32; i++) {
        set_idt_gate(i, isr_stubs[i], GATE_TYPE_INT32);
    }

    load_idt(idtr);

    asm volatile("sti");
}