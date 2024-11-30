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
    ret
    ljmp $0x8, $reload_cs
reload_cs:
    MOV $0x10, %eax
    mov %eax,  %ds
    mov %eax,  %cs
    mov %eax,  %ss
    mov %eax,  %es
    mov %eax,  %fs
    mov %eax,  %gs
    sti
    ret
