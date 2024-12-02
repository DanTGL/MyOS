.section .text

.global flush_gdt
.type flush_gdt, @function
flush_gdt:
    cli
    push %ebp
    mov %esp, %ebp
    lgdt 0x8(%ebp)
    pop %ebp
    mov %cr0, %eax
    or $1, %al
    mov %eax, %cr0
    ljmp $0x8, $reload_cs

reload_cs:
    mov $0x10, %ax
    mov %ax,  %ds
    mov %ax,  %es
    mov %ax,  %fs
    mov %ax,  %gs
    mov %ax,  %ss
    ret
