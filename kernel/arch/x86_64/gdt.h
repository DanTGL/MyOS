#ifndef X86_64_GDT_H
#define X86_64_GDT_H

#define SEG_NULL        (0x00)
#define SEG_KERNEL_CODE (0x08)
#define SEG_KERNEL_DATA (0x10)
#define SEG_USER_CODE   (0x18)
#define SEG_USER_DATA   (0x20)

void init_gdt();

#endif
