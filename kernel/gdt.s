.code32

.section .text

.global flush_gdt

.type flush_gdt, @function

flush_gdt:
    push %ebp

    mov %esp, %ebp
    mov 8(%ebp), %eax
    lgdt (%eax)

    mov $0x10, %ax
    mov %ax, %es
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %fs
    mov %ax, %gs

    pop %ebp
    ret
    