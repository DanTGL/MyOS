#include "gdt.h"
#include <stdint.h>
#include <string.h>

#define SEG_TYPE_CD   (1 << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES      (1 << 0x07) // Present
#define SEG_SAVL      (1 << 0x0C) // Available for system use
#define SEG_LONG      (1 << 0x0D) // Long mode
#define SEG_SIZE      (1 << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN      (1 << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)   (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)

// Data segment types
#define DATA_RD			0x0 // Read-Only
#define DATA_RDA		0x1 // Read-Only, accessed
#define DATA_RDWR		0x2 // Read/Write
#define DATA_RDWRA		0x3 // Read/Write, accessed
#define DATA_RDEXPD 	0x4 // Read-Only, expand-down
#define DATA_RDEXPDA	0x5 // Read-Only, expand-down, accessed
#define DATA_RDWREXPD	0x6 // Read/Write, expand-down
#define DATA_RDWREXPDA	0x7 // Read/Write, expand-down, accessed

// Code segment types
#define CODE_EX			0x8 // Execute-Only
#define CODE_EXA		0x9 // Execute-Only, accessed
#define CODE_EXRD		0xA // Execute/Read
#define CODE_EXRDA		0xB // Execute/Read, accessed
#define CODE_EXC		0xC // Execute-Only, conforming
#define CODE_EXCA		0xD // Execute-Only, conforming, accessed
#define CODE_EXRDC		0xE // Execute/Read, conforming
#define CODE_EXRDCA		0xF	// Execute/Read, conforming, accessed

static uint64_t gdt_entries[3];

struct gdt_descriptor {
    uint16_t size;
    uint64_t address;
} __attribute__((packed));

extern void reload_segments();

int set_descriptor(size_t num, uint32_t base, uint32_t limit, uint16_t flag) {
	if (num >= (sizeof(gdt_entries) / sizeof(*gdt_entries))) {
		return -1;
	}

	// Set the high 32 bit segment
	gdt_entries[num] = limit		 & 0x000F0000;
	gdt_entries[num] |= (flag <<  8) & 0x00F0FF00;
	gdt_entries[num] |= (base >> 16) & 0x000000FF;
	gdt_entries[num] |= base		 & 0xFF000000;

	// Shift by 32 to allow for low part of segment
	gdt_entries[num] <<= 32;

	// Set the low 32 bit segment
	gdt_entries[num] |= limit & 0x0000FFFF;
	gdt_entries[num] |= (base << 16);

	return 0;
}

void load_gdt(struct gdt_descriptor gdtr) {
    asm volatile("lgdt %0" :: "m"(gdtr));
}

void init_gdt() {
    struct gdt_descriptor gdtr;

	set_descriptor(0, 0, 0, 0);
	set_descriptor(1, 0x00000000, 0xFFFFFFFF, (SEG_PRIV(0) | CODE_EXRD | SEG_TYPE_CD | SEG_PRES | SEG_GRAN | SEG_LONG));
	set_descriptor(2, 0x00000000, 0xFFFFFFFF, (SEG_PRIV(0) | DATA_RDWR | SEG_TYPE_CD | SEG_PRES | SEG_GRAN | SEG_SIZE));

    gdtr.address = (uint64_t)gdt_entries;
    gdtr.size = sizeof(gdt_entries);

    load_gdt(gdtr);
    reload_segments();
}