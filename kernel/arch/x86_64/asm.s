.section .text

.global reload_segments
.type reload_segments, @function
reload_segments:
    push $0x08
    lea reload_cs(%rip), %rax
    push %rax
    lretq
reload_cs:
    mov $0x10, %ax
    mov %ax,  %ds
    mov %ax,  %es
    mov %ax,  %fs
    mov %ax,  %gs
    mov %ax,  %ss
    ret
